CROSS_COMPILE = arm-none-eabi-
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main
INCLUDE = -I.
CFLAGS  = -g -march=armv7-a -O1 -Wl,--build-id=none -nostdlib -fno-builtin $(INCLUDE)
LDSCRIPTS=-L. -T gcc.ld -lgcc
LFLAGS= $(LDSCRIPTS)
LDSCRIPTSDDR=-L. -T ddr.ld -lgcc
LFLAGSDDR= $(LDSCRIPTSDDR)

test: test.bin

test.bin: test.elf
	$(CROSS_COMPILE)objcopy -O binary $< $@
	$(CROSS_COMPILE)objdump -S $< > test.list

test.elf: start.S test.c uart.c printf.c pwm.c timer.c clock.c gpio.c i2c.c spi.c gic.c mmc.c
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ $(LFLAGSDDR) -o $@

ddrboot: ddrboot.img

ddrboot.img: ddrboot.bin
	mkimage -n rk3288 -T rksd -d $< $@

ddrboot.bin: ddrboot.elf
	$(CROSS_COMPILE)objcopy -O binary $< $@
	$(CROSS_COMPILE)objdump -S $< > ddrboot.list

ddrboot.elf: start.S ddrboot.c uart.c printf.c timer.c clock.c gic.c ddr.c mmc.c
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ $(LFLAGS) -o $@

.PHONY: burn_sdcard clean test ddrboot

burn_sdcard: test.bin ddrboot.img
	sudo dd if=ddrboot.img of=/dev/mmcblk0 seek=64 oflag=sync status=progress
	sudo dd if=test.bin of=/dev/mmcblk0 seek=128 oflag=sync status=progress

clean:
	rm -f *.img *.bin *.elf *.list
