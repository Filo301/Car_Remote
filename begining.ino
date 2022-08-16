#define LED_PIN 8
#define BUTTON_PIN 7
#define BREAKE 6

byte lastButtonState = LOW;
byte ledState = HIGH;
bool engine = false;
byte state = 0;
byte buttonState = digitalRead(BUTTON_PIN);

unsigned long debounceDuration = 30; // millis
unsigned long lastTimeButtonStateChanged = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  digitalRead(BUTTON_PIN);
}

void loop() {
  if (millis() - lastTimeButtonStateChanged > debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW) {
        ledState = (ledState == HIGH) ? LOW: HIGH;
                digitalWrite(LED_PIN, ledState);

        if ((state == 2) && (engine == false)) {
          state = 0;
        }
        else {
          state = state +1;
        }
      }
    }
    if (engine == true)
    {
      digitalWrite(10, HIGH);
    }else if (engine == false){
      digitalWrite(10, LOW);
    }
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
     if ((engine == false) && (digitalRead(BREAKE) == HIGH) && (buttonState != lastButtonState)) {
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      delay(1300);
      digitalWrite(13, HIGH);
      delay(900);
      digitalWrite(13, LOW);
      engine = true;
      state = 2;
    }
  else if ((engine == true) && (digitalRead(BREAKE) == HIGH) && (buttonState != lastButtonState)) {
      
      engine = false;
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      state = 0;
      delay(200);
  }  
      else {};
    
}

