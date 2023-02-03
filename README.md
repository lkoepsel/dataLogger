# dataLogger

## Introduction
This repository contains a series of coding examples which support developing a simple data logger. The examples are:
1. **blink** - demonstrate all aspects of the programming environment are working
2. **analogRead** - demonstrate how to capture and display analog values
3. **analogSave** - demonstrate once the values have been captured, store in EEPROM memory to retain on power off
4. **eepromRead** - re-display the values which have been stored in EEPROM
5. **dataLogger** - simple data logger which resolves *analogSave* flaw
6. **dataLogger_wANdisplay** - enhancement of *dataLogger*, adding an alphanumeric display to the Uno to display status and captured data

## Sketches:

### 1. blink
The ubiquitous "Hello World" program for the Uno to demonstrate the PC, Arduino IDE, USB cable, Uno are all connected and working properly. 

Do **NOT** depend on a blinking Uno to indicate that everything is working.  Change the delay value in the two *delay()* commands to ensure your changes are being written to the Uno. For example, the common value is *1000* which equates to *1 change per second*, change the values to *500* (*twice per second*) or even better change the value to *100* (*ten times per second*) as the blink rate change needs to be obvious.

Use this program as needed, to determine if everything is working properly. It is a great way to debug your *total system*, when *something just isn't working right*. The blink concept is also a great way to demonstrate a program's state, an example of which, you will see in a later program.

### 2. analogRead
Reads an analog pin (*A0*) and displays the values using the serial port. Open the serial monitor via *Tools -> Serial Monitor* to view the values. 

To test, attach a potentiometer with the following wiring:

* left pin to GND
* center pin to the analog pin *A0*
* right pin to 5V

Rotate the potentiometer and watch the values change on the screen. If the values, don't change, check your connections. 

### 3. analogSave
Builds on *analogRead* by adding the ability to save the values to the Uno memory called EEPROM. This memory retains its contents when power is removed, which means it is great for saving data read or captured. It allows you to power the Uno, capture the data then remove power from the Uno with the data retained. *analogSave* will fill all of the EEPROM memory (1kB or 1024 bytes on the Uno) with data and will stop once the memory is full.

The format of the data saved is *unsigned int* *unsigned int*.  This means there are two fields, each one, 16 bits of data, which can represent an integer ranging from 0 to 65,535. With *4 bytes per capture*, the Uno will fill up the memory with 254 *captures*. Note the printout shows the *captures* ranging from 0 to 252.

### 4. eepromRead
Reads the data stored in EEPROM and displays via the serial monitor. The best way to use this program is to use it in conjunction with the *analogSave* program. Once *analogSave* has captured the data and has displayed *Out of memory*, you may upload the *eepromRead* program to re-display the data *analogSave* captured. 

**NOTE:**
This program and the *analogSave* program may act as a rudimentary data logger, however, this approach has a fatal flaw. *analogSave* will automatically begin saving data (or overwriting the current data), once reset or powered on. Which means, if we remove power from the Uno, we won't have sufficient time to upload the *eepromRead* before *analogSave* begins to overwrite our data. See *dataLogger* for a better solution to *analogSave*.

### 5. dataLogger
A simple data logger which will wait for a specified amount of time (*start_time*), blinking the built-in LED. Once *start_time* has elapsed, it will begin to capture data into the EEPROM until it has filled memory. Power can be removed and the Uno will retain the data. When power is restored, there will be *start_time* amount of time to upload *eepromREAD* to display the data. To test continue to use potentiometer attached to pin A0 and dial up and down to ensure values are being recorded properly.
#### dataLogger embedded functions:
```C
// captureData: read analog pin, display and store values
void captureData();

// blink: delay for n seconds, blinking n/2 times per second
void blink(unsigned int seconds, unsigned int times);

// "stop" the uC by using an empty infinite loop, use to exit void loop()
void stop();
```

### 6. dataLogger_wANdisplay
Adds a local alphanumeric display (AND) to the dataLogger program. Removes the blink method and displays status and recorded values on AND. Complete instructions for the [SparkFun Qwiic Alphanumeric Display](https://www.sparkfun.com/products/18566) are at [SparkFun Qwiic Alphanumeric Display Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-qwiic-alphanumeric-display-hookup-guide#resources-and-going-further). 

The connections are (connect via QWIC connector to pin cable):

* SDA to pin SDA (above AREF)
* SCLK to pin SCL (above SDA)
* 5V to 5V
* GND to GND

To test continue to use potentiometer attached to pin A0 and dial up and down to ensure values are being recorded properly.

