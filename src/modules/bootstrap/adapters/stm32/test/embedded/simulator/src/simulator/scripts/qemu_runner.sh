qemu-system-arm -cpu cortex-m0 -M stm32vldiscovery -nographic \
                -device loader,file=/Users/jtaylor/CLionProjects/Injector/cmake-build-simulated/src/modules/bootstrap/adapters/stm32/test/embedded/serial/stm32_serial_tests.elf \
                -gdb tcp::1234 -S
