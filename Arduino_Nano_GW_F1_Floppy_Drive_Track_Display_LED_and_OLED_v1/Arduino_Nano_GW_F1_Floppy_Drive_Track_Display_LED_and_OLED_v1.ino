/***************************************************************************/
// GW F1 (Gotek and 3.5 custom boards) Floppy Drive Tracker - LEDC68 and OLED
// Supports following screens:
// * LEDC68
// * 0.91" 128x32 I2C OLED
// * 0.96" 128x64 I2C OLED
//
// Following OLED driver libraries supported
// * SSD1306
// * SSH1106 (TBC)
/**************************************************************************/

const char *myDescription = "Greaseweazle F1 (Gotek or 3.5) Track Display";

const char *myVersion = "v1.0";

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "I2CScanner.h"

// Setup I2C scanner
I2CScanner scanner;
byte i2c_address;
int i2c_found_count = 0;
byte i2c_found_address;

enum ScreenType {
  NONE,
  LED,
  LCD,
  OLED
};

ScreenType screen_type = NONE;

// Include libraries for OLED screen - assumed to be SSD1306

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#include "TM1651.h"

//Define LED screen pins
int DIO_Pin = 18;    // A4
int CLK_Pin = 19;    // A5

// Define drive signal pins
const byte STEP_Pin = 2;   // D2 (D2 and D3 are interrupt capable)

int DIR_Pin = 4;    // D4
int SIDE_Pin = 5;   // D5
int SEL_Pin = 6;   // D6
int INDEX_Pin = 7;  // D7
int TRK0_Pin = 8;   // D8
int DKWE_Pin = 9;   // D9

int JP_SPARE_Pin = 14;      // D14 / A0
int JP_OLED_DR_Pin = 15;    // D15 / A1
int JP_OLED_RES_Pin = 16;   // D16 / A2


// variables to store the drive signal states
int DIR_State = 0;
int STEP_State = 0;
int SIDE_State = 0;
int SIDE_Last = 0;  // For edge detection - for activity counter
int INDEX_State = 0;
int TRK0_State = 0;
int SEL_State = 0;
int DKWE_State = 0;

int JP_OLED_RES_State = 0;
int JP_OLED_DR_State = 0;
int JP_SPARE_State = 0;

// Track position
int TRACK_POS = 0;
int TRACK_TENS = 0;
int TRACK_UNITS = 0;

// Note: D13 is used by onboard LED
const byte ledPin = 13;
int counter = 0;


// OLED
#define OLED_RESET 4

int oled_w = 128; // default oled width
int oled_h = 32;  // defaylt oled height

// Default font sizes
int font_1_w = 6;
int font_1_h = 8;

int font_2_w = 12;
int font_2_h = 16;

int font_3_w = 18;
int font_3_h = 24;

int font_4_w = 24;
int font_4_h = 32;

// ----------------------------------------------------------

// 'Greaseweazle - logo', 128x48px
const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x13, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x80, 0x00, 0x00, 0x00, 0x71, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x80, 0x00, 0x00, 0x00, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x18, 0x00, 0x00, 0x00, 0x00, 0x11, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x01, 0xf0, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x7f, 0x80, 0x06, 0x0e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0xc0, 0x0e, 0x0e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x81, 0xe0, 0x70, 0x01, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xe0, 0xf0, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x1c, 0x1f, 0xe0, 0x31, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x1c, 0x1c, 0x63, 0xfc, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x1c, 0x18, 0x63, 0xfc, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0x1b, 0x90, 0x63, 0xfc, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0x1f, 0x90, 0x07, 0xe0, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0x1f, 0x90, 0x07, 0xc0, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0x0f, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x08, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x10, 0x00, 0x00, 0x01, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x03, 0xff, 0xfc, 0x01, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x04, 0xf0, 0xf4, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x84, 0x60, 0x62, 0x01, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xe0, 0x10, 0xe1, 0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x11, 0xc1, 0x82, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x70, 0x0e, 0x01, 0xf0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x06, 0x01, 0xf3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x03, 0x01, 0xf3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0x7f, 0xe3, 0xfc, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x3f, 0xc7, 0xf8, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x0c, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc3, 0x80, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x83, 0x80, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7f, 0xf0, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x10, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x01, 0xf0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x01, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00
};



// ----------------------------------------------------------

