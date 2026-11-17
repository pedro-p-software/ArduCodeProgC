
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#include <TouchScreen.h>
//declaraçao de pinos de cada camada
int XP = 7, YP = A2, XM = A1, YM = 6;

//função que lê o ID da tela
uint16_t readID(void) {
    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9486;
    return ID;
}

//declaração da tela por meio da localização dos fins e começos de cada camada, junto da resistencia em ohms da tela como um todo
TouchScreen ts(XP, YP, XM, YM, 300);


// Conjunto de dados contendo localizaçao e pressao do toque
TSPoint tp;

void readResistiveTouch(void)
{
    tp = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
   }

void gameStart(void)
{
  tft.fillScreen(TFT_BLUE);
  delay(500);
  tft.fillScreen(TFT_NAVY);
  tft.println("Game starting in..");
  delay(1000);
  tft.println("3");
  delay(500);
  tft.println("2");
  delay(500);
  tft.println("1");
  tft.fillScreen(TFT_BLUE);
  delay(1000);
}

void circleSpawn()
{
randomSeed(analogRead(A8));


int maxX = tft.width() - 7;
int maxY = tft.height() - 7;

int randomX = random(0, maxX);
int randomY = random(0, maxY);

tft.fillCircle(randomX, randomY, 7 , TFT_RED);
}

void setup() {
  
  uint16_t ID = readID();

  Serial.begin(9600);
  
  tft.begin(ID);
  gameStart();

  tft.println("Here's some info, human.");

  tft.print("Max X coordinate: ");
  tft.println(tft.width());

  tft.print("Max Y coordinate: ");
  tft.println(tft.height());

  
  circleSpawn();
}

void loop() {
  // put your main code here, to run repeatedly:

  

}

