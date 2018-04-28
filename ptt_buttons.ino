// Set Key values
#define KEY_LEFT_CTRL  0x01
#define KEY_BUTTON_A 0x2F
#define KEY_BUTTON_B 0x30

// Map buttons to Pins
#define PIN_BUTTON_MODIFIER 2
#define PIN_BUTTON_A 7
#define PIN_BUTTON_B 8

uint8_t defaultValue = 0;

uint8_t previousButtonState[8] = { 0 };  /* Keyboard report buffer */
uint8_t readState[8] = { 0 }; /* Button read state */

unsigned long debounceDelay = 100;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUTTON_MODIFIER, INPUT);
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);
}

void loop() {
  // read the Button States:
  GetButtonState();

  bool stateHasChanged = ButtonStateChanged(previousButtonState, readState);
  // Check if the button states have changed and send new keypresses if true
  if (stateHasChanged) {

    // Send keypress
    Serial.write(readState, 8);

    // Set Previous state to current readState
    UpdatePreviousState(previousButtonState, readState);

    delay(debounceDelay);
  }
}

void UpdatePreviousState(uint8_t *previousState, uint8_t *currentState) {
  int n;
  int arrayLength = 4;

  // Set each member of the previous state array to the current state value
  for (n = 0; n < arrayLength ; n++) {
    previousState[n] = currentState[n];
  }
}

boolean ButtonStateChanged(uint8_t *a, uint8_t *b) {
  int n;
  int arrayLength = 4;
  
  // test each element to be the same. if not, return true
  for (n = 0; n < arrayLength ; n++) {
    if (a[n] != b[n]){
      //Serial.print("State updated at: ");
      //Serial.print(n);
      //Serial.print("   ");
      //Serial.print(a[n]);
      return true;
    }   
  }
  //ok, if we have not returned yet, they are equal so we want to return false :)
  return false;
}

void GetButtonState() {

  // Read current state from button pins
  int buttonStateModifier = digitalRead(PIN_BUTTON_MODIFIER);
  int buttonStateA = digitalRead(PIN_BUTTON_A);
  int buttonStateB = digitalRead(PIN_BUTTON_B);

  //Set Modifier Button
  if (buttonStateModifier == HIGH) {
    readState[0] = KEY_LEFT_CTRL;
  }
  if (buttonStateModifier == LOW) {
    readState[0] = defaultValue;
  }

  //Set Button A value
  if (buttonStateA == HIGH) {
    readState[2] = KEY_BUTTON_A;
  }
  if (buttonStateA == LOW) {
    readState[2] = defaultValue;
  }

  //Set Button B value
  if (buttonStateB == HIGH) {
    readState[3] = KEY_BUTTON_B;
  }
  if (buttonStateB == LOW) {
    readState[3] = defaultValue;
  }
}
