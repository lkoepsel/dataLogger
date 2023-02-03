// AnalogRead: Reads and prints the values on an an analog pin

int sensorPin = A0;           // set the input pin to be read
unsigned int sensorValue = 0; // variable to store the sensor value
unsigned int wait_ms = 1000;  // amount of time in ms to wait

// setup function for initializing uC, req'd by Arduino
void setup() 
{
  Serial.begin(115200);
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() 
{
    // read the value from the sensor and print it:
    sensorValue = analogRead(sensorPin);
    Serial.print("Sensor Value: \t");
    Serial.println(sensorValue);

    // wait before repeating read/print
    delay(wait_ms); 
}
