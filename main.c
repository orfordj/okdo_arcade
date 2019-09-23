//include the library for the LED strip from Adafruit
#include <Adafruit_NeoPixel.h>

//define the time between each bullet movement
#define bullet_step_time 30 //milliseconds

//initiate all of the objects for the LED strips (buttons still considered as strips even though there is only 1 button)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(29, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(29, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(29, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(29, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel button1 = Adafruit_NeoPixel(29, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel button2 = Adafruit_NeoPixel(29, 5, NEO_GRB + NEO_KHZ800);

//define an array to hold the value for red, green and blue
const uint32_t rgb[3] = {strip1.Color(255, 0, 0), strip1.Color(0, 255, 0), strip1.Color(0, 0, 255)};

//a function which allows for you to write a specific pixel of one of the four strips to a colour
void strip_pixel(uint32_t c, char which, char num) {
  switch (which) {
    case 0:
      strip1.setPixelColor(num, c);
      break;
    case 1:
      strip2.setPixelColor(num, c);
      break;
    case 2:
      strip3.setPixelColor(num, c);
      break;
    case 3:
      strip4.setPixelColor(num, c);
      break;
  }
}

//set the first led of the four strips to yellow
void yellow() {
  strip1.setPixelColor(0, strip1.Color(255, 200, 0));
  strip2.setPixelColor(0, strip1.Color(255, 200, 0));
  strip3.setPixelColor(0, strip1.Color(255, 200, 0));
  strip4.setPixelColor(0, strip1.Color(255, 200, 0));
}

//a function which load the four main strips one by one then buttons to red then fade to black leaving the buttons on
void start_red() {
  //show all the strips as 0,0,0 (black)
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();

  int i;
  //fade strip 1 in
  for (i = 0; i < strip1.numPixels(); i++) {
    strip1.setPixelColor(i, strip1.Color(255, 0, 0));
  }
  strip1.show();
  delay(500); //wait half a second before next one

  //fade strip 2 in
  for (i = 0; i < strip2.numPixels(); i++) {
    strip2.setPixelColor(i, strip1.Color(255, 0, 0));
  }
  strip2.show();
  delay(500); //wait half a second before next one

  //fade strip 3 in
  for (i = 0; i < strip3.numPixels(); i++) {
    strip3.setPixelColor(i, strip1.Color(255, 0, 0));
  }
  strip3.show();
  delay(500); //wait half a second before next one

  //fade strip 4 in
  for (i = 0; i < strip4.numPixels(); i++) {
    strip4.setPixelColor(i, strip1.Color(255, 0, 0));
  }
  strip4.show();
  delay(500); //wait half a second before next one

  //fade buttons in
  for (i = 0; i < button1.numPixels(); i++) {
    button1.setPixelColor(i, strip1.Color(255, 0, 0));
    button2.setPixelColor(i, strip1.Color(255, 0, 0));
  }
  button1.show();
  button2.show();

  //fade all four strips to 0,0,0 (black)
  for (int k = 255; k > 0; k--) {
    for (int i = 0; i < strip1.numPixels(); i++) {
      strip1.setPixelColor(i, strip1.Color(k, 0, 0));
      strip2.setPixelColor(i, strip1.Color(k, 0, 0));
      strip3.setPixelColor(i, strip1.Color(k, 0, 0));
      strip4.setPixelColor(i, strip1.Color(k, 0, 0));
    }
    //update strips
    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
  }
}

//function to deal with the rainbow at boot
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

//j is the global variable which holds the current position in the rainbow
uint16_t j = 0;

//function which acts as a global for loop to handle the rainbow operation
void rainbow(void) {
  uint16_t i;
  //updates the colour of each pixel in the strip of each strip
  for (i = 0; i < strip1.numPixels(); i++) {
    strip1.setPixelColor(i, Wheel((i + j) & 255));
    strip2.setPixelColor(i, Wheel((i + j) & 255));
    strip3.setPixelColor(i, Wheel((i + j) & 255));
    strip4.setPixelColor(i, Wheel((i + j) & 255));
    button1.setPixelColor(i, Wheel((i + j) & 255));
    button2.setPixelColor(i, Wheel((i + j) & 255));
  }

  //as this acts as a global for loop, j's limits must be checked and kept below 256
  j++;
  if (j > 256) {
    j = 0;
  }

  //update the led strips
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  button1.show();
  button2.show();
  //delay(100);
}

