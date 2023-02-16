# dataLogger

## NOTE: The [SparkFun Qwiic Alphanumeric Display](https://www.sparkfun.com/products/18566) uses 3.3V and not the 5V from the UNO! Please use a level-shifter or a Pi Pico (or equivalent) when using this specific display.


## Introduction
This repository contains a series of coding examples which support developing a simple data logger. A data logger is a combination of hardware and software which gathers data, saves it and may also display the data during collection. 

In this example, we'll be collecting data from an *analog* pin also known as an analog-to-digital converter (ADC) pin. The *ADC* will take an input voltage from 0-5V and will convert it to 0-1023, with 0 representing 0V and 1023 representing 5V. As the converter uses 10 bits or 2 to the 10th power (1024), this *ADC* is known as a *10-bit ADC*. To convert from *ADC* value to a voltage, we multiply the value by 5V/1024, this is known as the *conversion factor*.

The examples are:
a. **test** - demonstrate all aspects of the programming environment are working
b. **analogRead** - demonstrate how to capture and display *ADC* values
c. **analogSave** - demonstrate once the values have been captured, store in EEPROM memory to retain on power off
d. **eepromRead** - re-display the values which have been stored in EEPROM
e. **dataLogger** - simple data logger which resolves *analogSave* flaw
f. **dataLogger_wANdisplay** - enhancement of *dataLogger*, adding an alphanumeric display to the Uno to display status and captured data
**Note:** *The folders and filenames have the example letter prepended to them to make it easy to use them in order.*

