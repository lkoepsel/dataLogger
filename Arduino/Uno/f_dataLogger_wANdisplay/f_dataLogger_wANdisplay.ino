// dataLogger_wAN_display: dataLogger w Alphanumberic display
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
HT16K33 AN_display;

/// global variables used in program
unsigned int address = 0;           // beginning address at which to store data
unsigned int ADCpin = A0;           // set the input pin (ADC) to be read
unsigned int ADCvalue = 0;          // variable to store the ADC value
float voltage = 0;                  // voltage conversion from ADC
const float conversion = 5.0/1024;  // conversion constant for ADC to voltage
unsigned int now;                   // time stamp for data
unsigned int start_time = 10;       // n seconds before logging data
unsigned int start_blinks = 10;     // n/2 blinks per second, indicate startup
unsigned int read_delay = 2;        // n seconds before logging data
unsigned int read_blinks = 2;       // n/2 blinks per second, indicate ADC read
String sNumber = "";                // string version of number for AN display

// alignRight: align right number for AN display
void alignRight(float number);

// blink: delay for n seconds, blinking n/2 times per second
void blink(unsigned int seconds, unsigned int times);

// convert: convert ADC data to voltage
void convert();

// displaySerial: show values on Serial port
void displaySerial();

// display: show values on Alphanumeric display
void displayAN();

// determine if memory is full, if so stop program
bool end();

// read: get the time and the ADC value
void read();

// save:  save converted value and time stamp to non-volatile memory
void save();

// "stop" the uC by using an empty infinite loop, use to exit void loop()
void stop();

// setup function for initializing uC, req'd by Arduino
// initialize serial/display, print a header for the data, delay start_time
void setup() 
{
    Serial.begin(115200);
    Wire.begin(); //Join I2C bus

    if (AN_display.begin() == false)
    {
      Serial.println("Device did not acknowledge! Freezing.");
      while (1);
    }

    // initialize digital pin LED_BUILTIN (pin 13) as an output
    pinMode(13, OUTPUT);

    
    // indicate startup and delay to allow user to upload a different program 
    AN_display.print("STRT");
    blink(start_time, start_blinks);
    Serial.println("Address\tTime\tData");
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() 
{
    read();
    convert();
    save();
    displaySerial();
    displayAN();
    if (end())
    {
        stop();
    }
}

// displayAN: right align number based on value, X 100 to remove decimal point
void displayAN()
{
    sNumber = String(voltage*100,0);
    if (voltage < 1.0)
    {
        sNumber = "  " + sNumber;
    }
    else if (voltage < 10.0)
    {
        sNumber = " " + sNumber;
    }
    AN_display.print(sNumber);
}

void blink(unsigned int seconds, unsigned int times)
{
    for (unsigned int i = 0; i < seconds; i++) 
    {
        for (unsigned int j = 0; j < times; j++) 
        {    
            digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000/times/2); // wait for a second, blinking 
            digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
            delay(1000/times/2); // wait for a second, blinking
        }
    }
}

void convert()
{
    voltage = ADCvalue * conversion;
}

void displaySerial()
{
    // print address, time and voltage
    // as address has incremented past orig location, reset for printing
    Serial.print(address - (sizeof(now) + sizeof(voltage)));
    Serial.print("\t");
    Serial.print(now);
    Serial.print("\t ");
    Serial.println(voltage);
}

bool end()
{
    // check if the next address exceeds EEPROM capacity, return true
    if (address >= EEPROM.length()) 
    {
        Serial.print("Address ");
        Serial.print(address);
        Serial.print(" will exceed memorysize of ");
        Serial.println(EEPROM.length());
        return true;
    }

    // if not, wait then return false
    blink(read_delay, read_blinks);
    return false;

}

void read()
{    // read the value from the ADC pin and get the elapsed time:
    ADCvalue = analogRead(ADCpin);
    now = millis();
}

void save()
{    
    EEPROM.put(address, now);
    address += sizeof(now);
    // store voltage and set the next available address
    EEPROM.put(address, voltage);
    address += sizeof(voltage);

}

void stop()
{
    while(1) {};
}

