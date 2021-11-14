# What is this?
It is an embedded serial bridge with monitor functionality

## What Is the problem?
In the age of USB, ethernet and wireless gizmos, the trusty RS232 is still a common way to interface PC to instrumentation in production environments.\
During the development of production test software, progress can be hindered by poorly written protocols, lackluster documentation and connection issues.
## My idea:
A serial bridge, with USB logger&monitor functionality. \
Said bridge is intended to be inserted between two serial devices and relay in real time any data being exchanged to a host terminal connected via USB (Virtual Com Port), all this while acting as a "cable" for the two serial devices.\
The data being sent to the host PC is formatted adding timestamps and a color code to differentiate the data direction.\
The bridge is controlled remotely by a set of serial commands via the VCP and locally by tactile switches.\
Activity on the serial channel is indicated by a set of leds and an onboard graphic LCD, that show various statistics about baud rate, activity time and data rate.\
It is equipped with onboard ROM memory as in a pinch it can be used as a standalone device.

## What will I need :
- A microcontroller, SAMD21J18A is a candidate as I have already the dev board;
- RS232 level shifters, probably MAX232;
- SPI Flash memory, one of the winbond line as I am already familiar with them;
- An LDO to convert the 5 volt from the USB into a 3.3V (the development board use the SPX3819R2-L/TR;
- Some sort of activity indicator, Leds for TX and RX and an LCD with 8080 parallel driver;
- Various jelly bean components (resistor, capacitor).
## Block diagram 
![Block diagram](Images/Uart%20bridge.png)