## Installation (If new to GitHub)
1. Click on down arrow in the green "*<> Code*" button in the upper right corner of this page.
2. Make sure you are on the tab "*Local*".
3. Click on "**Download ZIP**"
4. Once downloaded, double-click (macOS) (or right-click and select [Extract All](https://www.pcworld.com/article/394871/how-to-unzip-files-in-windows-10.html) (Windows)) to uncompress the ZIP file into a folder.
5. Move the folder where you want to keep it...*Documents*, *MyDocuments* etc
6. Open the Arduino program, the original version, **not the new 2.0 IDE**.
7. In Arduino, click on Open and navigate to *dataLogger -> Arduino -> Uno -> test*. Yes, this is the same code as the *blink* example in this Examples. It is great for testing your PC, Arduino, USB cable and Uno are all working together.
8. In Arduino, go to *Sketch -> Upload* to compile and upload *test* to the Uno. If everything is working correctly, you will see "*Done uploading*" in a green bar at the bottom of the Arduino window, an "avrdude done. Thank you." below the "*Done...*" message and your Uno will be blinking slowly.
![Toolbar](./images/upload.png)
9. Follow the directions in the *Sketches 1. test* below to confirm you are able to change the blink rate.

## Shortcuts
### Software (Arduino application)
![Toolbar](./images/Arduino_toolbar.png)

**1. Compile** - The *checkmark* icon in the upper lefthand corner of the Arduino window is useful for checking if your sketch will compile. If you are attempting to solve a series of compilation errors, its useful to fix the first error found then *compile* again, before attempting to *upload*. Repeating this "*fix first found error -> Compile*" until all errors are fixed is a useful tool, as compared to *upload*, which might upload your code, even though it still has errors. You may also use the keys *Cmd-R* (macOS) or *Ctrl-R* (Windows) to perform the *compile* command.

**2. Upload** - The arrow pointing to the right beside the *Compile* checkmark can be used to upload the code or you may use the keys *Cmd-U* (macOS) or *Ctrl-U* (Windows) to perform the *Upload* command. If a compilation error occurs when using the upload command, fix the error and re-compile or re-upload. Don't attempt to run a program which hasn't compiled successfully.

**3. Save** - The down arrow in the top of the Arduino window will save the file. This is important as you will want to save often so you don't lose your work. You may also use the keys *Cmd-S* (macOS) or *Ctrl-S* (Windows) to perform the *Save* command.

**4. Serial Monitor** - The magnifying glass icon in the upper right-hand corner of the Arduino window will open the serial monitor. This will allow you to view messages sent from the Arduino i.e. *Serial.print()*, as well as allow you to send text to the Uno i.e. *Serial.read()*, when programmed properly. Opening the Serial Monitor will also reset the Uno.

### Hardware (Arduino Uno)
**Reset** - There is a button right beside the USB connector on the [Uno](./docs/ArduinoUno_R3_Pinouts.png). If you wish to rerun your program with no changes to the code, simply press the *reset* button and the code will be rerun from the beginning. This is useful in situations where you might be running *analogRead*, for example, and you want to see new data.

## dataLogger Components
For this data logger, we'll use a potentiometer connected to a analog pin on the Uno. This will allow us to measure a range of voltages from 0V to 5V. The steps required for logging the voltages, are:
1. **Initialize** - setup the sensor and various parameters required
2. **Read** *ADC* pin - get the value from pin connected to the sensor
3. **Convert** - convert the *ADC* value to a voltage
4. **Save** - save the voltage along with a time stamp to *non-volatile memory*. Memory which is *volatile*, loses its contents when power is removed, while *non-volatile* memory will retain their contents.
5. **Display** - show the values on either a local display or via a USB cable to a PC, either during the recording of the values or after the fact.

## Sketches:
### 1. test
The ubiquitous "Hello World" program for the Uno to demonstrate the PC, Arduino IDE, USB cable, Uno are all connected and working properly. 

Do **NOT** depend on a blinking Uno to indicate that everything is working.  Change the delay value in the two *delay()* commands to ensure your changes are being written to the Uno. For example, the current value is *1000* which equates to *1 change per second*, change the values to *500* (*twice per second*) or even better change the value to *100* (*ten times per second*) as the blink rate change needs to be obvious.

Use this program as needed, to determine if everything is working properly. It is a great way to debug your *total system*, when *something just isn't working right*. The blink concept is also a great way to demonstrate a program's state, an example of which, you will see in a later program.

### 2. analogRead
Reads an *ADC* pin (*A0*) and displays the both the *ADC* value and the corresponding voltage using the serial port. Open the serial monitor via *Tools -> Serial Monitor* to view both values. 

To test, attach a potentiometer with the following wiring:

* left pin to 5V
* center pin to the *ADC* pin *A0*
* right pin to GND

Rotate the potentiometer and watch the values change on the screen. If the values, don't change, check your connections. Better yet, attach a digital multimeter (DMM) to pin A0 and compare the DMM readings to the Uno's values.

![Uno_pot_bb](./images/Uno_pot_bb.png)

### 3. analogSave
Builds on *analogRead* by adding the ability to save the values to the Uno memory called EEPROM. This memory retains its contents when power is removed, which means it is great for saving data read or captured. It allows you to power the Uno, capture the data then remove power from the Uno with the data retained. *analogSave* will fill all of the EEPROM memory (1kB or 1024 bytes on the Uno) with data and will stop once the memory is full. **Use the same hardware configuration as seen in *2. analogRead*.**

The format of the data saved is *unsigned int* and *float*.  This means there are two fields, first one is [unsigned int](https://reference.arduino.cc/reference/en/language/variables/data-types/unsignedint/) or integer, 2 bytes of data, which can represent an integer ranging from 0 to 65,535. The second is a [float](https://reference.arduino.cc/reference/en/language/variables/data-types/float/) or floating point number which consumes 4 bytes of memory and can represent numbers in scientific notation, ranging from -3.4028235E+38 to 3.4028235E+38. With *6 bytes per capture*, the Uno will fill up the memory with 170 *captures*.

### 4. eepromRead
Reads the data stored in EEPROM and displays via the serial monitor. The best way to use this program is to use it in conjunction with the *analogSave* program. Once *analogSave* has captured the data and has displayed *Out of memory*, you may upload the *eepromRead* program to re-display the data *analogSave* captured. 

**NOTE:**
This program and the *analogSave* program may act as a rudimentary data logger, however, this approach has a fatal flaw. *analogSave* will automatically begin saving data (or overwriting the current data), once reset or powered on. Which means, if we remove power from the Uno, we won't have sufficient time to upload the *eepromRead* before *analogSave* begins to overwrite our data. See *dataLogger* for a better solution to *analogSave*.

### 5. dataLogger
A simple data logger which will wait for a specified amount of time (*start_time*), blinking the built-in LED. Once *start_time* has elapsed, it will begin to capture data into the EEPROM until it has filled memory. Power can be removed and the Uno will retain the data. When power is restored, there will be *start_time* amount of time to upload *eepromREAD* to display the data. To test continue to use potentiometer attached to pin A0 and dial up and down to ensure values are being recorded properly. **Use the same hardware configuration as seen in *2. analogRead*.**
#### dataLogger embedded functions:
```C
// read: get the time and the ADC value
void read();

// convert: convert ADC data to voltage
void convert();

// save:  save converted value and time stamp to non-volatile memory
void save();

// display: show values
void display();

// determine if memory is full, if so stop program
bool end();

// blink: delay for n seconds, blinking n/2 times per second
void blink(unsigned int seconds, unsigned int times);

// "stop" the uC by using an empty infinite loop, use to exit void loop()
void stop();
```

### 6. dataLogger_wANdisplay
Adds a local alphanumeric display (AND) to the dataLogger program. Removes the blink method and displays status and recorded values on AND. Complete instructions for the [SparkFun Qwiic Alphanumeric Display](https://www.sparkfun.com/products/18566) are at [SparkFun Qwiic Alphanumeric Display Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-qwiic-alphanumeric-display-hookup-guide#resources-and-going-further). 

The connections on the [Uno](./docs/ArduinoUno_R3_Pinouts.png) are (connect via QWIC connector to pin cable):

* SDA to pin SDA (above AREF)
* SCLK to pin SCL (above SDA)
* 5V to 5V
* GND to GND

To test continue to use potentiometer attached to pin A0 and dial up and down to ensure values are being recorded properly.

![Uno_pot_bb](./images/Uno_pot_AN_bb.png)