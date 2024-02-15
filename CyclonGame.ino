#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitch.h"
#include "melody.h"

#include "FastLED.h"  //FastLED.h Library Download
#define NUM_LEDS 48  //Total Number of LED
#define DATA_PIN 2   //Cyclone LED Strip D2
#define SCORE_PIN 6  //Level LED Strip D6
#define SCORE_LEDS 4
#define buzzer 8
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
CRGB leds[NUM_LEDS];
CRGB sleds[NUM_LEDS];

bool reachedEnd = false;
byte gameState = 0;
//byte ledSpeed = 0;
int period = 1000;
unsigned long time_now = 0;
byte Position = 0;
byte level = 0;

const byte ledSpeed[4] = {50, 40, 35, 20};

//Debounce
bool findRandom = false;
byte spot = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, SCORE_PIN, GRB>(sleds, SCORE_LEDS);
  // initialize the LCD
  lcd.begin(16, 2);

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();

  pinMode(4, INPUT_PULLUP);                                           //Push Button D4
  // lcd.print("Game Begins");
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("Reset");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (gameState == 0) {

    fill_rainbow(leds, NUM_LEDS, 0, 15); //2 = longer gradient strip
    fill_rainbow(sleds, SCORE_LEDS, 0, 7); //2 = longer gradient strip

    if (digitalRead(4) == LOW) {

      Position = 0;
      findRandom = true;
      pink_panther();
      
      String welmsg = "Welcome to Cyclone Arcade Led Chaser Game!!!";
      lcd.clear();
      scrolling_loop(welmsg);
      delay(500);
      for (byte i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(0, 0, 0);
        delay(40);
        FastLED.show();
      }

      for (byte i = 0; i < SCORE_LEDS; i++) {
        sleds[i].setRGB(0, 0, 0);
        delay(100);
        FastLED.show();
      }
      //pink_panther();
      gameState = 1;
    }
    FastLED.show();
  }
  if (gameState == 1) {
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("Level 1");
//    lcd.setCursor(0, 1);
//    lcd.print("Begins");
    period = ledSpeed[0];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(44) + 3;              //Total Cyclone LED - 4
        findRandom = false;
      }
      leds[spot - 1].setRGB(255, 140, 0);
      leds[spot].setRGB(0, 255, 0);
      leds[spot + 1].setRGB(255, 140, 0);
      sleds[0].setRGB(0, 0, 255);
      PlayGame(spot - 1, spot + 1);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      findRandom = false;
      if (Position > spot - 1 && Position < spot + 3) {
        level = gameState;
        gameState = 98;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Level 1");
        lcd.setCursor(0, 1);
        lcd.print("Completed");
        delay(100);
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 2) {
    //    period = 320;
//    lcd.setCursor(0, 0);
//    lcd.print("Level 2");
//    lcd.setCursor(0, 1);
//    lcd.print("Begins");
    period = ledSpeed[1];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(44) + 3;              //Total Cyclone LED - 4
        findRandom = false;
      }
      leds[spot - 1].setRGB(255, 140, 0);
      leds[spot].setRGB(0, 255, 0);
      leds[spot + 1].setRGB(255, 140, 0);
      sleds[1].setRGB(0, 0, 255);
      PlayGame(spot - 1, spot + 1);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (spot - 1 && Position < spot + 3) {
        level = gameState;
        gameState = 98;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Level 2");
        lcd.setCursor(0, 1);
        lcd.print("Completed");
        delay(100);
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Level 3");
    lcd.setCursor(0, 1);
    lcd.print("Begins");
    period = ledSpeed[2];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(44) + 3;              //Total Cyclone LED - 4
        findRandom = false;
      }
      leds[spot].setRGB(0, 255, 0);
      sleds[2].setRGB(0, 0, 255);
      PlayGame(spot, spot);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (Position == spot + 1) {
        level = gameState;
        gameState = 98;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Level 3");
        lcd.setCursor(0, 1);
        lcd.print("Completed");
        delay(100);

      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 4) {
//    lcd.setCursor(0, 0);
//    lcd.print("Level 1");
//    lcd.setCursor(0, 1);
//    lcd.print("Begins");
    period = ledSpeed[3];
    if (millis() > time_now + period) {
      time_now = millis();
      if (findRandom) {
        spot = random(44) + 3;              //Total Cyclone LED - 4
        findRandom = false;
      }
      leds[spot].setRGB(0, 255, 0);
      sleds[3].setRGB(0, 0, 255);
      PlayGame(spot, spot);
    }
    if (digitalRead(4) == LOW) {
      delay(300);
      if (Position == spot + 1) {
        level = gameState;
        gameState = 98;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Level 4");
        lcd.setCursor(0, 1);
        lcd.print("Completed");
        delay(100);
      } else {
        gameState = 99;
      }
    }
  }
  if (gameState == 98) {
    winner();
  }
  if (gameState == 99) {
    loser();
  }
}
void PlayGame(byte bound1, byte bound2) {
  leds[Position].setRGB(255, 0, 0);
  if (Position < bound1 + 1 || Position > bound2 + 1) {
    leds[Position - 1].setRGB(0, 0, 0);
  }
  FastLED.show();
  Position++;
  if (Position >= NUM_LEDS) {
    leds[Position - 1].setRGB(0, 0, 0);
    Position = 0;
  }
}