void found_i2c(byte i2c_address)
{
  i2c_found_count = i2c_found_count + 1;
  i2c_found_address = i2c_address;
  
  //Serial.print(F("### found_i2c() - i2c_found_count: "));
  //Serial.print(i2c_found_count);
  //Serial.println(F(" ###"));

  //Serial.print(F("### found_i2c() - i2c_address: 0x"));
  //Serial.print(i2c_address, HEX);
  //Serial.println(F(" ###"));
}

void stepping()
{
  //Serial.println(F("### stepping() - FALLING ###"));

  // Read current DIR state
  DIR_State = digitalRead(DIR_Pin);

  // Increment or decrement Track position
  switch (DIR_State)
  {
    case 0:
      {
        TRACK_POS = TRACK_POS + 1;
        break;
      }

    case 1:
      {
        if (TRACK_POS > 0) // only if it is greater than 0
        {
          TRACK_POS = TRACK_POS - 1;
        }
        break;
      }
  }

  counter++;
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup()
{
  Serial.begin(9600);
  while (!Serial) {};

  // -----------------------

  Serial.println(F("---------------------------"));
  Serial.println(F("###"));
  
  Serial.print(F("### "));
  Serial.print(myDescription);
  Serial.println(F(" ###"));
  
  Serial.print(F("### "));
  Serial.print(myVersion);
  Serial.println(F(" ###"));
  
  Serial.println(F("###"));

  // Set digital input pins with internal pullups

  pinMode(DIR_Pin, INPUT_PULLUP);

  // Make interrupt for STEP pin, so that falling edge can be detected.
  pinMode(STEP_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(STEP_Pin), stepping, FALLING);
  pinMode(INDEX_Pin, INPUT_PULLUP);
  pinMode(SIDE_Pin, INPUT_PULLUP);
  pinMode(TRK0_Pin, INPUT_PULLUP);
  pinMode(SEL_Pin, INPUT_PULLUP);
  pinMode(DKWE_Pin, INPUT_PULLUP);

  //----------------------------

  // Check Jumpers

  pinMode(JP_SPARE_Pin, INPUT_PULLUP);
  pinMode(JP_OLED_RES_Pin, INPUT_PULLUP);
  pinMode(JP_OLED_DR_Pin, INPUT_PULLUP);

  JP_SPARE_State = digitalRead(JP_SPARE_Pin);
  JP_OLED_RES_State = digitalRead(JP_OLED_RES_Pin);
  JP_OLED_DR_State = digitalRead(JP_OLED_DR_Pin);

  Serial.print(F("### JP_SPARE_State: "));
  Serial.print(JP_SPARE_State);
  Serial.println(" ###");

  Serial.print(F("### JP_OLED_RES_State: "));
  Serial.print(JP_OLED_RES_State);
  Serial.println(F(" ###"));

  Serial.print(F("### JP_OLED_DR_State: "));
  Serial.print(JP_OLED_DR_State);
  Serial.println(F(" ###"));

  switch (JP_OLED_RES_State)
  {
    case 1:
      {

        oled_w = 128; // default oled width
        oled_h = 32;  // defaylt oled height
        
        Serial.print(F("### JUMPER: OLED Resolution: "));
        Serial.print(oled_w);
        Serial.print(F("x"));
        Serial.print(oled_h);
        Serial.println (F(" ###"));

        break;
      }
    case 0:
      {

        oled_w = 128; // default oled width
        oled_h = 64;  // defaylt oled height


        Serial.print(F("### JUMPER: OLED Resolution: "));
        Serial.print(oled_w);
        Serial.print(F("x"));
        Serial.print(oled_h);
        Serial.println (F(" ###"));
        break;
      }
  }

  switch (JP_OLED_DR_State)
  {
    case 1:
      {
        Serial.println(F("### JUMPER: OLED Driver: SSD1306 ###"));
        break;
      }
    case 0:
      {
        Serial.println(F("### JUMPER: OLED Driver: SH1106 ###"));
        break;
      }
  }


  //----------------------------

  // Scan for I2C screens

  //Serial.println(F("### Screen Scan: Init... ###"));
  scanner.Init();

  //Serial.println(F("### Screen Scan: Execute... ###"));
  scanner.Execute(found_i2c);

  //Serial.println(F("### Screen Scan: Done... ###"));

  if (i2c_found_count == 0) {
    screen_type = NONE;
    Serial.println(F("### Screen Type: NONE !!! ###"));
  }
  else if (i2c_found_count == 1) {
    screen_type = OLED;
    Serial.println(F("### Screen Type: OLED ###"));
  }
  else if (i2c_found_count > 100) {
    screen_type = LED;
    Serial.println(F("### Screen Type: LED ###"));
  }

  switch (screen_type) {

    case LED:
      {
        Serial.println(F("### LED screen found! ###"));

        // Reset I2C bus
        TWCR = 0;

        // Create TM1651Display
        TM1651 Display(CLK_Pin, DIO_Pin);

        Serial.println(F("### LED: TM1651 display created ###"));

        // Set display brightness
        Display.displaySet(0);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

        Serial.println(F("### LED: Display brightness set to 0 ###"));

        delay(300);

        // Initialise screen
        Display.displayNum(0, 20);
        Display.displayNum(1, 20);
        Display.displayNum(2, 20);

        Serial.println(F("### LED: Display initialised (---) ###"));

        delay(300);

        while (1)
        {
          // Poll the drive signals
          DIR_State = digitalRead(DIR_Pin);
          STEP_State = digitalRead(STEP_Pin);
          SIDE_State = digitalRead(SIDE_Pin);
          INDEX_State = digitalRead(INDEX_Pin);
          TRK0_State = digitalRead(TRK0_Pin);
          SEL_State = digitalRead(SEL_Pin); // LOW = STEP IN; HIGH = STEP OUT
          DKWE_State = digitalRead(DKWE_Pin);

          if (TRK0_State == 0)
          {
            TRACK_POS = 0;

            Display.displayNum(0, 22);  // Show letter 't'
          }

          // DKWE Display
          // This will flash the middle segment briefly - as it is above the SIDE display code.
          if (DKWE_State == 0) //
          {
            Display.displayNum(2, 20);
          }

          // SIDE Display
          if (SIDE_State == 1) // High = Lower head = side 0
          {
            Display.displayNum(2, 21);
            //Display.displayNum(2,17);
          }

          if (SIDE_State == 0) // Low = Upper head = side 1
          {
            Display.displayNum(2, 19);
            //Display.displayNum(2,18);
          }

          if (SIDE_Last != SIDE_State) // edge detection
          {
            counter++;
          }

          SIDE_Last = SIDE_State; // for edge detection

          // Track display
          TRACK_TENS = TRACK_POS / 10;
          TRACK_UNITS = TRACK_POS % 10;

          if (TRACK_TENS == 0)
          {
            if (TRK0_State == 0)
            {
              Display.displayNum(0, 22);  // Show letter 't' (0x78)
            }
            else
            {
              Display.displayNum(0, 16);  // show space/empty character
            }
          }
          else
          {
            Display.displayNum(0, TRACK_TENS);
          }

          Display.displayNum(1, TRACK_UNITS);

          // Change built-in LED state
          if (counter % 2 == 0)
          {
            digitalWrite(ledPin, HIGH);
          }
          else
          {
            digitalWrite(ledPin, LOW);
          }

        } // while loop

        break;
      } // case LED

    case OLED:
      {
        Serial.print(F("### OLED screen found! (0x"));
        Serial.print(i2c_found_address, HEX);
        Serial.println(F(") ###"));

        // Set up OLED:
        Adafruit_SSD1306 oled_display(oled_w, oled_h, &Wire, OLED_RESET);

        //oled_display.begin(SSD1306_SWITCHCAPVCC, i2c_found_address);
        if(!oled_display.begin(SSD1306_SWITCHCAPVCC, i2c_found_address)) { // Address 0x3D for 128x64
          Serial.println(F("SSD1306 allocation failed"));
          for(;;); // Don't proceed, loop forever
        }
        
        oled_display.setRotation(2); // rotate 180 degrees
        oled_display.setTextColor (WHITE); // Only white for an OLED!

        Serial.print(F("### OLED:  Adafruit_SSD1306 screen created (0x"));
        Serial.print(i2c_found_address, HEX);
        Serial.println(F(") ###"));
       
        // For some reason, the DIR pin mode needs to be set again when an OLED screen is used.
        pinMode(DIR_Pin, INPUT_PULLUP);

        // 
        // Loading screen
        oled_display.clearDisplay(); //for Clearing the display
         switch(oled_h)
          {
            case 32:
            {
              oled_display.drawBitmap(0, 0, myBitmap, 128, 32, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
              oled_display.setCursor (oled_w/2 - (font_1_w*12)/2,oled_h-font_1_h); // position the cursor
              //oled_display.print ("Greaseweazle");
              break;
            }
            case 64:
            {
              oled_display.drawBitmap(0, 0, myBitmap, 128, 48, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
              oled_display.setTextSize (1); 
              oled_display.setCursor (oled_w/2 - (font_1_w*12)/2,oled_h-font_2_h/2 - font_1_h/2); // position the cursor
              oled_display.print ("Greaseweazle");
              
              break;
            }
          }

          oled_display.display ();
          delay(2000);

        // While loop
        while (1)
        {
          // Poll the drive signals

          DIR_State = digitalRead(DIR_Pin);
          STEP_State = digitalRead(STEP_Pin);
          SIDE_State = digitalRead(SIDE_Pin);
          INDEX_State = digitalRead(INDEX_Pin);
          TRK0_State = digitalRead(TRK0_Pin);
          SEL_State = digitalRead(SEL_Pin); // LOW = STEP IN; HIGH = STEP OUT
          DKWE_State = digitalRead(DKWE_Pin);
          
          oled_display.clearDisplay (); // clear display

          if (TRK0_State == 0)
          {
            TRACK_POS = 0;
          }

          // DKWE text
          if (DKWE_State == 0)
          {
            switch(oled_h)
            {
              case 32:
              {
                oled_display.setTextSize (1); 
                oled_display.setCursor (((oled_w/2) - (font_1_w/2)), 0); // position the cursor
                break;
              }
              case 64:
              {
                oled_display.setTextSize (2); 
                oled_display.setCursor (((oled_w/2) - (font_2_w/2)), oled_h-font_2_h); // position the cursor
                break;
              }
            }
            
            
            //oled_display.setTextColor (WHITE); // white is not default !
            oled_display.print ("*");
          }

          // Track text

          switch(oled_h)
          {
            case 32:
            {
              oled_display.setTextSize (3); 

              if(TRACK_POS < 10) // 1 digit
              {
                oled_display.setCursor (((oled_w/2)-font_3_w-font_2_w),(oled_h/2)-(font_3_h/2));
              }
              else // 2-digits
              {
                oled_display.setCursor (((oled_w/2)-(font_3_w*2)-font_2_w),(oled_h/2)-(font_3_h/2));
              }
              
              break;
            }
            case 64:
            {
              oled_display.setTextSize (4); 

              if(TRACK_POS < 10) // 1 digit
              {
                oled_display.setCursor (((oled_w/2)-(font_4_w))-5, ((oled_h-font_2_h)/2)-(font_4_h/2));
              }
              else // 2-digits
              {
                oled_display.setCursor (((oled_w/2)-(font_4_w*2))-5,((oled_h-font_2_h)/2)-(font_4_h/2));
              }
             
              break;
            }
          }
            
          oled_display.print (TRACK_POS);
          
          // SIDE

          // Dot
          //oled_display.setCursor ((oled_w / 2) - (font_3_w / 2), (oled_h / 2) - (font_3_h / 2));
          //oled_display.print (".");
          switch(oled_h)
          {
            case 32:
            {
              oled_display.fillCircle(oled_w/2,oled_h/2,3,WHITE);
              oled_display.setCursor ((oled_w/2)+12, (oled_h / 2) - (font_3_h / 2));
              break;
            }
            case 64:
            {
              oled_display.fillCircle((oled_w)/2,(oled_h-font_2_h)/2,4,WHITE);
              oled_display.setCursor ((oled_w/2)+10, ((oled_h-font_2_h)/2)-(font_4_h/2));
              break;
            }
          }
          
          // Side value
           oled_display.print (!SIDE_State);

          // Dir text
          oled_display.setTextSize (2); 

          if (DIR_State == 0) // increment
          {
             switch(oled_h)
            {
              case 32:
              {
                oled_display.setCursor ((oled_w/2)+ (font_3_w * 2), (oled_h / 2) - (font_2_h / 2)); // position the cursor
                break;
              }
              case 64:
              {
                oled_display.setCursor (oled_w - font_2_w, (oled_h-font_2_h)); // position the cursor
                break;
              }
            }
            
            oled_display.print (">");
          }

          if (DIR_State == 1) // decrement
          {
               switch(oled_h)
              {
                case 32:
                {
                  if (TRACK_POS < 10) // 1 digit
                  {
                    oled_display.setCursor (((oled_w / 2) - (font_3_w * 3)), (oled_h / 2) - (font_2_h / 2)); // position the cursor
                  }
                  else // 2 digits
                  {
                    oled_display.setCursor (((oled_w / 2) - (font_3_w * 4)), (oled_h / 2) - (font_2_h / 2)); // position the cursor
                  }
                  break;
                }
                case 64:
                {
                  oled_display.setCursor (0,oled_h-font_2_h); // position the cursor
                  break;
                }
              }
            
            

            oled_display.print ("<");
          }

          // Track line
          //
          switch(oled_h)
          {
            case 32:
            {
              oled_display.drawLine(0, oled_h - 1, TRACK_POS, oled_h - 1, WHITE);
              break;
            }
            case 64:
            {
              //oled_display.drawLine(0, oled_h - font_2_h - 1 , TRACK_POS, oled_h - font_2_h - 1, WHITE);
              oled_display.drawLine((oled_w/2) - (TRACK_POS/2), oled_h - font_2_h - 1 , (oled_w/2) + (TRACK_POS/2), oled_h - font_2_h - 1, WHITE);
              break;
            }
          }

          // SEL text

          if (SEL_State == 0)
          {
            switch(oled_h)
            {
              case 32:
              {
                oled_display.setTextSize (1); 
                oled_display.setCursor (oled_w - (font_1_w * 3), 0); // position the cursor
                break;
              }
              case 64:
              {
                oled_display.setTextSize (2); 
                oled_display.setCursor (oled_w*0.75 - ((font_2_w*3)/2), oled_h-font_2_h); // position the cursor
                break;
              }
            }
            
            oled_display.print ("SEL");
          }

          // TRK0 text
          if (TRK0_State == 0)
          {
            switch(oled_h)
            {
              case 32:
              {
                oled_display.setTextSize (1); 
                oled_display.setCursor (0, oled_h-font_1_h); // position the cursor
                break;
              }
              case 64:
              {
                oled_display.setTextSize (2); 
                oled_display.setCursor ((oled_w/4)-(font_2_w/2), oled_h - font_2_h); // position the cursor
                break;
              }
            }

            oled_display.print ("T0");
          }

          /**
          if (INDEX_State == 0)
          {
            switch(oled_h)
            {
              case 32:
              {
                oled_display.setCursor ((oled_w/2)-(font_1_w/2), oled_h-font_1_h); // position the cursor
                break;
              }
              case 64:
              {
                oled_display.setCursor ((oled_w/2) + (font_1_w * 3), oled_h - font_1_h); // position the cursor
                break;
              }
            }
            
            oled_display.setTextSize (1); 
            //oled_display.setTextColor (WHITE); // white is not default !
            oled_display.print ("I");
          }
          **/

          // Guide lines

          if(0) // enable/disable
          {
            switch(oled_h)
            {
              case 32:
              {
                oled_display.drawRect(0, 0, oled_w, oled_h, WHITE);  // borders
                oled_display.drawLine(oled_w/2, 0, oled_w/2, oled_h, WHITE);  // vertical
                oled_display.drawLine(0, oled_h/2, oled_w, oled_h/2, WHITE);  // horizontal
                break;
              }
  
              case 64:
              {
                // Top
                oled_display.drawRect(0, 0, oled_w, oled_h-font_2_h, WHITE);  // borders
                oled_display.drawLine(oled_w/2, 0, oled_w/2, oled_h-font_2_h, WHITE);  // vertical
                oled_display.drawLine(0, (oled_h-font_2_h)/2, oled_w, (oled_h-font_2_h)/2, WHITE);  // horizontal
                
                // Bottom
                oled_display.drawRect(0, oled_h-font_2_h, oled_w, font_2_h, WHITE);  // borders
                oled_display.drawLine(oled_w/2, 0, oled_w/2, oled_h, WHITE);  // vertical
                oled_display.drawLine(0, oled_h-(font_2_h/2), oled_w, oled_h-(font_2_h/2), WHITE);  // horizontal
           
                
                break;
              }
            }
          }
          

          // Draw OLED display
          oled_display.display ();

          //
          if (SIDE_Last != SIDE_State) // edge detection
          {
            counter++;
          }

          SIDE_Last = SIDE_State; // for edge detection

          if (counter % 2 == 0)
          {
            digitalWrite(ledPin, HIGH);
          }
          else
          {
            digitalWrite(ledPin, LOW);
          }

          /**
          Serial.print("### OLED: counter = ");
          Serial.print(counter);
          Serial.println(" ###");
          **/
          
        } // while loop
        break;

      } // case OLED

    default:
      {
        Serial.println(F("### NO screen found! ###"));
        //Serial.println(F("### Performing warm reset... ###"));
        //delay(300);
        //resetFunc();  //call reset
        break;
      } // default
  } // switch(type)
} // void setup()

void loop()
{
  //Serial.println("### void LOOP ###");
  //delay(500);
}
