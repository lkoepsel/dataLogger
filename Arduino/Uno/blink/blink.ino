// blink: turns an LED on for one second, then off for one second, repeatedly

// setup function for initializing uC, req'd by Arduino
void setup() {
    // initialize digital pin LED_BUILTIN (pin 13) as an output
    pinMode(13, OUTPUT);
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
