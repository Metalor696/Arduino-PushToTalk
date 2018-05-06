// Set Modifier Key ints (can be combined)
#define KEY_LEFT_CTRL  1
#define KEY_LEFT_SHIFT 2
#define KEY_LEFT_ALT 4
#define KEY_RIGHT_CTRL  16
#define KEY_RIGHT_SHIFT 32
#define KEY_RIGHT_ALT 64

// Set Key values
#define KEY_LEFT_SQUARE 0x2F  // Left square bracket [
#define KEY_RIGHT_SQUARE 0x30  // Right square bracket ]
#define KEY_NUM_LOCK 0x53  // Num lock
#define KEY_F20 0x6F       // F20
#define KEY_F21 0x70       // F21
#define KEY_F22 0x71
#define KEY_F23 0x72
#define KEY_F24 0x73

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

  // test each element to be the same. if not, return true as state has changed
  for (n = 0; n < arrayLength ; n++) {
    if (a[n] != b[n]) {
      //Serial.print("State updated at: ");
      //Serial.print(n);
      //Serial.print("   ");
      //Serial.print(a[n]);
      return true;
    }
  }
  // If we have not returned yet, the arrays and button states are equal so we want to return false :)
  return false;
}

void GetButtonState() {

  // Read current state from button pins
  int buttonStateModifier = digitalRead(PIN_BUTTON_MODIFIER);
  int buttonStateA = digitalRead(PIN_BUTTON_A);
  int buttonStateB = digitalRead(PIN_BUTTON_B);

  //Set Modifier Value
  SetModifier(buttonStateModifier);

  //Set Button A value
  if (buttonStateA == HIGH) {
    readState[2] = KEY_F20;
  }
  if (buttonStateA == LOW) {
    readState[2] = defaultValue;
  }

  //Set Button B value
  if (buttonStateB == HIGH) {
    readState[3] = KEY_NUM_LOCK;
  }
  if (buttonStateB == LOW) {
    readState[3] = defaultValue;
  }
}

void SetModifier(int buttonStateModifier) {

  int modifierCombined = 0;

  if (buttonStateModifier == HIGH) {
    modifierCombined = KEY_RIGHT_CTRL;
  }
  // Set modifier array element to the required int value based on button states
  readState[0] = modifierCombined;
}
