target = mandelbrot.c

program:
	arm-none-eabi-gcc crt0.s $(target) -mcpu=arm7tdmi -nostartfiles -Tlnkscript
	arm-none-eabi-objcopy -O binary a.out a.gba
	./ht.pl -cl a.gba

clean:
	trash-put a.out
