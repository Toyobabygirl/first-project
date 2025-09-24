// LED outputs
int LED1 = 13;  // bit0 (LSB)
int LED2 = 12;  // bit1
int LED3 = 8;   // bit2 (MSB)

// Button inputs
int LSB = 7;
int MSB = 6;
int PLUS = 5;
int MINUS = 4;
int EQUAL = 3;

// States
enum State {INPUT_NUM1, INPUT_NUM2};
State currentState = INPUT_NUM1;

// Calculator variables
int num1;
int num2;
char operation = ' ';
int result = 0;
int LEDi[3]={13,12,8};
const int debounceDelay = 50;  
const int stepDelay = 500;      

void setup() {
  // LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Buttons 
  pinMode(LSB, INPUT_PULLUP);
  pinMode(MSB, INPUT_PULLUP);
  pinMode(PLUS, INPUT_PULLUP);
  pinMode(MINUS, INPUT_PULLUP);
  pinMode(EQUAL, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  switch (currentState) {
    case INPUT_NUM1:
      if (digitalRead(LSB) == LOW || digitalRead(MSB) == LOW) {
        delay(stepDelay);
        if (digitalRead(LSB) == LOW && digitalRead(MSB) == LOW) {
          num1 = 3;
        } else if (digitalRead(MSB) == LOW) {
          num1 = 2;
        } else if (digitalRead(LSB) == LOW) {
          num1 = 1;
        }
        
        Serial.print("Num1: ");
        Serial.println(num1);
      }

      if (digitalRead(PLUS) == LOW || digitalRead(MINUS) == LOW) {
        if (digitalRead(PLUS) == LOW) {
          operation = '+';
          Serial.println("+");
        }
        if (digitalRead(MINUS) == LOW) {
          operation = '-';
          Serial.println("-");
        }
        currentState = INPUT_NUM2;
        delay(stepDelay);
      }
      break;

    case INPUT_NUM2:
      if (digitalRead(LSB) == LOW || digitalRead(MSB) == LOW) {
        delay(stepDelay);
        if (digitalRead(LSB) == LOW && digitalRead(MSB) == LOW) {
          num2 = 3;
        } else if (digitalRead(MSB) == LOW) {
          num2 = 2;
        } else if (digitalRead(LSB) == LOW) {
          num2 = 1;
        }
        
        Serial.print("Num2: ");
        Serial.println(num2);
      }

      if (digitalRead(EQUAL) == LOW) {  // pressed
        if (operation == '+') {
          result = num1 + num2;
        } else if (operation == '-') {
          result = num1 - num2;
        }

        Serial.print("Result = ");
        Serial.println(result);

        // Show result on LEDs
        displayResult(result);

        // reset
        num1 = 0;
        num2 = 0;
        operation = ' ';
        currentState = INPUT_NUM1;
        delay(stepDelay);
      }
      break;
  }
}

// Display result in binary on LEDs
void displayResult(int result) {
  // limit result to -3..+3
  if (result > 3) result = 3;
  if (result < -3) result = -3;

  // clear LEDs briefly
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(200);

  // convert to 3-bit two’s complement
  int binary = result & 0b111;

  Serial.print("Binary : ");
  for (int i = 2; i >= 0; i--) {
    Serial.print(bitRead(binary, i));
  }
  Serial.println();

  // update LEDs
  digitalWrite(LED1, bitRead(binary, 0)); // LSB
  digitalWrite(LED2, bitRead(binary, 1)); // middle
  digitalWrite(LED3, bitRead(binary, 2)); // MSB
}
