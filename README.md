Bare metal experiments on the ASUS Tinkerboard.
Purpose: To initialize ddr, load test code from sd card to ddr and run test code from ddr.

Cross compiler used : arm-none-eabi-gcc
The following 11 tests are included: ( see below for tests summary )
1. uart test
2. led test
3. button test
4. pwm led test
5. i2c lcd test
6. tongsong
7. servo
8. spi oled test
9. ddr test
a. mmc test
b. dmac test

-------------------------------------------------------------------
To compile and flash to sd card:
cd tinker-baremetal-ddr
make clean
make ddrboot
make test
plugin a formated sd card to PC ( see below to format sd card )
make burn_sdcard
plugin the sd card to ASUS Tinkerboard.
Connect Tinkerboard gpio Pin 37 to serial USB cable TX.
Connect Tinkerboard gpio pin 36 to serial USB cable RX. 
Connect Tinkerboard gpio pin 39 to serial USB cable ground. 
Type "script ~/outputfile.txt" on PC.
Plugin serial USB cable to PC.
Type "sudo screen /dev/ttyUSB0 115200" on PC.
Power on the Tinkerboard.
It should display the test menu with 8 test items on PC.
After tests done, hit q to exit tests.
Power off the Tinkerboard.
Unplug serial USB cable from PC.
Type "exit" on PC.

-------------------------------------------------------------------------
To format sd card using PC:
plugin sd card to PC.
sudo dd if=/dev/zero of=/dev/mmcblk0 bs=1M count=1024 conv=notrunc,fsync
sudo fdisk /dev/mmcblk0 <<EOF
o
n
p
1
8192
139263
n
p
2
139264

t
1
c
t
2
83
a
1
w
q
EOF
sync
eject sd card. 
Plugin sd card to PC again.
sudo fdisk -l /dev/mmcblk0
sudo mkfs.vfat -i 4C892DED /dev/mmcblk0p1
sudo mkfs.ext4 /dev/mmcblk0p2
sync
eject sd card.

-----------------------------------------------------------------------
Here are the summary of the tests: ( see tinker_gpio.png )
These tests used Seeed Grove  starter kit LED, button, buzzer, Grove-LCD RGB Backlight V3.0 JHD1313M2, Analog Servo and Adafruit SSD1306 128x32 SPI OLED Display.
1. uart test. 
   This test is to test uart tx and rx.
   Connect gpio pin 37 to serial USB cable TX.
   Connect gpio pin 36 to serial USB cable RX.
   Connect gpio pin 39 to serial USB cable ground.
   Enter a sentence and hit return key. 
2. led test.
   This test will blink led 5 times. 
   Connect gpio pin 8 to led control. 
   Connect gpio pin 2 to led 5V. 
   Connect gpio pin 9 to led ground.
3. button test. 
   Connect gpio pin 8 to led control. 
   Connect gpio pin 2 to led 5V. 
   Connect gpio pin 9 to led ground. 
   Connect gpio pin 10 to button control.
   Connect gpio pin 4 to button 5V.
   Connect gpio pin 6 to button ground.
4. pwm led test.
   This test will dim led 10 times.
   Connect gpio pin 32 to led control.
   Connect gpio pin 2 to led 5V.
   Connect gpio pin 9 to led ground.
5. i2c lcd test.
   This test will change lcd backlight color for 5 cycles.
   Then it will display two sentences on lcd display.
   Connect gpio pin 3 to lcd display SDA.
   Connect gpio pin 5 to lcd display SCL.
   Connect gpio pin 2 to lcd display 5V.
   Connect gpio pin 9 to lcd display ground.
6. tongsong.
   This test will generate song using buzzer.
   Connect gpio pin 32 to buzzer control.
   Connect gpio pin 2 to buzzer 5V.
   Connect gpio pin 9 to buzzer ground. 
7. servo.
   This test will turn servo 90 degree - 180 degree - 90 degree - 0 degree etc.
   Connect gpio pin 32 to servo control.
   Connect gpio pin 2 to servo 5V.
   Connect gpio pin 9 to servo ground.
8. spi oled test.
   This test will show some ascii characters on the oled display.
   Connect gpio pin 18 to oled display DC.
   Connect gpio pin 24 to oled display CS.
   Connect gpio pin 19 to oled display TX.
   Connect gpio pin 23 to oled display CLK.
   Connect gpio pin 1 to oled display 3.3V.
   Connect gpio pin 9 to oled display ground.
9. ddr test.
   This test will writing random data to ddr address from 0x20000 to 0x7ffffff
   Then read ddr address from 0x20000 to 0x7ffffff compare to expected data.
   It will stop when any data mismatch.
a. mmc test.
   This test will read sd card lba 8192.
   Then erase 4MB from lba 6275072 to 6283263.
   Then read sd card lba 6283260.
   Then write incremental data to sd card lba 6283260.
   Then read data from sd card lba 6283260.
b. dmac test.
   This test will dma from sram address 0xff704000 to ddr address 0x10000000 for 16 KB.
   Then dma from ddr address 0x10000000 to ddr address 0x20000000 for 16 KB.

-----------------------------------------------------------------------------
Download compiler from :
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
select gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 to download
see ~/gcc-arm-none-eabi-9-2020-q2-update/share/gcc-arm-none-eabi/samples/readme.txt

use ~/gcc-arm-none-eabi-9-2020-q2-update/share/gcc-arm-none-eabi/samples/ldscripts/gcc.ld

