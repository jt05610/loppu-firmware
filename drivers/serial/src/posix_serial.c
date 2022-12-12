/**
  ******************************************************************************
  * @file   posix_serial.c
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifdef __APPLE__

#include "posix_serial.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include "stdlib.h"
#include "stdbool.h"
#define TIMEOUT 4500

static struct posix_serial_t
{
    Timer  time;
    Serial base;
    const char * port;
    uint8_t    * buffer;
    uint16_t      buffer_len;
    char_size_t   char_size;
    parity_t      parity;
    termios_t     term;
    enable_t      flow_control;
    input_t       input;
    enable_t      echo;
    blocking_t    blocking;
    time_amount_t start_rec;
    output_t      output;
    uint8_t       timeout;
    uint8_t       min_char_read;
    int           file_descriptor;
    int           options;

    comm_port_list_t port_list;
} self = {0};

bool posix_serial_open();

bool posix_serial_close();

bool posix_serial_read(sized_array_t * dest);

bool posix_serial_write(const sized_array_t * data);

void posix_serial_set_options(serial_opt_t options);

static CommPortList posix_serial_list_ports(void);

static void configure_terminal();

serial_interface_t posix_interface = {
        .open = posix_serial_open,
        .close = posix_serial_close,
        .read = posix_serial_read,
        .write = posix_serial_write,
        .list_ports = posix_serial_list_ports,
        .set_options = posix_serial_set_options
};

void
posix_serial_set_timer(Timer time)
{
    self.time = time;
}

void
posix_serial_create(Serial base, SerialInit params)
{
    base->baud   = params->baud;
    base->vtable = &posix_interface;
    self.port    = params->port;
    self.buffer  = params->rx_buffer;

    self.file_descriptor = -1;
    self.base            = base;
    self.options         = DEFAULT_OPTIONS;
    self.char_size       = DEFAULT_CHAR_SIZE;
    self.parity          = DEFAULT_PARITY;
    self.input           = DEFAULT_INPUT;
    self.flow_control    = DEFAULT_FLOW_CONTROL;
    self.echo            = DEFAULT_ECHO;
    self.blocking        = DEFAULT_BLOCKING;
    self.output          = DEFAULT_OUTPUT;
    self.timeout         = DEFAULT_TIMEOUT;
    self.min_char_read   = DEFAULT_MIN_CHAR_READ;
    self.buffer_len      = 0;
}

bool posix_serial_open()
{
    bool ret = false;
    self.file_descriptor = open(self.port, self.options);
    if (-1 == self.file_descriptor)
    {
        perror("serial_open: unable to open port");
    } else
    {
        fcntl(self.file_descriptor, F_SETFL, self.blocking);
        ret = true;
        configure_terminal();
    }
    return ret;
}

bool posix_serial_close()
{
    close(self.file_descriptor);
    self.file_descriptor = -1;
    return true;
}

bool posix_serial_read(sized_array_t * data)
{
    bool   ret = false;
    size_t size;
    ioctl(self.file_descriptor, FIONREAD, &size);
    if (size)
    {
        self.start_rec = timer_micros(self.time);
        while (!ret)
        {
            ioctl(self.file_descriptor, FIONREAD, &size);
            read(self.file_descriptor, &self.buffer[self.buffer_len], size);
            data->bytes = self.buffer;
            self.buffer_len += size;
            if (timer_micros(self.time) - self.start_rec >= TIMEOUT)
            {
                data->bytes     = self.buffer;
                data->size      = self.buffer_len;
                self.buffer_len = 0;
                ret = true;
            }
        }
    }
    return ret;
}

bool posix_serial_write(const sized_array_t * data)
{
    bool           ret = true;
    static ssize_t n;
    n = write(self.file_descriptor, data->bytes, data->size);
    if (n < 0)
    {
        fputs("serial_write failed!", stderr);
        ret = false;
    }
    return ret;
}

static void set_parity_type_bits(termios_t * options, uint32_t size_mask)
{
    options->c_cflag &= ~CSTOPB;
    options->c_cflag &= ~CSIZE;
    options->c_cflag |= size_mask;
}

static void set_parity(termios_t * options, parity_t parity)
{
    if (NO_PARITY == parity)
    {
        options->c_cflag &= ~PARENB;
        set_parity_type_bits(options, CS8);
    } else
    {
        options->c_cflag |= PARENB;
        if (EVEN_PARITY == parity)
            options->c_cflag &= ~PARODD;
        else
            options->c_cflag |= PARODD;
        set_parity_type_bits(options, CS7);
        options->c_iflag |= (INPCK | ISTRIP);
    }
}

static void
configure_terminal()
{
    tcgetattr(self.file_descriptor, &self.term);
    cfsetispeed(&self.term, self.base->baud);
    cfsetospeed(&self.term, self.base->baud);
    self.term.c_cflag |= (CLOCAL | CREAD);
    self.term.c_cflag &= ~CSIZE;
    self.term.c_cflag |= self.char_size;
    set_parity(&self.term, self.parity);

#ifdef CNEW_RTSCTS
    if (self.flow_control)
            self.term.c_cflag |= CNEW_RTSCTS;
            self.term.c_iflag |= (IXON | IXOFF | IXANY);
        else
            self.term.c_cflag &= ~CNEW_RTSCTS;
            self.term.c_iflag &= ~(IXON | IXOFF | IXANY);
#endif

    if (CANONICAL_INPUT == self.input)
    {
        tcflag_t flag_mask = ICANON;
        if (self.echo)
            flag_mask |= (ECHO | ECHOE);
        self.term.c_lflag |= flag_mask;
    } else
        self.term.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    if (PROCESSED_OUTPUT == self.output)
        self.term.c_oflag |= OPOST;
    else
        self.term.c_oflag &= ~OPOST;
    self.term.c_cc[VMIN]  = self.min_char_read;
    self.term.c_cc[VTIME] = self.timeout;
    tcsetattr(self.file_descriptor, TCSANOW, &self.term);
}

void posix_serial_set_parity(Serial base, parity_t parity)
{
    if (NO_PARITY == parity || EVEN_PARITY == parity || ODD_PARITY == parity)
        self.parity = parity;
}

void posix_serial_set_input_type(Serial base, input_t input)
{
    if (CANONICAL_INPUT == input || RAW_INPUT == input)
        self.input = input;
}

void posix_serial_set_flow_control(Serial base, enable_t enable)
{
    if (ENABLE == enable || DISABLE == enable)
        self.flow_control = enable;
}

void posix_serial_set_echo(Serial base, enable_t enable)
{
    if (ENABLE == enable || DISABLE == enable)
        self.echo = enable;
}

void posix_serial_set_char_size(Serial base, char_size_t size)
{
    if (FIVE_BITS == size || SIX_BITS == size
        || SEVEN_BITS == size || EIGHT_BITS == size
            )
        self.char_size = size;
}

void posix_serial_set_blocking(Serial base, blocking_t blocking)
{
    if (BLOCKING == blocking || NON_BLOCKING == blocking)
        self.blocking = blocking;
}

void posix_serial_set_output(Serial base, output_t output)
{
    if (PROCESSED_OUTPUT == output || RAW_OUTPUT == output)
        self.output = output;
}

void posix_serial_set_timeout(Serial base, uint8_t timeout)
{
    self.timeout = timeout;
}

void posix_serial_set_min_char_read(Serial base, uint8_t value)
{
    self.min_char_read = value;
}

termios_p posix_serial_get_termios(Serial base)
{
    return &self.term;
}

int posix_serial_get_file_descriptor(Serial base)
{
    return self.file_descriptor;
}

void posix_serial_set_options(serial_opt_t options)
{
    self.options = options;
}

CommPortList posix_serial_list_ports(void)
{
    self.port_list.n_ports = 0;
    const char    * names[2] = {"tty.", "cu."};
    const char    * dir      = "/dev/";
    DIR           * dir_p;
    struct dirent * ent_p;
    dir_p         = opendir(dir);
    while ((ent_p = readdir(dir_p)))
    {
        for (uint8_t i = 0; i < 2; i++)
        {
            char * dev_name = strstr(ent_p->d_name, names[i]);
            if (dev_name)
            {
                char * name_p;
                char * dev_path = calloc(500, sizeof(char));
                self.port_list.ports[self.port_list.n_ports] = calloc(
                        1, sizeof(comm_port_t));
                sprintf(dev_path, "%s%s", dir, dev_name);
                self.port_list.ports[self.port_list.n_ports]->name = dev_path;
                name_p = dev_path;
                name_p += strlen(names[i]) + strlen(dir);
                self.port_list.ports[self.port_list.n_ports]->device = name_p;
                self.port_list.n_ports++;
            }
        }
    }
    closedir(dir_p);
    return &self.port_list;
}

int posix_serial_get_options()
{
    return self.options;
}

#endif