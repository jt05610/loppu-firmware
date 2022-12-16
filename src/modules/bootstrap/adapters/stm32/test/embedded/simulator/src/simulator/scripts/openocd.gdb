target remote :3333

set print asm-demangle on

break unity_output_complete

load

stepi