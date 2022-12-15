/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */


#include "needle_positioner.h"

int
main()
{
    NeedlePositioner positioner;
    needle_positioner_init_t params;
    bootstap(&params);
    positioner = needle_positioner_create(&params);
    while (1) {
        needle_positioner_run(positioner);
    }
}
