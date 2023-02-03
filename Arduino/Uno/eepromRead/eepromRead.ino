// eepromRead: Reads the values in EEPROM based an AnalogSave.
// Values written to EEPROM will stay in the EEPROM when the board is
// turned off and may be retrieved later with this sketch

// Add the funtions which control the EEPROM storage
#include <EEPROM.h>

// global variables used in program
int address = 0;            // beginning address at which to store data
unsigned int data1 = 0;     // variable to store the first read data
unsigned int data2 = 0;     // variable to store the second read data
unsigned int wait_ms = 100; // amount of time in ms to wait
unsigned int now;           // time stamp for data
int memorySize = EEPROM.length()/(sizeof(data1) + sizeof(data2));

// function to use to "stop" the uC by using an infinite loop
void stop()
{
    while(1) {};
}

// setup function for initializing uC, req'd by Arduino
// initialize the serial port and print a header for the data
void setup() 
{
    Serial.begin(115200);
    Serial.println("Address\tData 1\tData 2");
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() {
    // print address, read first value, then advance to next address
    Serial.print(address);
    EEPROM.get(address, data1);
    address += sizeof(data1);

    // read second value then advance to next address
    EEPROM.get(address, data2);
    address += sizeof(data2);

    // print the two data values found
    Serial.print("\t");
    Serial.print(data1);
    Serial.print("\t ");
    Serial.println(data2);

    // check if the next address exceeds EEPROM capacity, if so, stop
    if (address >= memorySize) 
    {
        Serial.println("Out of memory");
        stop();
    }

    // if not, wait then continue to read and store values
    delay(wait_ms);
}
