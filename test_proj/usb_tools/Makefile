
all:usbtest usbecho

usbtest: usbtest.c
	gcc -I/usr/local/include/libusb-1.0 -L/usr/local/lib usbtest.c -o usbtest -lusb-1.0

usbecho: usbecho.c
	gcc -I/usr/local/include/libusb-1.0 -L/usr/local/lib usbecho.c -o usbecho -lusb-1.0


clean:
	rm -fr usbtest usbecho