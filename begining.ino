// constants won't change. They're used here to set pin numbers:
const int buttonPin = 7;    // the number of the pushbutton pin
const int ledPin = 8;      // the number of the LED pin
const int brake = 6;
const int one = 11;
const int sec = 12;
const int starter = 13;
const int oil_pressure = 2;
const int door_sense = 4;
const int door_lock = 9;
const int handbrake = 5;
const int gear_neutral = 3;
const int voltage = A0;

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState = HIGH;             // the current reading from the input pin
int remoteState = HIGH;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
int lastRemoteState = HIGH;   // the previous reading from the input pin
bool engine_running = false;
bool engine_start_allowed = true;
bool oil_pressure_requied = false;
bool voltage_requied = false;
bool handbrake_requied = true;
bool neutral_gear_requied = false;
bool door_open = true;
bool remote_start_allowed = true;
bool remote_started = false;
bool remote_stop_allowed = false;
bool timeron = false;
byte remote_count = 0;
byte remote_starts = 3;
byte voltage_s = 12;
byte voltage_r = 13;
byte remote = 0;
byte state = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long remoteLastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long remoteDebounceDelay = 25;    // the debounce time; increase if the output flickers
int acc = 1500;
int start = 1200;
int lock = 500;
int waiting = 5000;
int remote_wait = 2000;
int remote_acc = 30000;
unsigned long timer = 0;
unsigned long time_now = 0;
//unsigned long time_now = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(brake, INPUT);
  pinMode(oil_pressure, INPUT_PULLUP);
  pinMode(door_sense, INPUT_PULLUP);
  pinMode(door_lock, OUTPUT);
  pinMode(handbrake, INPUT_PULLUP);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  int readingdoor = digitalRead(door_sense);
   time_now = millis();

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
       // ledState = !ledState;
         if ((state >= 2) && (engine_running == false)) {
          state = 0;
        }
        else if (digitalRead(brake) == LOW) {
          state = state +1;
        }
      }
    }




  readingdoor = digitalRead(door_sense);

    // If the switch changed, due to noise or pressing:
  if (readingdoor != lastRemoteState) {
    // reset the debouncing timer
    remoteLastDebounceTime = millis();
  }

  if ((millis() - remoteLastDebounceTime) > remoteDebounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingdoor != remoteState) {
      remoteState = readingdoor;

      // only toggle the LED if the new button state is LOW
      if ((remoteState == LOW) || (remoteState != lastRemoteState)) {
          remote = remote +1;
      }
     // if (remote == 2) {digitalWrite(10, HIGH);}
    }
  }
  if ((remote != 0) && (timeron == false)){
    timer = millis();
    timeron = true;
  }
    while ((timeron == true) && (millis() >= timer + waiting)){
      remote = 0;
      timeron = false;
    }
    if (timeron == true){
      digitalWrite(10, HIGH);
    }
      else {digitalWrite(10, LOW);
      }
    
  if (digitalRead(brake) == HIGH){
    remote_stop_allowed = false;
  }


  // set the LED:
  digitalWrite(ledPin, ledState);
  if (engine_running == true) {
    digitalWrite(9, HIGH);
  }else if (engine_running == false) {
    digitalWrite(9, LOW);
  }
        }

        if ((digitalRead(oil_pressure) == LOW) && (oil_pressure_requied == true)){
          engine_start_allowed = false;
        }

