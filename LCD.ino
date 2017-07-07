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
  byte aux;
    int i,j;
    for(i=1;i<=10;i++){
      if(per>=i*10)lcd.write((uint8_t)FULL);
      else if(per<=(i-1)*10)lcd.write((uint8_t)EMPTY);
      else{
        int tmp = per-((i-1)*10);
        tmp/=2;
        for(j=0;j<5;j++){
          if(tmp>=j)aux= aux | mask[i];
          else aux = aux & mask[i];
        }
        Serial.print("draw_per per = ");
        Serial.print(per);
        Serial.print(" aux");
        Serial.print(aux);
        Serial.print(" tmp");
        Serial.println(tmp);
        for(j=0;j<8;j++)my_per[i]=aux;
        Serial.print("escreveu teste i=");
        Serial.println(i);


        lcd.createChar(c, my_per);
        lcd.setCursor(5+i,c);
        lcd.write((uint8_t)c);
      }
    }
}
void draw(int lum, int sta){
    lcd.setCursor(6,0);
    draw_per(lum/10,A);
    lcd.setCursor(6,1);
    draw_per(35,B);
}
int readPhotocell(){
  int photocellReading = analogRead(8);  
 
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     
 
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
    if(photocellReading>1000)photocellReading=1000;
  }
  return photocellReading;
}
void loop()
{
  int lum,sta;
  lum = readPhotocell();
  sta = 50;
  draw(lum,sta);
  delay(250);
}

