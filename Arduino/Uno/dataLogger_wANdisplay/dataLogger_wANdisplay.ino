// dataLogger_wANdisplay: dataLogger w Alphanumberic display
// 10 second wait allows user to load new program onto Uno to read data
// AN Display will show STRT for startup delay or value while capturing data

// Add the funtions which control the EEPROM storage, I2C and AN Display
#include <EEPROM.h>
#include <Wire.h>
#include <SparkFun_Alphanumeric_Display.h>

//SparkFun Qwiic Alphanumeric Display - Green COM-18566
// https://learn.sparkfun.com/tutorials/sparkfun-qwiic-alphanumeric-display-hookup-guide
// Connect via QWIC connector to pin cable
// SDA to pin SDA (above AREF)
// SCLK to pin SCL (above SDA)
// 5V to 5V 
// GND to GND
HT16K33 display;

// global variables used in program
unsigned int address = 0;       // beginning address at which to store data
unsigned int sensorPin = A0;    // set the input pin to be read
unsigned int sensorValue = 0;   // variable to store the sensor value
unsigned int now;               // time stamp for data
unsigned int memorySize = EEPROM.length()/(sizeof(sensorValue) + sizeof(now));
unsigned int start_time = 10;   // n seconds before logging data
unsigned int capture_delay = 2; // n seconds before logging data
String sNumber = "";            // string version of number for AN display

// captureData: read analog pin, display and store values
void captureData();

// alignRight: align right number for AN display
void alignRight(unsigned int number);

// "stop" the uC by using an empty infinite loop, use to exit void loop()
void stop();

// setup function for initializing uC, req'd by Arduino
// initialize serial/display, print a header for the data, delay start_time
void setup() 
{
    Serial.begin(115200);
    Wire.begin(); //Join I2C bus

    if (display.begin() == false)
    {
      Serial.println("Device did not acknowledge! Freezing.");
      while (1);
    }

    // initialize digital pin LED_BUILTIN (pin 13) as an output
    pinMode(13, OUTPUT);

    
    // indicate startup and delay to allow user to upload a different program 
    display.print("STRT");
    delay(start_time*1000);
    Serial.println("Address\tTime\tData");
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() 
{
    captureData();
}

void captureData()
{
    // read the value from the sensor and get the elapsed time:
    sensorValue = analogRead(sensorPin);
    now = millis();

    // print address, store time at address then get next available address
    Serial.print(address);
    EEPROM.put(address, now);
    address += sizeof(now);

    // store sensor value and set the next available address
    EEPROM.put(address, sensorValue);
    address += sizeof(sensorValue);

    // print time and sensor value
    Serial.print("\t");
    Serial.print(now);
    Serial.print("\t ");
    Serial.println(sensorValue);
    alignRight(sensorValue);

    // check if the next address exceeds EEPROM capacity, if so, stop
    if (address >= memorySize) 
    {
        Serial.println("Out of memory");
        stop();
    }

    // if not, wait then continue to read and store values
    delay(capture_delay*1000);
}

// alignRight: right align number based on value
void alignRight(unsigned int number)
{
    sNumber = String(number);
    if (number < 10)
    {
        sNumber = "   " + sNumber;
    }
    else if (number < 100)
    {
        sNumber = "  " + sNumber;
    }
    else if (number < 1000)
    {
        sNumber = " " + sNumber;
    }
    else
    {
        ;
    }
    display.print(sNumber);
}

void stop()
{
    while(1) {};
}
