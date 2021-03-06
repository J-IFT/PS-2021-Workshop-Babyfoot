#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 255;
int RScore = 0;
int BScore = 0;
String TXT;

const byte TRIGGER_PINB = 4; // Broche TRIGGER
const byte ECHO_PINB = 5;    // Broche ECHO


const byte TRIGGER_PINR = 2; // Broche TRIGGER
const byte ECHO_PINR = 3;    // Broche ECHO

const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
/* Vitesse du son dans l'air en mm/us */
;const float SOUND_SPEED = 340.0 / 1000;
float moyR;
float moyB;
const float distanceDif = 15;

// Define pin 10 for buzzer, you can use any other digital pins (Pin 0-13)
const int buzzer = 6;

// Change to 0.5 for a slower version of the song, 1.25 for a faster version
const float songSpeed = 1;

// Defining frequency of each music note
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
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

// Music notes of the song, 0 is a rest/pulse
//notes in the melody:
int melody[] = {
    //End of Repeat

    NOTE_C4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
   NOTE_C4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
      NOTE_C4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4,
      0, 
};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int noteDurations[] = {
        //End of Repeat

    2, 2, 4, 4, 4, 8, 4, 8, 4,
  4, 4, 4, 4, 4, 8, 4, 8, 4,
  4, 4, 4, 4, 4, 8, 4, 8, 4, 4, 4, 2,
  2,
};

    
    
void setup() {
  // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    Serial.begin(9600);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("Bleu   VS  Rouge");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(BScore);
    lcd.print("             ");
    lcd.print(RScore);

    /* Initialise les broches */
  pinMode(TRIGGER_PINB, OUTPUT);
  digitalWrite(TRIGGER_PINB, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PINB, INPUT);

   pinMode(TRIGGER_PINR, OUTPUT);
   digitalWrite(TRIGGER_PINR, LOW); // La broche TRIGGER doit être à LOW au repos
   pinMode(ECHO_PINR, INPUT);

}

void loop() {
    lcd.setCursor(0,0);
    lcd.print("Bleu   VS  Rouge");
    lcd.setCursor(0, 1);
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(BScore);
    lcd.print("              ");
    lcd.print(RScore);
    

    // Sensor Bleu
    digitalWrite(TRIGGER_PINB, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PINB,LOW);
  
    long measureB = pulseIn(ECHO_PINB,HIGH,MEASURE_TIMEOUT);
    float distance_mmB = measureB / 2.0 * SOUND_SPEED;

    // Sensor Rouge
    digitalWrite(TRIGGER_PINR, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PINR,LOW);
  
    long measureR = pulseIn(ECHO_PINR,HIGH,MEASURE_TIMEOUT);
    float distance_mmR = measureR / 2.0 * SOUND_SPEED;
    

    if(distance_mmB < 90)
    {
     RIncrease(); 
     Serial.print("R");
     Serial.println(RScore);
     
    }

    if(distance_mmR < 123)
    {
     BIncrease();
     Serial.print("B");
     Serial.println(BScore);
     
    }
    
    

    if((BScore == 9) || (RScore == 9))
    {
      if (BScore<RScore)
      {
        lcd.setCursor(0,0);
        lcd.print("Rouges Win !!!!!");
        lcd.setCursor(0, 1);
        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
        // print the number of seconds since reset:
        lcd.print("BLUE SUCKS BHOOOOOOOOO");
        RBlink();
        music();
      }
      else
      {
        lcd.setCursor(0,0);
        lcd.print("Blues Win !!!!!!");
        lcd.setCursor(0, 1);
        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
        // print the number of seconds since reset:
        lcd.print("RED SUCKS BHOOOOO");
        BBlink();
        music();
      }
      RScore = 0;
      BScore = 0;
    }
    

}

void music(){
  //iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {

    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     */
    int noteDuration = 1000/noteDurations[thisNote];
    tone(6, melody[thisNote],noteDuration);

    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(9); //stop the tone playing:
  }
  digitalWrite(6,LOW);
  
}

void RBlink(){
  for(int i=0; i<5; i = i+1)
  {
    lcd.setRGB(255, 0, 0);
    delay(500);
    lcd.setRGB(colorR, colorG, colorB);
    delay(1000);
  }
}

void BBlink(){
  for(int i=0; i<5; i = i+1)
  {
    lcd.setRGB(0, 0, 255);
    delay(500);
    lcd.setRGB(colorR, colorG, colorB);
    delay(1000);
  }
}
  

void RIncrease(){
  RScore += 1;
  lcd.setCursor(0,0);
  lcd.print("But Rouges !!!!!");
  lcd.setCursor(0, 1);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  lcd.print("Score Rouges :");
  lcd.print(RScore);
  lcd.print("  ");
  RBlink();
  
}

void BIncrease(){
  BScore += 1;
  lcd.setCursor(0,0);
  lcd.print("But Bleus !!!!!!");
  lcd.setCursor(0, 1);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  lcd.print("Score Bleus :");
  lcd.print(BScore);
  lcd.print("  ");
  BBlink();
  
}
