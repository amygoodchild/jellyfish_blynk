#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN_A   D4
#define DATA_PIN_B   D3
#define DATA_PIN_C   D5

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS_A    30
#define NUM_LEDS_B    30
#define NUM_LEDS_C    20

CRGB leds[80];

#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

// Jellyfish 1
//char auth[] = "16b78629cad74030b8623a6bd5fe2e29";

// Jellyfish 2
char auth[] = "7fde6f4475a143db9bdd6bdf7df3cd09";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN_A,COLOR_ORDER>(leds, 0, NUM_LEDS_A).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN_B,COLOR_ORDER>(leds, 30, NUM_LEDS_B).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN_C,COLOR_ORDER>(leds, 60, NUM_LEDS_C).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  Blynk.begin(auth, "VM2897163", "n5sjLcjLfqmg");
  Serial.print("Connecting");
  while (Blynk.connect() == false) {
      // Wait until connected
      Serial.print(".");
      delay(100);
  }
  Serial.println();
  Blynk.syncAll();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();

}


BLYNK_WRITE(V1){
  int r = param[0].asInt();
  int g = param[1].asInt();
  int b = param[2].asInt();


    for (int i=0; i<80; i++){
    leds[i].setRGB(r,g,b);
  }

  // send the 'leds' array out to the actual LED strip
  FastLED.show(); 
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);  
}

