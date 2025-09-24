int ledPin1= 13;  // LED connected to pin 13
int ledPin2 = 12; 
int ledPin3 = 8; 
void setup() {
   pinMode(ledPin1, OUTPUT); 
   pinMode(ledPin2, OUTPUT);
   pinMode(ledPin3, OUTPUT);    // Set pin 13 as output
   digitalWrite(ledPin1, HIGH); // Turn LED OFF
   digitalWrite(ledPin2, HIGH); // Turn LED OFF
   digitalWrite(ledPin3, HIGH);

}

void loop() {
  // Nothing needed, LED stays OFF
}
