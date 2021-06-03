#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <gfxfont.h>

#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>



int x = 0;
int index = 0;

#define NB0  31
#define NC1  33
#define NCS1 35
#define ND1  37
#define NDS1 39
#define NE1  41
#define NF1  44
#define NFS1 46
#define NG1  49
#define NGS1 52
#define NA1  55
#define NAS1 58
#define NB1  62
#define NC2  65
#define NCS2 69
#define ND2  73
#define NDS2 78
#define NE2  82
#define NF2  87
#define NFS2 93
#define NG2  98
#define NGS2 104
#define NA2  110
#define NAS2 117
#define NB2  123
#define NC3  131
#define NCS3 139
#define ND3  147
#define NDS3 156
#define NE3  165
#define NF3  175
#define NFS3 185
#define NG3  196
#define NGS3 208
#define NA3  220
#define NAS3 233
#define NB3  247
#define NC4  262
#define NCS4 277
#define ND4  294
#define NDS4 311
#define NE4  330
#define NF4  349
#define NFS4 370
#define NG4  392
#define NGS4 415
#define NA4  440
#define NAS4 466
#define NB4  494
#define NC5  523
#define NCS5 554
#define ND5  587
#define NDS5 622
#define NE5  659
#define NF5  698
#define NFS5 740
#define NG5  784
#define NGS5 831
#define NA5  880
#define NAS5 932
#define NB5  988
#define NC6  1047
#define NCS6 1109
#define ND6  1175
#define NDS6 1245
#define NE6  1319
#define NF6  1397
#define NFS6 1480
#define NG6  1568
#define NGS6 1661
#define NA6  1760
#define NAS6 1865
#define NB6  1976
#define NC7  2093
#define NCS7 2217
#define ND7  2349
#define NDS7 2489
#define NE7  2637
#define NF7  2794
#define NFS7 2960
#define NG7  3136
#define NGS7 3322
#define NA7  3520
#define NAS7 3729
#define NB7  3951
#define NC8  4186
#define NCS8 4435
#define ND8  4699
#define NDS8 4978

int melody1[] = {
  NA4, NC5, NE5, NA5, NB5, NE5, NC5, NB5, 
  NC6, NE5, NC5, NC6, NFS5, ND5, NA4, NFS5, 
  NE5, NC5, NA4, NC5, 0, NE5, NC5, NA4, 
  NG4, NA4, NA4, 0, 0, NA4, NF5, NE5,

  NA4, NA4, NC5, NE5, NB5, NE5, NC5, NB5, 
  NC6, NE5, NC5, NC6, NFS5, ND5, NA4, NFS5, 
  NE5, NC5, NA4, NC5, 0, NE5, NC5, NA4, 
  NG4, NA4, NA4
};

int tempo[] = {
8, 8, 8, 8, 8, 8, 8, 8,
8, 8, 8, 8, 8, 8, 8, 8,
8, 8, 8, 4, 12, 8, 8, 8,
8, 8, 8, 8, 4, 8, 8, 8,


8, 8, 8, 8, 8, 8, 8, 8,
8, 8, 8, 8, 8, 8, 8, 8,
8, 8, 8, 4, 12, 8, 8, 8,
8, 8, 8,
};

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    8  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void drawDayRect(int day, int color) {
  int row = day / 7;
  int col = day % 7;
  
  tft.drawRect(3 + 18 * col, 43 + 16 * row, 15, 12, color);
}

int day = 3;

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(20, 20);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.print("It ain't much,\n\n but it's honest work");
  
  tft.drawLine(tft.width()/2, tft.height()/2, tft.width()/2-20, tft.height()/2-20, ST7735_RED);
  tft.drawLine(tft.width()/2, tft.height()/2, tft.width()/2+20, tft.height()/2-20, ST7735_RED);
  
  tft.drawLine(tft.width()/2-20, tft.height()/2-20, tft.width()/2-40, tft.height()/2, ST7735_RED);
  tft.drawLine(tft.width()/2+20, tft.height()/2-20, tft.width()/2+40, tft.height()/2, ST7735_RED);

  tft.drawLine(tft.width()/2-40, tft.height()/2, tft.width()/2, tft.height()/2+80, ST7735_RED);
  tft.drawLine(tft.width()/2+40, tft.height()/2, tft.width()/2, tft.height()/2+80, ST7735_RED);

  delay(7000);
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(20, 7);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.print("JUN 2021");
  
  int startx = 5;
  int starty = 30;
  int distance = 16;

  tft.setCursor(startx, starty);
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.print("Mo Tu We Th Fr Sa Su");

  tft.setCursor(startx, starty+distance);
  tft.setTextColor(ST7735_GREEN);
  tft.print("    1  2  3  4  5  6");

  tft.setCursor(startx, starty+distance*2);
  tft.print(" 7  8  9 10 11 12 13");

  tft.setCursor(startx, starty+distance*3);
  tft.print("14 15 16 17 18 19 20");

  tft.setCursor(startx, starty+distance*4);
  tft.print("21 22 23 24 25 26 27");

  tft.setCursor(startx, starty+distance*5);
  tft.print("28 29 30");

  int i = 0;
  for (i = 1; i <= 30; i++) {
    drawDayRect(i, ST7735_YELLOW);
    delay(50);
  }

  drawDayRect(day, ST7735_RED);

  tft.drawLine(0, 127, tft.width(), 127, ST7735_BLUE);
  


  DDRD |= (1 << PD6);


  DDRD &= ~(1 << PD7);
  PORTD |= (1 << PD7);

  DDRD &= ~(1 << PD5);
  PORTD |= (1 << PD5);
}

int hour = 16;
int minute = 20;
int second = 45;
char buffer[50];

void loop() {
  static long long previousMillis = 0;
  
  if (millis() - previousMillis >= 1000) {
    previousMillis = millis();

    second++;
    if (second >= 60) {
      second = 0;
      minute++;
    }
    if (minute >= 60) {
      minute = 0;
      hour++;
    }
    if (hour >= 24) {
      hour = 0;
    }

    tft.fillRect(0, 128, tft.width(), tft.height(), ST7735_BLACK);

    sprintf(buffer, "%02d:%02d:%02d", hour, minute, second);
    tft.setCursor(18, 137);
    tft.setTextColor(ST7735_CYAN);
    tft.setTextSize(2);
    tft.print(buffer);

    int size = sizeof(melody1) / sizeof(int);

    if (second == 0 && minute == 21 && hour == 16) {
      for (int i = 0; i < size; i++) {
        int noteDuration = 2000/tempo[i];
        tone(6, melody1[i], noteDuration);
        int pauseBetweenNotes = noteDuration*1.30;
        delay(pauseBetweenNotes);
        noTone(6);
      }

      second = 19;
    }

    if (!(PIND & (1 << PD5)) && !(PIND & (1 << PD7))) {
      drawDayRect(day, ST7735_YELLOW);
      day++;

      if (day >= 31) {
        day = 1;
      }
      
      drawDayRect(day, ST7735_RED);
    } else if (!(PIND & (1 << PD7))) {
      minute++;
      second = 0;
    } else if (!(PIND & (1 << PD5))) {
      hour++;
      second = 0;
    }
  }
}
