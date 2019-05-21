//OVERALL CODE

//Tells you what level you are on
boolean lv1 = true;
boolean lv2 = false;
boolean lv3 = false;
boolean lv4 = false;
boolean lv5 = false;

//This will turn true once all levels are completed
boolean win = false;

//Pin for the buzzer
int buzzerPin = 52;



//Level 1 - Simon
//Declarations:
int simonbutton[] = {23, 25, 27, 29};
int simonled[] = {22, 24, 26, 28};
int simontones[] = {262, 330, 392, 494};
int simonroundsToWintones = 3;
int simonbuttonSequence[16];
int simonpressedButton = 4;
int simonroundCounter = 1;
long simonstartTime = 0;
long simontimeLimit = 2000;
boolean simongameStarted = false;

//Level 2 - Cyclone Game
int cycloneLed[] = {31, 33, 35, 37, 39, 41, 43, 45, 47};
int cycloneTime = 500;
boolean push = false;
int cycloneButtonPin = 49;
int presscnt = 0;



void setup() {

  //Level 1 - Simon
  pinMode(simonbutton[0], INPUT_PULLUP);
  pinMode(simonbutton[1], INPUT_PULLUP);
  pinMode(simonbutton[2], INPUT_PULLUP);
  pinMode(simonbutton[3], INPUT_PULLUP);
  pinMode(simonled[0], OUTPUT);
  pinMode(simonled[1], OUTPUT);
  pinMode(simonled[2], OUTPUT);
  pinMode(simonled[3], OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  //Level 2 - Cyclone
  pinMode(cycloneButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(cycloneLed[0], OUTPUT);
  pinMode(cycloneLed[1], OUTPUT);
  pinMode(cycloneLed[2], OUTPUT);
  pinMode(cycloneLed[3], OUTPUT);
  pinMode(cycloneLed[4], OUTPUT);
  pinMode(cycloneLed[5], OUTPUT);
  pinMode(cycloneLed[6], OUTPUT);
  pinMode(cycloneLed[7], OUTPUT);
  pinMode(cycloneLed[8], OUTPUT);
}



//----------FUNCTIONS------------

//Level 1 - Simon
void simonflashled (int simonledNumber) {
  digitalWrite(simonled[simonledNumber], HIGH);
  tone(buzzerPin, simontones[simonledNumber]);
}
void simonallledoff () {
  digitalWrite(simonled[0], LOW);
  digitalWrite(simonled[1], LOW);
  digitalWrite(simonled[2], LOW);
  digitalWrite(simonled[3], LOW);
  noTone(buzzerPin);
}
int simonbuttonCheck() {
  if (digitalRead(simonbutton[0]) == LOW) {
    return 0;
  } else if (digitalRead(simonbutton[1]) == LOW) {
    return 1;
  } else if (digitalRead(simonbutton[2]) == LOW) {
    return 2;
  } else if (digitalRead(simonbutton[3]) == LOW) {
    return 3;
  } else {
    return 4;
  }
}
void simonstartSequence() {
  randomSeed(analogRead(A0));
  for (int i = 0; i <= simonroundsToWintones; i++) {
    simonbuttonSequence[i] = round(random(0, 4));
  }
  for (int i = 0; i <= 3; i++) {
    tone(buzzerPin, simontones[i], 200); //play one of the 4 simontones
    digitalWrite(simonled[0], HIGH);
    digitalWrite(simonled[1], HIGH);
    digitalWrite(simonled[2], HIGH);
    digitalWrite(simonled[3], HIGH);
    delay(100);
    digitalWrite(simonled[0], LOW);
    digitalWrite(simonled[1], LOW);
    digitalWrite(simonled[2], LOW);
    digitalWrite(simonled[3], LOW);
    delay(100);
  }
}
void simonwinSequence() {
  for (int j = 0; j <= 3; j++) {
    digitalWrite(simonled[j], HIGH);
  }
  tone(buzzerPin, 1318, 150);   //E6
  delay(175);
  tone(buzzerPin, 1567, 150);   //G6
  delay(175);
  tone(buzzerPin, 2637, 150);   //E7
  delay(175);
  tone(buzzerPin, 2093, 150);   //C7
  delay(175);
  tone(buzzerPin, 2349, 150);   //D7
  delay(175);
  tone(buzzerPin, 3135, 500);   //G7
  delay(500);
  /*                                    //testing commenting this out, remove/edit later
    do {
    simonpressedButton = simonbuttonCheck();
    } while (simonpressedButton > 3);
  */
  delay(100);
  simongameStarted = false;
  simonallledoff();
}
void simonloseSequence() {
  for (int j = 0; j <= 3; j++) {
    digitalWrite(simonled[j], HIGH);
  }
  tone(buzzerPin, 130, 250);   //E6
  delay(275);
  tone(buzzerPin, 73, 250);   //G6
  delay(275);
  tone(buzzerPin, 65, 150);   //E7
  delay(175);
  tone(buzzerPin, 98, 500);   //C7
  delay(500);
  do {
    simonpressedButton = simonbuttonCheck();
  } while (simonpressedButton > 3);
  delay(200);
  simongameStarted = false;
}



void loop() {
  if (lv1) {
    if (simongameStarted == false) {
      simonstartSequence();
      simonroundCounter = 0;
      delay(1500);
      simongameStarted = true;
    }
    for (int i = 0; i <= simonroundCounter; i++) {
      simonflashled(simonbuttonSequence[i]);
      delay(200);
      simonallledoff();
      delay(200);
    }
    for (int i = 0; i <= simonroundCounter; i++) {
      simonstartTime = millis();
      while (true) {
        simonpressedButton = simonbuttonCheck();
        if (simonpressedButton < 4) {
          simonflashled(simonpressedButton);
          if (simonpressedButton == simonbuttonSequence[i]) {
            delay(250);
            simonallledoff();
            break;
          } else {
            simonloseSequence();
            break;
          }
        } else {
          simonallledoff();
        }
        if (millis() - simonstartTime > simontimeLimit) {
          simonloseSequence();
          break;
        }
      }
    }
    simonroundCounter = simonroundCounter + 1;
    if (simonroundCounter >= simonroundsToWintones) {
      simonwinSequence();
      lv1 = false;
      lv2 = true;
    }
    delay(500);
  }
  if (lv2) {
    for (int flash = 0; flash < 9; flash++) {
      digitalWrite(cycloneLed[flash], HIGH);
      if (digitalRead(cycloneButtonPin) == LOW) {
        presscnt = flash;
        if (presscnt == 4) {
          tone(buzzerPin, 1318, 150);  //right beep
        }
        else
        {
          tone(buzzerPin, 1000, 150); //wrong beep
          cycloneTime += 50;

        }
        
        Serial.println("Button pushed");
      }
      delay(cycloneTime);  //This is the key command for the delay between the LEDs
      /*
        if (digitalRead(cycloneButtonPin) == LOW) {  //if the button to stop the LEDs is pressed: set the check variable to the current lit LED
        presscnt = flash;
        Serial.println("Button pushed");
        }
      */
      digitalWrite(cycloneLed[flash], LOW);
    }
  }
  if (presscnt == 4) {
    cycloneTime = cycloneTime * 2 / 3;
    Serial.println(cycloneTime);

    delay(150);
    presscnt = 0;
  }
  if (cycloneTime <= 200) {
    lv2 = false;
    lv3 = true;
  }
}

