/*
Cyrstal
Использование символа "начало новой строки"

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)

Sketch uses 5,656 bytes (17.5%) of program storage space. Maximum is 32,256 bytes.
Global variables use 57 bytes (2.8%) of dynamic memory, leaving 1,991 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;


void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  lcd->init(F("Привет мир!\rЯ Ардуино Уно =)"));
  lcd->printn(0);
  lcd->go(0, 1);
  lcd->printn(1);
}
void loop(){
}