if ((handbrake_requied == true) && (handbrake == LOW) && (neutral_gear_requied == true) && (gear_neutral == HIGH))
{
  remote_start_allowed = true;
}
else if ((handbrake_requied == false) && (neutral_gear_requied == true) && (gear_neutral == HIGH))
{
  remote_start_allowed = true;
}
else if ((handbrake_requied == true) && (handbrake == LOW) && (neutral_gear_requied = false))
{
  remote_start_allowed = true;
}
else
{
  remote_start_allowed = false;
}

   if (state == 0) {
   // digitalWrite(10, HIGH);
    digitalWrite(one, LOW);
    digitalWrite(sec, LOW);
    engine_running = false;
  } else if (state == 1) {
    digitalWrite(one, HIGH);

  } else if ((state == 2) && (remote_started == false)) {
    digitalWrite(one, HIGH);
    digitalWrite(sec, HIGH);
  }else if ((state == 2) && (remote_started == true) && (engine_running == true)) {
    digitalWrite(one, HIGH);
    digitalWrite(sec, HIGH);
  }else if ((state == 2) && (remote_started == true) && (engine_running == false)) {
    time_now = millis();
    while (millis() <= time_now + remote_acc ){
             if (digitalRead(door_sense) != remoteState) {
             remoteState = digitalRead(door_sense);
             if ((remoteState == LOW)) {
             remote = remote +1;
            }
           } 
    digitalWrite(one, HIGH);
    digitalWrite(sec, HIGH);
    }

    state = 0;

  }
     if ((engine_running == true) && (digitalRead(brake) == HIGH) && (buttonState == LOW ) && (lastButtonState != buttonState) ) {
      
      time_now = millis();
    digitalWrite(one, HIGH);
    digitalWrite(sec, HIGH);
      engine_running = false;
      state = 0;
      //reading = digitalRead(buttonPin);
       //while(millis() < time_now + acc + start);
      delay(800);
      remote = 0;
        //while(millis() < lastDebounceTime + start)
      reading = digitalRead(buttonPin);
      buttonState = HIGH;
  }  
  else if ((engine_running == false) && (engine_start_allowed == true) && (digitalRead(brake) == HIGH) && (buttonState == buttonState ) && (lastButtonState != buttonState)) {
     time_now = millis();
    digitalWrite(one, HIGH);
    digitalWrite(sec, HIGH);
       while(millis() < time_now + acc) {ledState = !ledState;}
      engine_running = true;
       while ((digitalRead(oil_pressure) == HIGH) && ((millis() < time_now + acc + start) || (digitalRead(buttonPin) == LOW))){ //wait approx. [period] ms
      digitalWrite(13, HIGH);
       }
      //if (digitalRead(2)  == LOW){
       // while(millis() < time_now + acc + start)
        delay(100);
      digitalWrite(13, LOW);
     // }
     // else {
        //(while(millis() < time_now + acc + start));
     //  delay(2000);
    //  digitalWrite(13, LOW);
//  };
      remote_stop_allowed = false;
      engine_running = true;
      state = 2;
      remote = 0;
      buttonState = HIGH;
     // reading = digitalRead(buttonPin);
    }



  if ((engine_running == false) && (remote == 2)) {
     

        state = 2;
        remote_started = true;

   }




   if ((engine_running == false) && (remote == 3)) {
     time_now = millis();
      while(millis() < time_now + lock) {
        digitalWrite(door_lock, HIGH);
         if (digitalRead(door_sense) != remoteState) {
           remoteState = digitalRead(door_sense);
           }
          }
        digitalWrite(door_lock, LOW);
        door_open = false;
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
         while(millis() < time_now + lock + remote_wait) {
             if (digitalRead(door_sense) != remoteState) {
             remoteState = digitalRead(door_sense);
             if ((remoteState == LOW)) {
             remote = remote +1;
            }
           }               
          }

     if ((remote == 3)) {
       while (remote_count < remote_starts){
         // analogRead(voltage) = voltage_s
           time_now = millis();
           digitalWrite(11, HIGH);
           digitalWrite(12, HIGH);
            while (millis() < time_now + acc){}

             while ((engine_start_allowed == true) && ((millis() < time_now + acc + start))){ //wait approx. [period] ms
             digitalWrite(13, HIGH);
             }
           delay(100);
           digitalWrite(13, LOW);
           remote_count = remote_count +1;
           while (millis() < time_now + start + acc *2) {
          //   analogRead(voltage) = voltage_r;
               if (((digitalRead(oil_pressure) == LOW) && (oil_pressure_requied == true)) || ((voltage_s - voltage_r > 1) && (voltage_requied == true)) || ((oil_pressure_requied == false) && (voltage_requied == false))){
                engine_start_allowed = false;
               }
           }
           if (engine_start_allowed == true){
           digitalWrite(11, LOW);
           digitalWrite(12, LOW);
             while (millis() < time_now + start + remote_wait *2){
                }
           }
       }
     }
      //if (digitalRead(2)  == LOW){
       // while(millis() < time_now + acc + start)
    
      
     // else {
        //(while(millis() < time_now + acc + start));
     //  delay(2000);
    //  digitalWrite(13, LOW);
//  };
      if (digitalRead(oil_pressure) == LOW){
        engine_running = true;
      }
     
      state = 2;
      remote_started = true;
      remote_stop_allowed = true;
      remote = 0;
      timeron = false;
      delay(100);
     // reading = digitalRead(buttonPin);
    }
     if ((engine_running == true) && (door_open == false) && (remote == 3 ) && (remote_started == true) && (remote_stop_allowed == true)) {
      
      //time_now = millis();
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      engine_running = false;
      state = 0;
      remote = 0;
      //remote_started = true;
      timeron = false;


      //reading = digitalRead(buttonPin);
       //while(millis() < time_now + acc + start);
      delay(300);
        //while(millis() < lastDebounceTime + start)
      //reading = digitalRead(buttonPin);
      //buttonState = HIGH;
      
  }  
      // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  lastRemoteState = readingdoor;
}
 
