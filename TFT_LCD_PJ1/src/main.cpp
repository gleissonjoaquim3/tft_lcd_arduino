//Programa: Display LCD Touch TFT 3.5" com Arduino
//Autor: Arduino e Cia
#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h> //Biblioteca grafica
#include <TouchScreen.h>  //Biblioteca Touch

#define YP A3 // Y+ is on Analog1
#define XM A2 // X- is on Analog2
#define YM 9 // Y- is on Digital7
#define XP 8 // X+ is on Digital6

#define TS_MINX 118
#define TS_MINY 92
#define TS_MAXX 906
#define TS_MAXY 951

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_RESET A4 //Pode ser conectado ao pino reset do Arduino
#define LCD_CS A3   // Chip Select
#define LCD_CD A2  // Command/Data
#define LCD_WR A1  // LCD Write
#define LCD_RD A0 // LCD Read

//Definicao de cores
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFD20
#define LIGHTGREY 0xC618 
#define DARKGREY  0x7BEF

MCUFRIEND_kbv tft;

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Armazena o estado dos botões
bool valor_botao1 = 0;
bool valor_botao2 = 0;
bool valor_botao3 = 0;
bool valor_botao4 = 0;
bool valor_botao5 = 0;


void mostra_ligado(int x, int y)
{
  tft.setTextColor(BLACK);
  tft.setCursor(x, y);
  tft.println("LIGADO");
  delay(100);
}

void mostra_desligado(int x, int y)
{
  tft.setTextColor(WHITE);
  tft.setCursor(x, y);
  tft.println("DESLIGADO");
  delay(100);
}

void tela_chamados()
{

//Tela Principal
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(80, 5);
  tft.println("TRANSPORTE VAN APM TERMINALS");

  tft.fillRoundRect(15, 40, 462, 50, 5, ORANGE); // ESPAÇO 1
  tft.drawRoundRect(15, 40, 462, 50, 5, WHITE);
  tft.drawRoundRect(265, 40, 212, 50, 5, WHITE);
  
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(25, 55);
  tft.println("PONTO - 1");

  tft.fillRoundRect(15, 95, 462, 50, 5, ORANGE); // ESPAÇO 2
  tft.drawRoundRect(15, 95, 462, 50, 5, WHITE);
  tft.drawRoundRect(265, 95, 212, 50, 5, WHITE);
  
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(25, 110);
  tft.println("PONTO - 2");

  tft.fillRoundRect(15, 150, 462, 50, 5, ORANGE); // ESPAÇO 3
  tft.drawRoundRect(15, 150, 462, 50, 5, WHITE);
  tft.drawRoundRect(265, 150, 212, 50, 5, WHITE);
  
  tft.setTextColor(WHITE);
  tft.setCursor(25, 165);
  tft.println("PONTO - 3");

  tft.fillRoundRect(15, 205, 462, 50, 5, ORANGE); // ESPAÇO 4
  tft.drawRoundRect(15, 205, 462, 50, 5, WHITE);
  tft.drawRoundRect(265, 205, 212, 50, 5, WHITE);
  
  tft.setTextColor(WHITE);
  tft.setCursor(25, 165);
  tft.println("PONTO - 4");

  tft.fillRoundRect(15, 150, 462, 50, 5, ORANGE); // ESPAÇO 5
  tft.drawRoundRect(15, 150, 462, 50, 5, WHITE);
  tft.drawRoundRect(265, 150, 212, 50, 5, WHITE);
  
  tft.setTextColor(WHITE);
  tft.setCursor(25, 165);
  tft.println("PONTO - 5");

    //Mensagens desligado
  tft.setTextColor(WHITE);
  tft.setCursor(295, 55);
  tft.println("DESLIGADO");
  tft.setCursor(295, 110);
  tft.println("DESLIGADO");
  tft.setCursor(295, 165);
  tft.println("DESLIGADO");
  
}

void setup()
{
  Serial.begin(9600);

  //Definicao pinos dos leds
  pinMode(45, OUTPUT); //Led vermelho
  pinMode(49, OUTPUT); //Led verde

  Serial.println(F("Teste do display LCD TFT"));
  tft.reset();

  //Mostra o tipo do controlador do display no Serial Monitor
  uint16_t identifier = tft.readID();
  Serial.print(F("Controlador do display: "));
  Serial.println(identifier, HEX);

  tft.begin(identifier);
  tft.fillScreen(DARKGREY);
  tft.setRotation(1);

  tela_chamados();
  
}

void loop()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = tft.width() - (map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height() - (map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));

    //Mostra no serial monitor as coordenadas quando o 
    //touch for acionado
    Serial.print("py: ");
    Serial.print(p.y);
    Serial.print(" px: ");
    Serial.println(p.x);

    if (p.y < 140)
    {
      //Botao led vermelho
      if (p.x > 268 & p.x < 307) // ESPAÇO 1
      {
        if (valor_botao1 == 0)
        {
          tft.fillRoundRect(266, 96, 210, 48, 5, GREEN);
          mostra_ligado(315, 110);
          valor_botao1 = !valor_botao1;
          //digitalWrite(45, HIGH);
        }
        else
        {
          tft.fillRoundRect(266, 96, 210, 48, 5, ORANGE);
          mostra_desligado(295, 110); 
          valor_botao1 = !valor_botao1;
          //digitalWrite(45, LOW);
        }
      }

      //Botao led verde
      if (p.x > 180 & p.x < 252) // ESPAÇO 2
      {
        if (valor_botao2 == 0)
        {
          tft.fillRoundRect(266, 151, 210, 48, 5, GREEN);
          mostra_ligado(315, 165); 
          valor_botao2 = !valor_botao2;
          //digitalWrite(49, HIGH);
        }
        else
        {
          tft.fillRoundRect(266, 151, 210, 48, 5,  ORANGE);
          mostra_desligado(295, 165);
          valor_botao2 = !valor_botao2;
          //digitalWrite(49, LOW);
        }
      }
      if (p.x > 400 & p.x < 430) // ESPAÇO 3
      {
        if (valor_botao3 == 0)
        {
          tft.fillRoundRect(266, 41, 210, 48, 5, GREEN);
          mostra_ligado(315, 55); 
          valor_botao3 = !valor_botao3;
          //digitalWrite(49, HIGH);
        }
        else
        {
          tft.fillRoundRect(266, 41, 210, 48, 5,  ORANGE);
          mostra_desligado(295, 55);
          valor_botao3 = !valor_botao3;
          //digitalWrite(49, LOW);
        }
      }
      if (p.x > 400 & p.x < 430) // ESPAÇO 4
      {
        if (valor_botao3 == 0)
        {
          tft.fillRoundRect(266, 41, 210, 48, 5, GREEN);
          mostra_ligado(315, 55); 
          valor_botao3 = !valor_botao3;
          //digitalWrite(49, HIGH);
        }
        else
        {
          tft.fillRoundRect(266, 41, 210, 48, 5,  ORANGE);
          mostra_desligado(295, 55);
          valor_botao3 = !valor_botao3;
          //digitalWrite(49, LOW);
        }
      }
      
    }
  }
  //tft.fillRoundRect(0, 35, 479, 60, 5, WHITE);
}
