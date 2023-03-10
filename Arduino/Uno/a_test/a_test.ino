// test: turns an LED on for one second, then off for one second, repeatedly
// why is it called test and not blink?
// Use it to test your complete system to ensure everything is working!

// setup function for initializing uC, req'd by Arduino
void setup() {
    // initialize digital pin LED_BUILTIN (pin 13) as an output
    pinMode(LED_BUILTIN, OUTPUT);
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
