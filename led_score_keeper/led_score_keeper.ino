/* LED Score Keeper

   This sketch tracks the score between two players: 'R' (red) and 'B' (blue). The
   current score is depicted as two series of red and blue dots which accumulate at
   opposite ends of the LED strip and move toward the center. The first color to
   reach the center wins and triggers a fancy pattern display in the winning color.

 */

#include "FastLED.h"

#define DATA_PIN    6
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    60    // This ain't gonna work unless this number is even
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

// LED array
CRGB leds[NUM_LEDS];

// Game state
int cScore;
int hScore;
int cIndex;
int hIndex;
int cSpell;
int hSpell;
int hEnteredAt;
int fireHue = 0;    // red (starts at "data in" end of LED strip)
int waterHue = 160;  // blue (starts at "data out" end of LED strip)
int airHue = 320;  // #TODO change this to actuval value for white (starts at "data out" end of LED strip)
bool gameOver;

void setup() {
  p1Score = 0;
  p2Score = 0;
  gameOver = false;

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  Serial.begin(9600);
}

void loop() {
  if (cIndex == NUM_LEDS || hIndex == 0))
  {
    displayWinner();
  } else if (cIndex + 1 == hIndex - 1) {
    resolveSpells();
  } else {
    displayScore();
  }
}

// Hit registered event signaled on serial port
void serialEvent() {
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'f') {
      hSpell = "fire";
    } else if (ch == 'w') {
      hSpell = "water";
    } else if (ch == 'a') {
      hSpell = "air";
    }
  }
}

void displayScore() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (hSpell){
      hEnteredAt = i;
    }
    if (cIndex)
    {
      cIndex = i;
      leds[cIndex] = CHSV(getHue(cSpell), 255, 192);
    }
    if (hIndex) {
      hIndex = NUM_LEDS - hEnteredAt - i;
      leds[hIndex] = CHSV(getHue(hSpell), 255, 192);
    }
  }
  FastLED.show();
  delay(500);

  // Blink the players' last LED
  if (cIndex > 0) {
    leds[cIndex - 1] = CRGB::Black;
  }
  if (hIndex < NUM_LEDS)
  {
    leds[hIndex + 1] = CRGB::Black;
  }
  FastLED.show();
  delay(500);
}

string getHue(spell string){
  if spell == "fire" {
    return fireHue;
  }
  if spell == "water" {
    return waterHue;
  }
  if spell == "air" {
    return airHue;
  }
}

void displayWinner() {
  // "sinelon" pattern - a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS-1 );
  //computer wins
  if (hIndex == nil) {
    leds[pos] += CHSV(getHue(cSpell), 255, 192);
    //pumpkinWinsLights()
    //pumpkinWinsSounds()
  //human wins
  }else if (cIndex == nil)  {
    leds[pos] += CHSV(getHue(hSpell), 255, 192);
    //pumpkinWinsLights()
    //pumpkinWinsSounds()
    //tie
  }else {
    // TODO FLASH BOTH
   // leds[pos] += CHSV(getHue(hSpell), 255, 192);
  }

  // Send the 'leds' array out to the actual LED strip
  FastLED.show();
  // Insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

void resolveSpells(){
  string winner switch (expression)
  {

  case cSpell == fire && hSpell == air
  case cSpell == water && hSpell == fire
  case cSpell == air && hSpell == water
    cWinDisplay()
    hIndex = nil
    break; /* optional */

  case hSpell == fire && cSpell == air
  case hSpell == water && cSpell == fire
  case hSpell == air && cSpell == water
    hWinDisplay()
    cIndex = nil
    break; /* optional */

  // if it's a tie, dispaly the tie animation and set both indexes to their end, setting off the tie game end
  default: /* Optional */
    tieDisplay()
        cIndex = NUM_LEDS
  }
}

void cWinDisplay(){
  
}
