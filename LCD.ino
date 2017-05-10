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
#define tree_empty_l 4
#define tree_empty_r 5
#define tree_l 6
#define tree_r 7

byte on = 0b11111;
byte off = 0b00000;
byte left[8] = {

	0b00100,
	0b10010,
	0b01111,
	0b10010,
	0b00010,
	0b00001,
	0b11111,
	0b11111
};

byte right[8] = {
	0b11111,
	0b11111,
	0b00001,
	0b00010,
	0b10010,
	0b01111,
	0b10010,
	0b00100
};
byte tree_empty_l_def[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111
};
byte tree_empty_r_def[8] = {
	0b11111,
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

byte tree_left_def[8] = {
	0b00000,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b11111,
	0b11111
};
byte tree_right_def[8] = {
	0b11111,
	0b11111,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b00000
};
byte full[8] = {
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
};
byte full2[8] = {
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
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  lcd.createChar(0, full);
  lcd.createChar(1, full2);
  lcd.createChar(2, left);
  lcd.createChar(3, right);
  lcd.createChar(tree_empty_l,tree_empty_l_def);
  lcd.createChar(tree_empty_r,tree_empty_r_def);
  lcd.createChar(tree_r,tree_right_def);
  lcd.createChar(tree_l,tree_left_def);
}

void draw_tree(int l, int c){

  //left
  if(c==-1){
  	lcd.setCursor(l,0);
    lcd.write((uint8_t)tree_l);
  	lcd.setCursor(l,1);
    lcd.write((uint8_t)tree_empty_r);
  }else if(c==1){
  	lcd.setCursor(l,0);
    lcd.write((uint8_t)tree_empty_l);
  }else if(c==0){
  	lcd.setCursor(l,0);
    lcd.write((uint8_t)tree_empty_l);
  	lcd.setCursor(l,1);
    lcd.write((uint8_t)tree_empty_r);
  }

  if(c>0){
    lcd.setCursor(l,1);
    lcd.write((uint8_t)tree_r);
  }else if(c>1){
    lcd.setCursor(l,0);
    lcd.write((uint8_t)tree_l);
  }
}
void draw(int l, int c){
  if(c==-1){
  	lcd.setCursor(l, 0);
    lcd.write((uint8_t)2);
    lcd.setCursor(l, 1);
    lcd.write((uint8_t)tree_empty_r);
  }
  if(c==1){
  	lcd.setCursor(l, 1);
    lcd.write((uint8_t)3);
    lcd.setCursor(l, 0);
    lcd.write((uint8_t)tree_empty_l);
  }
}
int i; int j;
void loop()
{
  //Limpa a tela
  //lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  if(millis()%2)draw(0,-1);
  else draw(0,1);
  for(i=0;i<3;i++){
  	draw_tree(1+(3*i),0);
  	draw_tree(2+(3*i),-1);
  	draw_tree(3+(3*i),1);
  }

  for(i=0;i<8;i++){
    full2[i]= (i<=j)?on:off;
  }
  lcd.createChar(1, full2);

  lcd.setCursor(11,0);
  lcd.write((uint8_t)0);
  lcd.setCursor(11,1);
  lcd.write((uint8_t)1);
  j++;
  j= j%8;
  delay(32);

}
