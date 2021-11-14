# What is this?
It is an embedded serial bridge with sniffer functionality

## What does it do?
In the age of USB, ethernet and wireless gizmos, the trusty RS232 is still a common way to interface PC to instrumentation in production enviroments.
During the development of production test software, progress can be halted by poorly written protocols, lackluster documentation and hardware connection failures.
My idea:
A serial bridge, with USB logger/sniffer functionality. 
Said device is intended to be inserted between two serial devices and relay any data being exchanged to a host terminal via USB Virtual Com Port, all this while acting as a "cable" between the two devices.
The data being sent to the terminal emulator is formatted adding timestamps and a way to differentiate data direction (eg: colors).
The device is controlled by a set of serial commands via VCP.

## What will I need :
	a microcontroller, SAMD21J18A is a candidate as I have already the dev board in my pile;
	RS232 level shifters, probably MAX232;
	SPI Flash memory, one of the winbond line as I am already familiar with them;
  An LDO to convert the 5 volt from the USB into a 3.3V (the development board use the SPX3819R2-L/TR;
	Some sort of activity indicator, Leds for TX and RX and an LCD with the last data activity;
  And jelly bean componenst (resistor, capacitor).
## Block diagram 
	![Uart bridge](https://user-images.githubusercontent.com/61431239/141692235-d6d9d671-0acf-49d5-98bb-6b82a8d552f0.png)
