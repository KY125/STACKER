//Author: Jackson Spry
//note: this is not polished, infact, there is a misfeature where the platform is not erased if it overhangs more than 1
#include <LedControl.h>
#include "binary.h"
LedControl lc = LedControl(14, 13, 12, 4);
int i = 0, SW_pin = 15, a = 0, x = 7, y = 6, butpress = 1, dir = 0,
    sto_x = 0, leh = 4, d = 0, sta = 1;
void setup() {
  while (i < 4) { //Loop to initiate and clear all displays
    lc.shutdown(i, false);
    lc.setIntensity(i, 6);
    lc.clearDisplay(i);
    i++;
  }
  i = 0;
  pinMode(SW_pin, INPUT); //button pin
}
void checkfall() {
  if (x != sto_x) { //If x is not equal to the previous x value
    lc.setLed(a, sto_x - leh, y + 2, 0); //erase the overhange
    lc.setLed(a, sto_x - leh, y + 3, 0);
    lc.setLed(a, sto_x + 1, y + 2, 0);
    lc.setLed(a, sto_x + 1, y + 3, 0);
    leh = leh - abs(x - sto_x); //subtract the difference in x from the length
    if (x > sto_x) { //if x overhangs to the left
      x = x - abs(x - sto_x); //shift x to be on the tower
      sto_x = x; //set previous x value
    }
  }
  sto_x = x; //set previous x value
}
void loop() {
  while (digitalRead(SW_pin) == LOW) { //while the button is not pressed
    delay(96 - 2 * ((a * 8) + (8 - y))); //variable delay to make it speed up the higher you go
    butpress = 1; //button lock variable on
    if (x < 0 || x > 6 + leh) { //if the platform is off the screen
      dir = abs(dir - 1); //switch the direction
    }
    if (dir == 0) { 
      x--; //incriment the platform right if the dir is 0
      lc.setLed(a, x + 1, y, 0); //erase the platform trail
      lc.setLed(a, x + 1, y + 1, 0);
    }
    else {
      x++; //incriment the platform left if the dir is 1
      lc.setLed(a, x - leh, y, 0); //erase the platform trail
      lc.setLed(a, x - leh, y + 1, 0);
    }
    while (d < leh) { //loop to draw the platform based off the length
      lc.setLed(a, x - d, y, 1); //top pixel
      lc.setLed(a, x - d, y + 1, 1); //bottom pixel
      d++;
    }
    d = 0;
  }
  if (y < 0) { //if y goes off the screen, warp to next sceen
    a++; //incriment screen address
    y = 6; //set y to bottom value
  }
  if (digitalRead(SW_pin) == HIGH && butpress == 1) { //activate once when button is pressed
    if (sta == 1) { //if its the first press of the game)
      sta = 0;
      sto_x = x;
    }
    y = y - 2; //move y up two pixels 
    butpress = 0;
    checkfall(); //check for misalignment
  }
}