//setup the arduino
void setup() {
  //start serial with 9600 baud
  Serial.begin(9600);

  //initiate all of the led strip objects
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  button1.begin();
  button2.begin();

  //show all of the strips with 0,0,0 (black) (good practice to do)
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  button1.show();
  button2.show();

  //A0 acts as a noise generator and shouldn't be connected to anything, it acts to generate random noise
  pinMode(A0, INPUT); //noise generator

  //all of the buttons are declared as inputs
  //change these values if you solder them the wrong way round!
  pinMode(12, INPUT);//blue button
  pinMode(11, INPUT);//green button
  pinMode(10, INPUT);//red button
  pinMode(A2, INPUT);//button 1
  pinMode(A3, INPUT);//button 2
  pinMode(A4, INPUT);//button 3
  pinMode(A5, INPUT);//button 4
}

//declare all the global variables
uint32_t current_color = strip1.Color(255, 0, 0);
char lives = 3;
unsigned char level = 1; //max level is 8 (max number of meteors)
//speed of meteors random but relative to level, i.e faster if higher level
unsigned char speed_times[8] = {170, 170, 160, 150, 140, 120, 100, 80}; //minimum meteor time
long int score = 0;

//array to hold all the position and step data of the meteors and bullets
//bullet position,bullet in flight?, meteor 1 position, meteor 2 position, meteor step time 1, meteor step time 2
unsigned int mega_strip[4][7] = {{0, 0, 30, 30, 200, 200},
  {0, 0, 30, 30, 200, 200},
  {0, 0, 30, 30, 200, 200},
  {0, 0, 30, 30, 200, 200}
};

//array to hold all the colours of the meteors and bullets
uint32_t colors[4][3] = {{strip1.Color(0, 0, 0), strip1.Color(255, 0, 0), strip1.Color(255, 0, 0)},
  {strip1.Color(0, 0, 0), strip1.Color(255, 0, 0), strip1.Color(255, 0, 0)},
  {strip1.Color(0, 0, 0), strip1.Color(255, 0, 0), strip1.Color(255, 0, 0)},
  {strip1.Color(0, 0, 0), strip1.Color(255, 0, 0), strip1.Color(255, 0, 0)}
};

//array to hold all the meteor speeds
unsigned long int meteor_tickers[4][2] = {{millis(), millis()},
  {millis(), millis()}, {millis(), millis()}, {millis(), millis()}
};

//a function to reset the game when you lose as variables are global
void setup_stuff() {
  for (int i = 0; i < 4; i++) {
    for (int p = 0; p < 3; p++) {
      colors[i][p] = rgb[0];
    }
    mega_strip[i][0] = 0;
    mega_strip[i][1] = 0;
    mega_strip[i][2] = 30;
    mega_strip[i][3] = 30;
    mega_strip[i][4] = 200;
    for (int p = 0; p < 2; p++) {
      meteor_tickers[i][p] = millis();
    }
  }
}

//record start time for the timer variables
unsigned long int meteor_ticker = millis();
unsigned long int level_ticker = millis();
unsigned long int bullet_ticker = millis();

//a function which returns the number of meteors in play
char num_meteors(void) {
  char temp = 0;
  for (int p = 0; p < 4; p++) {
    for (int i = 0; i < 2; i++) {
      if (mega_strip[p][i + 2] != 30) {
        temp++;
      }
    }
  }
  return temp;
}

