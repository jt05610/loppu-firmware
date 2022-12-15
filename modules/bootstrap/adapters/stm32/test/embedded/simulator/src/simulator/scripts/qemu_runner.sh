qemu-system-arm \
  -cpu cortex-m0 \
  -machine netduino2 \
  -nographic \
  -serial mon:stdio \
  -semihosting-config enable=on,target=native \
  -gdb tcp::3333 \
  -S \
  -kernel /Users/jtaylor/CLionProjects/Injector/cmake-build-simulated/modules/bootstrap/adapters/stm32/test/STM32Tests.elf \
