CMSIS_INCLUDES=../../archives/CMSIS/Include
SRCS=$(wildcard src/*.c)
SRCS+=$(wildcard src/*.s)
BIN=main.elf
$(BIN) : $(SRCS)
	arm-none-eabi-gcc -DSTM32F429_439xx $^ -Iinc -I$(CMSIS_INCLUDES) -TSTM32F429ZI_FLASH.ld -o $@ -ggdb3 -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -dD -lm