//main program loop
void loop() {
  //have the rainbow change colour whilst checking if buttons have been pressed
  if (millis() - meteor_ticker > 100) {
    rainbow();
    meteor_ticker = millis(); //reset counter
  }

  //if any of the buttons are read low, it means they have been pressed as they are normally pulled high
  if (digitalRead(A2) == LOW || digitalRead(A3) == LOW || digitalRead(A4) == LOW || digitalRead(A5) == LOW || digitalRead(10) == LOW || digitalRead(11) == LOW || digitalRead(12) == LOW) {
    //call the function to fade the bars to red one by one
    start_red();

    //reset all of the timers and variables
    level_ticker = millis();
    meteor_ticker = millis();
    bullet_ticker = millis();
    setup_stuff();
    lives = 3;
    level = 1;
    score = 0;

    //seed the random number generator using the time passed since power on, and the value from the noise generator (A0)
    randomSeed(analogRead(A0)*millis());
    
    while (lives > 0) {
      for (int i = 0; i < strip1.numPixels(); i++) {
        strip1.setPixelColor(i, strip1.Color(0, 0, 0));
        strip2.setPixelColor(i, strip1.Color(0, 0, 0));
        strip3.setPixelColor(i, strip1.Color(0, 0, 0));
        strip4.setPixelColor(i, strip1.Color(0, 0, 0));
      }

      yellow();

      //change current color using buttons
      if (digitalRead(10) == LOW) {
        current_color = strip1.Color(255, 0, 0);
      } else if (digitalRead(11) == LOW) {
        current_color = strip1.Color(0, 255, 0);
      } else if (digitalRead(12) == LOW) {
        current_color = strip1.Color(0, 0, 255);
      }

      if (digitalRead(A2) == LOW && mega_strip[0][1] == 0) {
        mega_strip[0][1] = 1;
        colors[0][0] = current_color;
        score -= 50;
      }
      if (digitalRead(A3) == LOW && mega_strip[1][1] == 0) {
        mega_strip[1][1] = 1;
        colors[1][0] = current_color;
        score -= 50;
      }
      if (digitalRead(A4) == LOW && mega_strip[2][1] == 0) {
        mega_strip[2][1] = 1;
        colors[2][0] = current_color;
        score -= 50;
      }
      if (digitalRead(A5) == LOW && mega_strip[3][1] == 0) {
        mega_strip[3][1] = 1;
        colors[3][0] = current_color;
        score -= 50;
      }

      for (int i = 0; i < button1.numPixels(); i++) {
        button1.setPixelColor(i, current_color);
        button2.setPixelColor(i, current_color);
      }
      button1.show();
      button2.show();

      //should I spit out a meteor?
      if (num_meteors() < level &&  random(0, 6) == 2) {
        char temp_meteor = random(0, 4);
        if (mega_strip[temp_meteor][2] == 30) {
          mega_strip[temp_meteor][2] = 29;
          char temp = level > 3 ? level - 3 : level;
          mega_strip[temp_meteor][5] = random(speed_times[level - 1], speed_times[temp]); //random speed of meteor

          colors[temp_meteor][1] = rgb[random(0, 3)];
        } else if (mega_strip[temp_meteor][3] == 30) {
          mega_strip[temp_meteor][3] = 29;
          colors[temp_meteor][2] = rgb[random(0, 3)];
          char temp = level > 3 ? level - 3 : level;
          mega_strip[temp_meteor][6] = random(speed_times[level - 1], speed_times[temp]); //random speed of meteor
        }
      }

      //go through each strip and check data
      for (int i = 0; i < 4; i++) {
        //movement time of bullets
        if (mega_strip[i][1] == 1 && millis() - bullet_ticker > bullet_step_time) {
          mega_strip[i][0] += 1;
        }

        //meteor movement
        if (mega_strip[i][2] < 30 && millis() - meteor_tickers[i][0] > mega_strip[i][5]) {
          meteor_tickers[i][0] = millis();
          mega_strip[i][2] -= 1;
        }
        if (mega_strip[i][3] < 30 && millis() - meteor_tickers[i][1] > mega_strip[i][6]) {
          meteor_tickers[i][1] = millis();
          mega_strip[i][3] -= 1;
        }

        //check if meteor hits yellow
        if (mega_strip[i][2] <= 0) {
          lives -= 1;
          mega_strip[i][2] = 30;
        }
        if (mega_strip[i][3] <= 0) {
          lives -= 1;
          mega_strip[i][3] = 30;
        }

        //update meteor on screen
        if (mega_strip[i][2] < 30 && mega_strip[i][2] > 0) {
          strip_pixel(colors[i][1], i, mega_strip[i][2]);
        }
        if (mega_strip[i][3] < 30 && mega_strip[i][3] > 0) {
          strip_pixel(colors[i][2], i, mega_strip[i][3]);
        }

        //update bullet on screen
        if (mega_strip[i][0] < 30 && mega_strip[i][0] > 0 && mega_strip[i][1] == 1) {
          strip_pixel(colors[i][0], i, mega_strip[i][0]);
        }

        //check if bullet flew off screen
        if (mega_strip[i][0] >= 30) {
          mega_strip[i][1] = 0; //no bullet in flight
          mega_strip[i][0] = 0; //reset position to 0
        }

        //check if bullet hit meteor 1
        if (mega_strip[i][0] >= mega_strip[i][2] && mega_strip[i][1] == 1) {
          if (colors[i][0] == colors[i][1]) {
            score += 200; //score 200 for correct color hit
            mega_strip[i][2] = 30; //destroy meteor
          } else {
            score -= 100; //wrong color loses 100 points
            //meteor not destroyed
          }
          mega_strip[i][1] = 0; //no bullet in flight
          mega_strip[i][0] = 0; //reset position to 0
        }

        //check if bullet hit meteor 2
        if (mega_strip[i][0] >= mega_strip[i][3] && mega_strip[i][1] == 1) {
          if (colors[i][0] == colors[i][2]) {
            score += 200; //score 200 for correct color hit
            mega_strip[i][3] = 30; //destroy meteor
          } else {
            score -= 100; //wrong color loses 100 points
            //meteor not destroyed
          }
          mega_strip[i][1] = 0; //no bullet in flight
          mega_strip[i][0] = 0; //reset position to 0
        }
      }

      //update level
      if (millis() - level_ticker > 5000) {
        level_ticker = millis();
        level += 1;
      }

      strip1.show();
      strip2.show();
      strip3.show();
      strip4.show();
    }
    for (int i = 0; i < 3; i++) {
      Serial.println(score);
      delay(1000);
    }
  }
}
