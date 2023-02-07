// AnalogRead: Reads and displays the values/voltages on an an ADC pin

int ADCpin = A0;                   // set the input pin to be read
unsigned int ADCvalue = 0;         // variable to store the ADC value
unsigned int wait_ms = 1000;       // amount of time in ms to wait
const float conversion = 5.0/1024; // conversion constant for ADC to voltage 

// setup function for initializing uC, req'd by Arduino
void setup() 
{
  Serial.begin(115200);
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() 
{
    // read value from ADC pin
    ADCvalue = analogRead(ADCpin);

    // print both ADC value and voltage, separated by tabs (\t)
    Serial.print("ADC Value: \t");
    Serial.print(ADCvalue);
    Serial.print(" Voltage: \t");
    Serial.println(ADCvalue * conversion, 2);

    // wait before repeating read/print
    delay(wait_ms); 
}
