//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __|
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/
//
// LCD
//
// Made by Matheus Stutzel
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/4855700-lcd

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define FULL 2
#define EMPTY 3
#define A 0
#define B 1
#define MAXSTA 100


#define btnNONE 0;  
#define btnUP 1;  
#define btnRIGHT 2; 
#define btnLEFT 3; 
#define btnDOWN 4; 
#define btnSELECT 5; 


int photocellPin=0;
int btPin = 1;
int sta=100;
int lum;

byte off   = 0b00000;
byte mask[5] = {
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001
  };

  byte teste[8] = {
    0b11111,
    0b11111,
    0b00001,
    0b00010,
    0b10010,
    0b01111,
    0b10010,
    0b00100
  };
byte f[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  };

byte e[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,    
    0b00000,    
    0b00000,
    0b00000
  };

void setup()
{
  Serial.begin(9600);  
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  //Define alguns chars personalizados
  lcd.createChar(FULL, f);
  lcd.createChar(EMPTY, e);
  
}

void draw_per(int per,int c){
  byte my_per[8];
  byte aux = off;
    int i,j;
    for(i=1;i<=10;i++){
      if(per>=i*10)lcd.write((uint8_t)FULL);
      else if(per<=(i-1)*10)lcd.write((uint8_t)EMPTY);
      else{
        int tmp = per-((i-1)*10);
        tmp/=2;
        for(j=0;j<5;j++){
          if(tmp>=j)aux= aux | mask[j];
        }
        for(j=0;j<8;j++)my_per[j]=aux;


        lcd.createChar(c, my_per);
        lcd.setCursor(5+i,c);
        lcd.write((uint8_t)c);
      }
    }
}
void draw(int lum, int sta){
  	
    lcd.setCursor(0,0);
  	lcd.write("Visib.");
    draw_per(lum/10,A);
    lcd.setCursor(0,1);
  	lcd.write("Energ.");
    draw_per(sta,B);
}
int readPhotocell(){
  int photocellReading = analogRead(photocellPin);  
 
  if(photocellReading>1000)photocellReading=1000;
 /*
  if (photocellReading < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }*/
  return photocellReading;
}

int read_button()
{
 int key_in = analogRead(btPin); 
 if (key_in > 1000) 
	return btnNONE;  
 if (key_in < 50)   return btnUP;  
 if (key_in < 250)  return btnRIGHT; 
 if (key_in < 450)  return btnLEFT; 
 if (key_in < 650)  return btnDOWN; 
 if (key_in < 850)  return btnSELECT;  

 return btnNONE;  
}
int calcSta(){
	sta=sta +10-lum/35;
	if(sta>=MAXSTA)sta=MAXSTA;
	if(sta<=0)sta=0;
}
void mySerial(int l, int b){
  Serial.println((int)b*1000+l);
}
void loop()
{
  int bt = read_button();
  lum = readPhotocell();
  sta = calcSta();
  draw(lum,sta);
  mySerial(lum,bt);
  delay(320);
}