void winner() {
  winning_sound();
  lcd.clear();
  String win = "Wahh bete Moj krdi !!!";
  scrolling_loop(win);
  delay(400);
  for (byte i = 0; i < 3; i++) {
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds[j].setRGB(0, 255, 0);
    }
    FastLED.show();
    delay(500);
    clearLEDS();
    FastLED.show();
    delay(500);
  }
  findRandom = true;
  Position = 0;

  gameState = level + 1;
  if (gameState > 4) {
    //we can call winAll function here acc. to mukul
    gameState = 0;
  }
}

void loser() {
  losing_sound();
  lcd.clear();
  String lose = "Nahi horra kya????";
  scrolling_loop(lose);
  delay(400);
  lcd.clear();
  for (byte i = 0; i < 3; i++) {
    //   ...........................//losing_sound();
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds[j].setRGB(255, 0, 0);
    }

    FastLED.show();
    delay(500);
    clearLEDS();
    FastLED.show();
    delay(500);
  }
  gameState = 0;
}

void clearLEDS() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }
}

void pink_panther() {
  // change this to make the song slower or faster
  int tempo = 130;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < (notes * 2) / 3.4; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void losing_sound() {
  tone(buzzer, NOTE_G4);
  delay(250);
  tone(buzzer, NOTE_C4);
  delay(500);
  noTone(buzzer);
}

void winning_sound() {
  // Sounds the buzzer at the frequency relative to the note C in Hz
  tone(buzzer, 261);
  // Waits some time to turn off
  delay(200);
  //Turns the buzzer off
  noTone(buzzer);
  // Sounds the buzzer at the frequency relative to the note D in Hz
  tone(buzzer, 293);
  delay(200);
  noTone(buzzer);
  // Sounds the buzzer at the frequency relative to the note E in Hz
  tone(buzzer, 329);
  delay(200);
  noTone(buzzer);
  // Sounds the buzzer at the frequency relative to the note F in Hz
  tone(buzzer, 349);
  delay(200);
  noTone(buzzer);
  // Sounds the buzzer at the frequency relative to the note G in Hz
  tone(buzzer, 392);
  delay(200);
  noTone(buzzer);

}
void scrolling_loop(String text)
{
  int i, j = 0;
  for (i = 0; i < text.length(); i++)
  {
    if (i < 15)
    {
      lcd.setCursor(i, 0);
      lcd.print(text.charAt(i));
      delay(150);
    }
    else
    {
      for (i = 16; i < text.length(); i++)
      {
        j++;
        lcd.setCursor(0, 0);
        lcd.print(text.substring(j, j + 16));
        delay(250);
      }
    }
  }
}
void winAll() {

}
