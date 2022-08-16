// constants won't change. They're used here to set pin numbers:
const int buttonPin = 7;    // the number of the pushbutton pin
const int ledPin = 8;      // the number of the LED pin
const int breake = 6;

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState = HIGH;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
bool engine = false;
byte state = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(breake, INPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW
      if (buttonState == LOW) {
        ledState = !ledState;
         if ((state == 2) && (engine == false)) {
          state = 0;
        }
        else if (digitalRead(breake) == LOW) {
          state = state +1;
        }
      }
    }
  

  // set the LED:
  digitalWrite(ledPin, ledState);
  if (engine == true) {
    digitalWrite(9, HIGH);
  }else if (engine == false) {
    digitalWrite(9, LOW);
  }
   // lastButtonState = reading;


        }
   if (state == 0) {
   // digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    engine = false;
  } else if (state == 1) {
    digitalWrite(11, HIGH);

  } else if (state == 2) {
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
  }
     if ((engine == true) && (digitalRead(breake) == HIGH) && (buttonState == LOW ) && (lastButtonState != buttonState) ) {
      
      
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      engine = false;
      state = 0;
      reading = digitalRead(buttonPin);
      delay(3000);
      reading = digitalRead(buttonPin);
  }  
  else if ((engine == false) && (digitalRead(breake) == HIGH) && (buttonState == LOW ) && (lastButtonState != buttonState)) {
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      engine = true;
      delay(1300);
      digitalWrite(13, HIGH);
      delay(900);
      digitalWrite(13, LOW);
      engine = true;
      state = 2;
      reading = digitalRead(buttonPin);
    }
      else {};
      // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
