//#include <pitches.h>
#include "IRremote.h"

#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
int notes[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6};
int duration = 500;  // tone duration
int buzzerPin = 8; // buzzer pin (woah)
int note = 0;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes

{
  switch (results.value)

  {
    case 0xFFA25D: Serial.println("POWER"); break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE");    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");    break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");    break;
    case 0xFF6897: Serial.println("1");
      note = 0; break;
    case 0xFF9867: Serial.println("2");
      note = 1; break;
    case 0xFFB04F: Serial.println("3");
      note = 2; break;
    case 0xFF30CF: Serial.println("4");
      note = 3; break;
    case 0xFF18E7: Serial.println("5");
      note = 4; break;
    case 0xFF7A85: Serial.println("6");
      note = 5; break;
    case 0xFF10EF: Serial.println("7");
      note = 6; break;
    case 0xFF38C7: Serial.println("8");
      note = 7; break;
    case 0xFF5AA5: Serial.println("9");
      note = 8; break;
    case 0xFF42BD: Serial.println("*");
      note = 9; break;
    case 0xFF4AB5: Serial.println("0");
      note = 10; break;
    case 0xFF52AD: Serial.println("#");
      note = 11;  break;
    case 0xFFFFFFFF: Serial.println(" REPEAT"); break;

    default:
      Serial.println(" other button   ");

  }// End Case


  delay(500); // Do not get immediate repeat


} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) {// have we received an IR signal?
    translateIR();
    noTone(buzzerPin);
    tone(buzzerPin, notes[note], duration);
    irrecv.resume(); // receive the next value
  }
}/* --(end main loop )-- */
