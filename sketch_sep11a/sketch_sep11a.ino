

// LED outputs 
int LED1 = 13;  // bit0 (LSB)
int LED2 = 12;  // bit1
int LED3 = 11;  // bit2 (MSB)

// Button inputs
int LSB = 11;    
int MSB = 10;     
int PLUS = 9;    
int MINUS = 6;   
int EQUAL = 5;   

// States
enum State {INPUT_NUM1, INPUT_OP, INPUT_NUM2, INPUT_EQUAL};
State currentState = INPUT_NUM1;

// Calculator variables
int num1 = 0;
int num2 = 0;
char operation = ' ';
int result = 0;

const int buttonDelay = 1000;

void setup() {
  // LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Buttons 
  pinMode(LSB, INPUT);
  pinMode(MSB, INPUT);
  pinMode(PLUS, INPUT);
  pinMode(MINUS, INPUT);
  pinMode(EQUAL, INPUT);

  Serial.begin(9600);
}

void loop() {
  switch (currentState)  {

    case INPUT_NUM1:
      if (readNumber(num1)) {
        Serial.print("First number = ");
        Serial.println(num1);
        currentState = INPUT_OP;
        delay(buttonDelay);
      }
      break;

    case INPUT_OP:
      if (digitalRead(PLUS) == HIGH) {
        operation = '+';
        Serial.println("Operator = +");
        currentState = INPUT_NUM2;
        delay(buttonDelay);
      } 
      else if (digitalRead(MINUS) == HIGH) {
        operation = '-';
        Serial.println("Operator = -");
        currentState = INPUT_NUM2;
        delay(buttonDelay);
      }
      else
      break;

    case INPUT_NUM2:
      if (readNumber(num2)) {
        Serial.print("Second number = ");
        Serial.println(num2);
        currentState = INPUT_EQUAL;
        delay(buttonDelay);
      }
      break;

    case INPUT_EQUAL:
      if (digitalRead(EQUAL) == HIGH) {
        if (operation == '+') 
        result = num1 + num2;
        else if (operation == '-') 
        result = num1 - num2;

        Serial.print("Result = ");
        Serial.println(result);

        displayResult(result);

        // reset
        num1 = 0;
        num2 = 0;
        operation = ' ';
        currentState = INPUT_NUM1;
        delay(buttonDelay);
      }
      break;
  }
}


// bool readNumber(int &num) {
//   if (digitalRead(LSB) == HIGH && digitalRead(MSB) == LOW) {
//     num = 1; // 01
//     return true;
//   }
//   else if (digitalRead(MSB) == HIGH && digitalRead(LSB) == LOW) {
//     num = 2; // 10
//     return true;
//   }
//   else if (digitalRead(MSB) == LOW && digitalRead(LSB) == LOW) {
//     num = 1; // 11
//     return true;
//   }
//   else if (digitalRead(MSB) == HIGH && digitalRead(LSB) == HIGH) {
//     num = 0; // 00
//     return true;
//   }
//   return false;
// }

// // result display
// void displayResult(int value) {
//   int v = abs(value);

//   // blink all LEDs once if result negative
//   if (value < 1) {
//     digitalWrite(LED1, HIGH);
//     digitalWrite(LED2, HIGH);
//     digitalWrite(LED3, HIGH);
//     delay(400);
//     digitalWrite(LED1, LOW);
//     digitalWrite(LED2, LOW);
//     digitalWrite(LED3, LOW);
//     delay(200);
//   }

//   digitalWrite(LED1, bitRead(v, 0));
//   digitalWrite(LED2, bitRead(v, 1));
//   digitalWrite(LED3, bitRead(v, 2));
// }
