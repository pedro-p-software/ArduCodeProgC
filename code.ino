

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;


#include <TouchScreen.h>
//declaraçao de pinos de cada camada
int XP = 7, YP = A2, XM = A1, YM = 6;


#define MINPRESSURE 200 /**< Pressão mínima para registar um toque válido. */
#define MAXPRESSURE 1000 /**< Pressão máxima permitida para um toque válido. */

//circle spawn logic variables
int rY = 0;
int rX = 0;
long dX = 0;
long dY = 0;
unsigned long lastCount = 0;
int score = 0;
int circleCount = 0;

const int 
TS_LEFT=201, 
TS_RT=890, 
TS_TOP=173, 
TS_BOT=881; // valores de calibração (presets sla)

//função que lê o ID da tela
uint16_t readID(void) {
    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9486;
    return ID;
}


//declaração da tela por meio da localização dos fins e começos de cada camada, junto da resistencia em ohms da tela como um todo
TouchScreen ts(XP, YP, XM, YM, 300);


//Declaração de botão
Adafruit_GFX_Button botao_circulo;
int X, Y;


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
  tft.println("If you let 10 circles in the screen you lose");
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


bool touched(){
  
  TSPoint p = ts.getPoint();


     pinMode(YP, OUTPUT);      // restaura pinos partilhados
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   // por causa dos pinos de controlo do TFT
    digitalWrite(XM, HIGH);


    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE); //valida o toque
    
    if (pressed) {
        X = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
        Y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}




void setup() {
  
  uint16_t ID = readID();


  Serial.begin(9600);
  
  tft.begin(ID);
  gameStart();

  tft.print("Max X coordinate: ");
  tft.println(tft.width());


  tft.print("Max Y coordinate: ");
  tft.println(tft.height());


  randomSeed(analogRead(A8));


}


void loop() {
  // put your main code here, to run repeatedly:
  
  bool press = touched();


  if (millis() - lastCount >= 1000){
    circleCount++;
    rX = random(0, tft.width() - 30);
    rY = random(0, tft.height() - 30);
    tft.fillCircle(rX, rY, 30, TFT_RED);
    lastCount = millis();
  }

  if (press){
    Serial.println(X);
    Serial.println(Y);
    dX = X - rX;
    dY = Y - rY;
    if( dX * dX + dY * dY <= 900){
      score++;
      tft.fillCircle(rX, rY, 30, TFT_BLUE);
      circleCount -= 1;
        Serial.println(score);
        Serial.println("pressionado");

    }
  }

}


