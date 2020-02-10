
#include <Arduino.h>
#include "Adafruit_GFX.h"    // Adafruit's core graphics library
#include "Adafruit_TFTLCD.h" // Adafruit's hardware-specific library
#include "TouchScreen.h"
#include "MCUFRIEND_kbv.h"     //Touchscreen library
//#include <Fonts/Org_01.h>    //Include a different font
//#include <EEPROM.h>         //Include the EEPROM library to score the highscore

bool backsensed = false;
bool resetsensed = false;

//Sense touch trough these pins
#define YP A3  // must be an analog pin
#define XM A2  // must be an analog pin
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 118
#define TS_MINY 92
#define TS_MAXX 906
#define TS_MAXY 951
//Create the touchscreen object
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  //(data,data,data,data,sensitivity);

//Some of the tft pins
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// Optional, used to reset the display
#define LCD_RESET A4

#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30

//Create the tft object
MCUFRIEND_kbv tft;

// Define some TFT readable colour codes to human readable names
#define BLACK    0x0000
//int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET   0x8888
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF
//#define GREY   tft.color565(64, 64, 64);
#define GOLD     0xFEA0
#define BROWN    0xA145
#define SILVER   0xC618
#define LIME     0x07E0
#define ORANGE   0xFD20      /* 255, 165,   0 */
#define BLUE     0x001F

int currentpcolour;
int tela_atual = 0;


//Minimum and maximum pressure to sense the touch
#define MINPRESSURE 10
#define MAXPRESSURE 1000

void tela_inicial()
{

  tft.fillScreen(ORANGE); // Plano de fundo
  tft.drawRoundRect(0, 0, 479, 319, 8, WHITE);     //Borda da página

  tft.fillRoundRect(140, 180, 200, 40, 10, WHITE); // Parte interna do botão
  tft.drawRoundRect(140, 180, 200, 40, 10, BLACK);

  tft.fillRoundRect(140, 130, 200, 40, 10, WHITE);   //RGB led
  tft.drawRoundRect(140, 130, 200, 40, 10, BLACK);

  tft.fillRoundRect(140, 80, 200, 40, 10, WHITE);
  tft.drawRoundRect(140, 80, 200, 40, 10, BLACK); //Oscilloscope

  tft.setCursor(110, 20);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("Escolha um modo :");
  tft.setTextColor(BLACK);
  tft.setCursor(175, 195);
  tft.print("AUSENTE");
  tft.setCursor(175, 145);
  tft.print("OCUPADO");
  tft.setCursor(150, 95);
  tft.print("DISPONIVEL");
  tft.setCursor(130, 280);
  tft.setTextColor(WHITE);
  tft.print("APM TERMINALS");
  //  delay(500);

}

void voltar()  //Oscilloscope function
{
  tft.fillScreen(BLACK);
  tft.fillRoundRect(5, 5, 50, 30, 8, BLUE);
  tft.drawRoundRect(5, 5, 50, 30, 8, WHITE);
  tft.setCursor(15, 15);
  tft.print("<-");
}

void setup()
{
  tft.reset(); // Reset
  tft.begin(tft.readID()); // Faz a leitura do núcleo tft_lcd
  Serial.begin(9600); // Inicia o Serial 9600
  Serial.println();
  Serial.print("Lendo informações...");
  delay(500);
  Serial.println(tft.readID(), HEX);
  tft.fillScreen(BLACK); // Fundo Preto
  tft.setRotation(1); // Setada posição horizontal da tela

  tela_atual = 0;

  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(50, 140);
  tft.print("Carregando...");

  tft.setTextColor(tft.color565(255, 255, 0));
  tft.setCursor(30, 70);
  tft.print("Feito por ");

  tft.setCursor(30, 100);
  tft.print("Infra Eletrica :)");
  delay(2000);

  tft.fillScreen(BLACK);

  tela_inicial();

}
void loop()
{

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();     // Read touchscreen
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (tela_atual == 0)
  {
    if (p.z > 10 && p.z < 1000)
    {
      if (p.x > 630 && p.x < 760 && p.y > 340 && p.y < 700)
      {
        Serial.println("Mudança de tela");

        tela_atual = 3;

        tft.fillRoundRect(140, 80, 200, 40, 8, WHITE);
        delay(70);

        tft.fillRoundRect(140, 80, 200, 40, 10, BLACK);
        tft.drawRoundRect(140, 80, 200, 40, 10, WHITE);

        tft.setTextColor(WHITE);
        tft.setCursor(150, 95);
        tft.print("DISPONIVEL");
        delay(1500);

        voltar();

      }
    }
  }
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    if (p.y > 743 && p.x < 247 && p.x > 150 && p.y < 875)
    {
      tft.fillRoundRect(5, 5, 50, 30, 8, WHITE);
      delay(70);
      tft.fillRoundRect(5, 5, 50, 30, 8, BLUE);
      tft.drawRoundRect(5, 5, 50, 30, 8, WHITE);
      tft.setCursor(15, 15);
      tft.print("<-");
      delay(70);
      tft.fillRoundRect(5, 5, 50, 30, 8, BLACK);
      tela_atual = 0;
      tela_inicial();
      p.x = 160;
      p.y = 760;
      return;
    }
}
