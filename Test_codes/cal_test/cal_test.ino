/***************************************************
 * Calcurator for ILI9341                          *
 ***************************************************/



#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

// This is calibration data for the raw touch data to the screen coordinates
#define TIRQ_PIN 16
#define TS_MINX 300
#define TS_MINY 300
#define TS_MAXX 3800
#define TS_MAXY 3800
#define TS_CS_PIN 13
XPT2046_Touchscreen ts(TS_CS_PIN);

#define TFT_CS 15
#define TFT_DC  2
#define TFT_RST 4
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 34
#define BOXX    0
#define BOXY    (320-BOXSIZE*7)

static const unsigned char PROGMEM bmp_sqrt[] = {
  B00000000, B11111111,
  B00000000, B10000000,
  B00000000, B10000000,
  B00000001, B00000000,
  B00000001, B00000000,
  B00000001, B00000000,
  B11000010, B00000000,
  B00100010, B00000000,
  B00100010, B00000000,
  B00100100, B00000000,
  B00010100, B00000000,
  B00010100, B00000000,
  B00010100, B00000000,
  B00001000, B00000000,
  B00001000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_xy[] = {
  B00000000, B00010010,
  B00000000, B00010010,
  B10000000, B10001110,
  B10000000, B10000010,
  B01000001, B00010010,
  B00100010, B00001100,
  B00100010, B00000000,
  B00010100, B00000000,
  B00001000, B00000000,
  B00010100, B00000000,
  B00100010, B00000000,
  B00100010, B00000000,
  B01000001, B00000000,
  B10000000, B10000000,
  B10000000, B10000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_x2[] = {
  B00000000, B00011000,
  B00000000, B00100100,
  B10000000, B10001000,
  B10000000, B10010000,
  B01000001, B00111100,
  B00100010, B00000000,
  B00100010, B00000000,
  B00010100, B00000000,
  B00001000, B00000000,
  B00010100, B00000000,
  B00100010, B00000000,
  B00100010, B00000000,
  B01000001, B00000000,
  B10000000, B10000000,
  B10000000, B10000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_10x[] = {
  B00000000, B00010010,
  B00000000, B00010010,
  B00000000, B00001100,
  B01000011, B00010010,
  B01000100, B10010010,
  B01000100, B10000000,
  B01001000, B01000000,
  B01001000, B01000000,
  B01001000, B01000000,
  B01001000, B01000000,
  B01001000, B01000000,
  B01000100, B10000000,
  B01000100, B10000000,
  B01000011, B00000000,
  B00000000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_x10[] = {
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000010, B00011000,
  B00000010, B00100100,
  B10001010, B00100100,
  B10001010, B01000010,
  B01010010, B01000010,
  B01010010, B01000010,
  B00100010, B01000010,
  B01010010, B01000010,
  B01010010, B00100100,
  B10001010, B00100100,
  B10001010, B00011000,
  B00000000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_ex[] = {
  B00000000, B00010010,
  B00000000, B00010010,
  B00000000, B00001100,
  B00001110, B00010010,
  B00010001, B00010010,
  B00100000, B10000000,
  B01000000, B01000000,
  B01000000, B01000000,
  B01111111, B11000000,
  B01000000, B00000000,
  B01000000, B00000000,
  B00100000, B10000000,
  B00010001, B00000000,
  B00001110, B00000000,
  B00000000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_pn[] = {
  B00000000, B00001000,
  B00001000, B00010000,
  B00001000, B00100000,
  B00111110, B00100000,
  B00001000, B01000000,
  B00001000, B01000000,
  B00000000, B10000000,
  B00000000, B10000000,
  B00000001, B00000000,
  B00000001, B00000000,
  B00000010, B01111110,
  B00000010, B00000000,
  B00000100, B00000000,
  B00000100, B00000000,
  B00000000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_pi[] = {
  B00000000, B00000000,
  B00000000, B00000000,
  B00111111, B11111100,
  B00000100, B00100000,
  B00000100, B00100000,
  B00000100, B00100000,
  B00000100, B00100000,
  B00001000, B00100000,
  B00001000, B00100000,
  B00010000, B00100000,
  B00100000, B00011000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_bs[] = {
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00001100,
  B00000000, B00111100,
  B00000000, B11111100,
  B00000011, B11111100,
  B00001111, B11111100,
  B00111111, B11111100,
  B00111111, B11111100,
  B00001111, B11111100,
  B00000011, B11111100,
  B00000000, B11111100,
  B00000000, B00111100,
  B00000000, B00001100,
  B00000000, B00000000,
  B00000000, B00000000
};

static const unsigned char PROGMEM bmp_mod[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000010,
  B00000000, B00000000, B00000010,
  B00000000, B00000000, B00000010,
  B10000000, B00111000, B00000010,
  B11101100, B01000100, B00000010,
  B10010010, B01000100, B00111010,
  B10010010, B10000010, B01000110,
  B10010010, B10000010, B10000010,
  B10010010, B10000010, B10000010,
  B10010010, B10000010, B10000010,
  B10010010, B10000010, B10000010,
  B10010010, B01000100, B10000010,
  B10010010, B01000100, B01000110,
  B10010010, B00111000, B00111010,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_sin[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00010000, B00000000,
  B00111000, B00010000, B10011000,
  B01000100, B00000000, B10100100,
  B10000010, B00000000, B11000010,
  B10000000, B00010000, B10000001,
  B01000000, B00010000, B10000001,
  B00111000, B00010000, B10000001,
  B00000100, B00010000, B10000001,
  B00000010, B00010000, B10000001,
  B10000010, B00010000, B10000001,
  B01000100, B00010000, B10000001,
  B00111000, B00010000, B10000001,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_cos[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00111000, B00111000, B00111000,
  B01000100, B01000100, B01000100,
  B01000100, B01000100, B10000010,
  B10000010, B10000010, B10000000,
  B10000000, B10000010, B01000000,
  B10000000, B10000010, B00111000,
  B10000000, B10000010, B00000100,
  B10000010, B10000010, B00000010,
  B01000100, B01000100, B10000010,
  B01000100, B01000100, B01000100,
  B00111000, B00111000, B00111000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_tan[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00010000, B00000000, B00000000,
  B00010000, B00111000, B10011000,
  B00010000, B01000100, B10100100,
  B11111110, B10000010, B11000010,
  B00010000, B00000010, B10000001,
  B00010000, B00111110, B10000001,
  B00010000, B01000010, B10000001,
  B00010000, B10000010, B10000001,
  B00010000, B10000010, B10000001,
  B00010000, B10000010, B10000001,
  B00010000, B01000110, B10000001,
  B00001110, B00111010, B10000001,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_asin[] = {
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00111101,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000001,
  B00000000, B00010000, B00000000,
  B00111000, B00010000, B10011000,
  B01000100, B00000000, B10100100,
  B10000010, B00000000, B11000010,
  B01000000, B00010000, B10000001,
  B00111000, B00010000, B10000001,
  B00000100, B00010000, B10000001,
  B10000010, B00010000, B10000001,
  B01000100, B00010000, B10000001,
  B00111000, B00010000, B10000001,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_acos[] = {
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00111101,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000000,
  B00111000, B00111000, B00111000,
  B01000100, B01000100, B01000100,
  B01000100, B01000100, B10000010,
  B10000000, B10000010, B01000000,
  B10000000, B10000010, B00111000,
  B10000000, B10000010, B00000100,
  B01000100, B01000100, B10000010,
  B01000100, B01000100, B01000100,
  B00111000, B00111000, B00111000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_atan[] = {
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00111101,
  B00000000, B00000000, B00000001,
  B00000000, B00000000, B00000001,
  B00010000, B00000000, B00000000,
  B00010000, B00111000, B10011000,
  B00010000, B01000100, B10100100,
  B11111110, B10000010, B11000010,
  B00010000, B00000010, B10000001,
  B00010000, B00111110, B10000001,
  B00010000, B01000010, B10000001,
  B00010000, B10000010, B10000001,
  B00010000, B01000110, B10000001,
  B00001110, B00111010, B10000001,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_log[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00110000, B00000000, B00000000,
  B00010000, B00000000, B00000000,
  B00010000, B00111000, B00111000,
  B00010000, B01000100, B01000100,
  B00010000, B01000100, B10000010,
  B00010000, B10000010, B10000010,
  B00010000, B10000010, B01000110,
  B00010000, B10000010, B00111010,
  B00010000, B01000100, B00000010,
  B00010000, B01000100, B00000010,
  B00111000, B00111000, B10000010,
  B00000000, B00000000, B01000100,
  B00000000, B00000000, B00111000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_ln[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00110000, B00000000, B00000000,
  B00010000, B00000000, B00000000,
  B00010000, B00000000, B00000000,
  B00010000, B10111000, B00000000,
  B00010000, B11000100, B00000000,
  B00010000, B10000010, B00000000,
  B00010000, B10000010, B00000000,
  B00010000, B10000010, B00000000,
  B00010000, B10000010, B00000000,
  B00010000, B10000010, B00000000,
  B00111000, B10000010, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_ca[] = {
  B00000000, B00000000, B00000000,
  B00001111, B00000000, B01100000,
  B00011001, B10000000, B01100000,
  B00110000, B11000000, B11110000,
  B01100000, B01100000, B11110000,
  B01100000, B01100001, B10011000,
  B11000000, B00000001, B10011000,
  B11000000, B00000011, B00001100,
  B11000000, B00000011, B00001100,
  B11000000, B00000011, B11111100,
  B01100000, B01100111, B11111110,
  B01100000, B01100110, B00000110,
  B00110000, B11001100, B00000011,
  B00011001, B10001100, B00000011,
  B00001111, B00001100, B00000011,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_m[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000011, B00000000, B11000000,
  B00000011, B10000001, B11000000,
  B00000011, B11000011, B11000000,
  B00000011, B01100110, B11000000,
  B00000011, B00111100, B11000000,
  B00000011, B00011000, B11000000,
  B00000011, B00000000, B11000000,
  B00000011, B00000000, B11000000,
  B00000011, B00000000, B11000000,
  B00000011, B00000000, B11000000,
  B00000011, B00000000, B11000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_ms[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B11000000, B00110000, B00000000,
  B11100000, B01110000, B00000000,
  B11110000, B11110000, B00000000,
  B11011001, B10110000, B11111100,
  B11001111, B00110000, B11111100,
  B11000110, B00110000, B00000000,
  B11000000, B00110000, B00000000,
  B11000000, B00110000, B11111100,
  B11000000, B00110000, B11111100,
  B11000000, B00110000, B00000000,
  B11000000, B00110000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_10[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B01000000, B11000010, B00000000,
  B11000001, B00100010, B01010100,
  B01000001, B00100000, B01111110,
  B01000010, B00010110, B11010100,
  B01000010, B00010010, B01111110,
  B01000010, B00010010, B01010100,
  B01000010, B00010010, B01111110,
  B01000010, B00010010, B01010100,
  B01000001, B00100010, B01111110,
  B01000001, B00100010, B00000000,
  B01000000, B11000101, B11111111,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM bmp_16[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B01000000, B11000010, B00000000,
  B11000001, B00100010, B01010100,
  B01000010, B00000000, B01111110,
  B01000010, B00000110, B11010100,
  B01000010, B11000010, B01111110,
  B01000011, B00100010, B01010100,
  B01000010, B00010010, B01111110,
  B01000010, B00010010, B01010100,
  B01000010, B00010010, B01111110,
  B01000001, B00100010, B00000000,
  B01000000, B11000101, B11111111,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000
};

static char txt[256];
static char cmd[256];
static int cmd_num;
static int calc_mode; // 10, 16
static double result;
static double result_old;
static double mem;

void setup(void) {
  int x, y;
  int n;
 
  Serial.begin(115200);
  Serial.println(F("Calcurator!"));
  
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);

  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");

  ts.setRotation(0);

  calc_mode=10;
  
  // Show panel
  show_panel();

  result=0;
  result_old=-1;
  cmd_num=0;

  cmd2txt();
  
  show_result();
}

boolean wastouched = true;

void loop()
{
  int x, y;
  int mx, my;
  char cc;
  TS_Point p;
  boolean istouched = ts.touched();

  if (istouched){
    p = ts.getPoint();
    if (wastouched){
      wastouched = istouched;
      delay(100);
      return;
    }
//    Serial.println("touched");
  }else{
//    Serial.println("no touch");
    wastouched = istouched;
    delay(100);
    return;
  }
  wastouched = istouched;

  mx=map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  my=map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  mx=tft.width()-1-mx;
  my=tft.height()-1-my;

  Serial.print("x = ");
  Serial.print(mx);
  Serial.print(", y = ");
  Serial.println(my);

  cc=get_key(mx, my);

  // Non
  if (cc>=100)
    return;

  // 10
  if (cc==90){
    calc_mode=10;
    show_panel();
    result_old=-1.2345;
  // 16
  }else if (cc==91){
    calc_mode=16;
    show_panel();
    result_old=-1.2345;
  // M=
  }else if (cc==92){
    if (cmd_num>0)
      result=calc();
    mem=result;
    cmd_num=0;
  // BS
  }else if (cc==94){
    if (cmd_num>0)
    cmd_num--;
  // C
  }else if (cc==98){
    cmd_num=0;
    result=0;
  // =
  }else if (cc==99){
    result=calc();
    cmd_num=0;
  // +/-
  }else if (cc==49){
    if (cmd_num==0)
      result=-result;
    else
      result=-calc();
    cmd_num=0;
  // +,-,x,/,mod,^
  }else if ((20<=cc && cc<=24) || cc==34){
    if (cmd_num==0)
      cmd[cmd_num++]=18;
    y=0;
    for(x=0;x<cmd_num;x++){
      if ((20<=cmd[x] && cmd[x]<=24) || cmd[x]==34){
        y=1;
        break;
      }
    }
    if (y==1){
      result=calc();
      cmd_num=0;
      cmd[cmd_num++]=18;
    }
    cmd[cmd_num++]=cc;
  // sin,cos,tan,^2,asin,acos,atan,sqrt,log,ln
  }else if ((30<=cc && cc<=33) ||
            (35<=cc && cc<=42)){
    if (cmd_num==0)
      cmd[cmd_num++]=18;
    cmd[cmd_num++]=cc;
    result=calc();
    cmd_num=0;
  }else{
    cmd[cmd_num++]=cc;
  }

  cmd2txt();

  show_result();

/* for debug
  tft.setTextSize(1);
  tft.setCursor(200, 40);
  tft.print(p.x);
  tft.print(",");
  tft.print(p.y);
  tft.setCursor(200, 60);
  tft.print(mx);
  tft.print(",");
  tft.print(my);
*/
}

void show_panel()
{
  int x, y;
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(4);
  for(y=0;y<7;y++){
    for(x=0;x<7;x++){
      if ((x==3 || x==4) && y==6){
        tft.drawRect(BOXX+3*BOXSIZE, BOXY+y*BOXSIZE, BOXSIZE*2, BOXSIZE, ILI9341_WHITE);
        tft.setCursor(BOXX+4*BOXSIZE-8, BOXY+y*BOXSIZE+2);
      }else{
        tft.drawRect(BOXX+x*BOXSIZE, BOXY+y*BOXSIZE, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        tft.setCursor(BOXX+x*BOXSIZE+6, BOXY+y*BOXSIZE+2);
      }
      if (x==0){
        if (y==0)
//          tft.print("pi");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_pi, 16, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("x^y");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_xy, 16, 16, ILI9341_WHITE);
        if (y==2 && calc_mode==16)
          tft.print("A");
        if (y==3)
          tft.print("7");
        if (y==4)
          tft.print("4");
        if (y==5)
          tft.print("1");
        if (y==6)
          tft.print("0");
      }else if (x==1){
        if (y==0)
//          tft.print("sin");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_sin, 24, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("sin");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_asin, 24, 16, ILI9341_WHITE);
        if (y==2 && calc_mode==16)
          tft.print("B");
        if (y==3)
          tft.print("8");
        if (y==4)
          tft.print("5");
        if (y==5)
          tft.print("2");
        if (y==6)
          tft.print(".");
      }else if (x==2){
        if (y==0)
//          tft.print("cos");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_cos, 24, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("cos");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_acos, 24, 16, ILI9341_WHITE);
        if (y==2 && calc_mode==16)
          tft.print("C");
        if (y==3)
          tft.print("9");
        if (y==4)
          tft.print("6");
        if (y==5)
          tft.print("3");
        if (y==6){
//          tft.setTextSize(2);
//          tft.setCursor(BOXX+x*BOXSIZE, BOXY+y*BOXSIZE+10);
//          tft.print("+/-");
//          tft.setTextSize(4);
          tft.drawBitmap(BOXX+x*BOXSIZE+6, BOXY+y*BOXSIZE+10, bmp_pn, 16, 16, ILI9341_WHITE);
        }
      }else if (x==3){
        if (y==0)
//          tft.print("tan");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_tan, 24, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("tan");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_atan, 24, 16, ILI9341_WHITE);
        if (y==2 && calc_mode==16)
          tft.print("D");
        if (y==3 && calc_mode==16)
          tft.print("E");
        if (y==4 && calc_mode==16)
          tft.print("F");
        if (y==5)
//        tft.print("MOD");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_mod, 24, 16, ILI9341_WHITE);
        if (y==6)
          tft.print("=");
      }else if (x==4){
        if (y==0)
//          tft.print("x^2");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_x2, 16, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("sqrt");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_sqrt, 16, 16, ILI9341_WHITE);
        if (y==2)
          tft.print("+");
        if (y==3)
          tft.print("-");
        if (y==4)
          tft.print("x");
        if (y==5)
          tft.print("/");
      }else if (x==5){
        if (y==0)
//          tft.print("M=");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_ms, 24, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("M");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_m, 24, 16, ILI9341_WHITE);
        if (y==2)
//          tft.print("10^");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_10x, 16, 16, ILI9341_WHITE);
        if (y==3)
//          tft.print("log");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_log, 24, 16, ILI9341_WHITE);
        if (y==6)
//          tft.print("16");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_16, 24, 16, ILI9341_WHITE);
      }else if (x==6){
        if (y==0)
//          tft.print("CA");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_ca, 24, 16, ILI9341_WHITE);
        if (y==1)
//          tft.print("BS");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_bs, 16, 16, ILI9341_WHITE);
        if (y==2)
//          tft.print("e^");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_ex, 16, 16, ILI9341_WHITE);
        if (y==3)
//          tft.print("ln");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_ln, 24, 16, ILI9341_WHITE);
        if (y==6)
//          tft.print("10");
          tft.drawBitmap(BOXX+x*BOXSIZE+4, BOXY+y*BOXSIZE+10, bmp_10, 24, 16, ILI9341_WHITE);
      }
    }
  }
}

char get_key(int mx, int my)
{
  int x, y;
  char cc;

  cc=100;
  if (my>=BOXY){
    x=mx/BOXSIZE;
    y=(my-BOXY)/BOXSIZE;

    if (x==0){
      if (y==0) cc=19; // pi
      if (y==1) cc=34; // x^y
      if (y==2 && calc_mode==16) cc=10; // A
      if (y==3) cc=7; // 7
      if (y==4) cc=4; // 4
      if (y==5) cc=1; // 1
      if (y==6) cc=0; // 0
    }
    if (x==1){
      if (y==0) cc=30; // sin
      if (y==1) cc=35; // asin
      if (y==2 && calc_mode==16) cc=11; // B
      if (y==3) cc=8; // 8
      if (y==4) cc=5; // 5
      if (y==5) cc=2; // 2
      if (y==6) cc=16; // .
    }
    if (x==2){
      if (y==0) cc=31; // cos
      if (y==1) cc=36; // acos
      if (y==2 && calc_mode==16) cc=12; // C
      if (y==3) cc=9; // 9
      if (y==4) cc=6; // 6
      if (y==5) cc=3; // 3
      if (y==6) cc=49; // +/-
    }
    if (x==3){
      if (y==0) cc=32; // tan
      if (y==1) cc=37; // atan
      if (y==2 && calc_mode==16) cc=13; // D
      if (y==3 && calc_mode==16) cc=14; // E
      if (y==4 && calc_mode==16) cc=15; // F
      if (y==5) cc=24; // mod
      if (y==6) cc=99; // =
    }
    if (x==4){
      if (y==0) cc=33; // x^2
      if (y==1) cc=38; // sqrt
      if (y==2) cc=20; // +
      if (y==3) cc=21; // -
      if (y==4) cc=22; // *
      if (y==5) cc=23; // /
      if (y==6) cc=99; // =
    }
    if (x==5){
      if (y==0) cc=92; // M=
      if (y==1) cc=93; // M
      if (y==2) cc=39; // 10^
      if (y==3) cc=41; // log
      if (y==6) cc=91; // 16
    }
    if (x==6){
      if (y==0) cc=98; // CA
      if (y==1) cc=94; // BS
      if (y==2) cc=40; // e^
      if (y==3) cc=42; // ln
      if (y==6) cc=90; // 10
    }
  }
  return(cc);
}

void cmd2txt()
{
  int i;
  char cc;
  int txt_num;

  txt_num=0;
  for(i=0;i<cmd_num;i++){
    cc=cmd[i];
    if (0<=cc && cc<=9){
      txt[txt_num++]='0'+cc;
    }else if (cc==10){
      txt[txt_num++]='A';
    }else if (cc==11){
      txt[txt_num++]='B';
    }else if (cc==12){
      txt[txt_num++]='C';
    }else if (cc==13){
      txt[txt_num++]='D';
    }else if (cc==14){
      txt[txt_num++]='E';
    }else if (cc==15){
      txt[txt_num++]='F';
    }else if (cc==16){
      txt[txt_num++]='.';
    }else if (cc==18){
      txt[txt_num++]='A';
      txt[txt_num++]='N';
      txt[txt_num++]='S';
    }else if (cc==20){
      txt[txt_num++]='+';
    }else if (cc==21){
      txt[txt_num++]='-';
    }else if (cc==22){
      txt[txt_num++]='x';
    }else if (cc==23){
      txt[txt_num++]='/';
    }else if (cc==24){
      txt[txt_num++]='%';
    }else if (cc==19){
      txt[txt_num++]='p';
      txt[txt_num++]='i';
    }else if (cc==30){
      txt[txt_num++]='s';
      txt[txt_num++]='i';
      txt[txt_num++]='n';
    }else if (cc==31){
      txt[txt_num++]='c';
      txt[txt_num++]='o';
      txt[txt_num++]='s';
    }else if (cc==32){
      txt[txt_num++]='t';
      txt[txt_num++]='a';
      txt[txt_num++]='n';
    }else if (cc==33){
      txt[txt_num++]='^';
      txt[txt_num++]='2';
    }else if (cc==34){
      txt[txt_num++]='^';
    }else if (cc==35){
      txt[txt_num++]='a';
      txt[txt_num++]='s';
      txt[txt_num++]='i';
      txt[txt_num++]='n';
    }else if (cc==36){
      txt[txt_num++]='a';
      txt[txt_num++]='c';
      txt[txt_num++]='o';
      txt[txt_num++]='s';
    }else if (cc==37){
      txt[txt_num++]='a';
      txt[txt_num++]='t';
      txt[txt_num++]='a';
      txt[txt_num++]='n';
    }else if (cc==38){
      txt[txt_num++]='s';
      txt[txt_num++]='q';
      txt[txt_num++]='r';
      txt[txt_num++]='t';
    }else if (cc==39){
      txt[txt_num++]='1';
      txt[txt_num++]='0';
      txt[txt_num++]='^';
    }else if (cc==40){
      txt[txt_num++]='e';
      txt[txt_num++]='^';
    }else if (cc==41){
      txt[txt_num++]='l';
      txt[txt_num++]='o';
      txt[txt_num++]='g';
    }else if (cc==42){
      txt[txt_num++]='l';
      txt[txt_num++]='n';
    }else if (cc==49){
      txt[txt_num++]='+';
      txt[txt_num++]='/';
      txt[txt_num++]='-';
    }else if (cc==93){
      txt[txt_num++]='M';
    }else if (cc==99){
      txt[txt_num++]='=';
    }

    if (txt_num>50)
      txt_num=50;
  }
  txt[txt_num++]='_';
  txt[txt_num]='\0';  
}

void num2txt(char *txt, char *txt10, double fn, int keta)
{
  int i;
  int n;
  int fx;
  char *str;
  double f0, f1, fl;
  double f0min;
  
  str=txt;
  f0=fn;
  
  if (f0<0){
    *(str++)='-';
    f0=-f0;
  }
  
  fl=log10(f0);
  n=floor(fl);
  f0min=pow(10,n+1-keta);
  f0=f0+f0min/2;

  // 0
  if (f0<=f0min){
    *(str++)='0';
    *(str++)='.';
    *(str++)='\0';
    *txt10='\0';
    return;
  }

  // 123.456 or 1.23456e3
  fx=0;
  if (n>=keta || n<=-(keta-4)){
    f0=f0/pow(10,n);
    fx=n;
    n=0;
  }
  
  // Integer
  if (n>=0){
    for(i=n;i>=0;i--){
      f1=f0/pow(10, i);
      f1=floor(f1);
      *(str++)=(char)f1+'0';
      f0=f0-f1*pow(10,i);
      if (i!=0 && (i % 3)==0)
        *(str++)=',';
      keta--;
    }
  }else{
    *(str++)='0';
  }
  *(str++)='.';

  // Float
  if (f0>f0min){
    for(i=-1;i>-16;i--){
      f1=f0/pow(10, i);
      f1=floor(f1);
      *(str++)=(char)f1+'0';
      f0=f0-f1*pow(10,i);
      if (f0<=f0min)
        break;
      keta--;
      if (keta<=0)
        break;
    }
  }
  *(str++)='\0';
  
  str=txt10;
  if (fx!=0){
    if (fx<0){
      *(str++)='-';
      fx=-fx;
    }
    if (fx>=100){
      n=fx/100;
      *(str++)=n+'0';
      fx=fx-n*100;
      n=fx/10;
      *(str++)=n+'0';
      fx=fx-n*10;
    }else if (fx>=10){
      n=fx/10;
      *(str++)=n+'0';
      fx=fx-n*10;
    }
    n=fx;
    *(str++)=n+'0';
  }
  *(str++)='\0';
}

void num2hex(char *txt, double fn, int keta)
{
  int i;
  int n;
  char *str;
  double f0, f1, fl;
  double f0min;
  
  str=txt;
  f0=fn;
  
  if (f0<0){
    *(str++)='-';
    f0=-f0;
  }
  
  fl=log10(f0)/log10(16);
  n=floor(fl);
  f0min=pow(10,n+1-keta);
  f0=f0+f0min/2;

  // 0
  if (f0<=f0min){
    *(str++)='0';
    *(str++)='.';
    *(str++)='\0';
    return;
  }

  if (n>=keta){
    for(i=0;i<keta;i++)
      *(str++)='F';
    *(str++)='.';
    *(str++)='\0';
    return;
  }
  if (n<=-(keta-4)){
    *(str++)='0';
    *(str++)='.';
    *(str++)='\0';
    return;
  }
  // Integer
  if (n>=0){
    for(i=n;i>=0;i--){
      f1=f0/pow(16, i);
      f1=floor(f1);
      if (f1<10)
        *(str++)=(char)f1+'0';
      else
        *(str++)=(char)f1-10+'A';
      f0=f0-f1*pow(16,i);
      if (i!=0 && (i % 4)==0)
        *(str++)=',';
      keta--;
    }
  }else{
    *(str++)='0';
  }
  *(str++)='.';
  // Float
  if (f0>f0min){
    for(i=-1;i>-16;i--){
      f1=f0/pow(16, i);
      f1=floor(f1);
      if (f1<10)
        *(str++)=(char)f1+'0';
      else
        *(str++)=(char)f1-10+'A';
      f0=f0-f1*pow(16,i);
      if (f0<=f0min)
        break;
      keta--;
      if (keta<=0)
        break;
    }
  }
  *(str++)='\0';
}

void show_result()
{
  char str[32];
  char str10[8];
  
  tft.fillRect(0, 0, tft.width(), 16, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.print(txt);

  tft.fillRect(240-30, BOXY-20, 24, 16, ILI9341_BLACK);
  if (calc_mode==10){
    tft.drawBitmap(240-30, BOXY-20, bmp_10, 24, 16, ILI9341_WHITE);
  }else{
    tft.drawBitmap(240-30, BOXY-20, bmp_16, 24, 16, ILI9341_WHITE);
  }

  if (result!=result_old){
    tft.fillRect(0, 16, tft.width(), 32, ILI9341_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 16);
    if (calc_mode==10){
      num2txt(str, str10, result, 9);
    }else{
      num2hex(str, result, 10);
      *str10='\0';
    }
    tft.print(str);

    if (*str10!='\0'){
      tft.drawBitmap(240-56, 24, bmp_x10, 16, 16, ILI9341_WHITE);
      tft.setTextSize(2);
      tft.setCursor(240-40, 16);
      tft.print(str10);
    }
    result_old=result;
  }
}

double calc()
{
  int i;
  double f0, f1;
  double ii;
  double unit;
  char opp;
  
  f0=0;
  f1=0;
  unit=1;
  opp=0;
  for(i=0;i<cmd_num;i++){
    if (0<=cmd[i] && cmd[i]<=15){
      if (unit<1){
        if (opp==0)
          f0=f0+((double)cmd[i])*unit;
        else
          f1=f1+((double)cmd[i])*unit;
        unit=unit/calc_mode;
      }else{
        if (opp==0)
          f0=f0*calc_mode+((double)cmd[i]);
        else
          f1=f1*calc_mode+((double)cmd[i]);
      }
    }else if (cmd[i]==16){
      unit=0.1;
    }else if (cmd[i]==18){
      f0=result;
    }else if (cmd[i]==19){
      if (opp==0)
        f0=M_PI;
      else
        f1=M_PI;
    }else if (cmd[i]==93){
      if (opp==0)
        f0=mem;
      else
        f1=mem;
    }else if (cmd[i]>=20){
      opp=cmd[i];
      unit=1;
    }
/* for debug
    tft.setTextSize(1);
    tft.setCursor(200, 32);
    tft.print(ff);
    tft.print(':');
*/
  }
  if (opp==20)
    f0=f0+f1;
  if (opp==21)
    f0=f0-f1;
  if (opp==22)
    f0=f0*f1;
  if (opp==23)
    f0=f0/f1;
  if (opp==24){
    ii=floor(f0/f1);
    f0=f0-f1*ii;
  }
  if (opp==30)
    f0=sin(f0);
  if (opp==31)
    f0=cos(f0);
  if (opp==32)
    f0=tan(f0);
  if (opp==33)
    f0=f0*f0;
  if (opp==34)
    f0=pow(f0, f1);
  if (opp==35)
    f0=asin(f0);
  if (opp==36)
    f0=acos(f0);
  if (opp==37)
    f0=atan(f0);
  if (opp==38)
    f0=sqrt(f0);
  if (opp==39)
    f0=pow(10, f0);
  if (opp==40)
    f0=exp(f0);
  if (opp==41)
    f0=log10(f0);
  if (opp==42)
    f0=log(f0);

  return(f0);
}
