/**
 * author: Jakub Chaba
 * file: distancelcd.ino
 * 
 * This code is for an Ardiuno project that measures distance up to 400cm and displays it on a
 * liquid crystal display.
 * 
 * Distance is measured using a HC-SR04 ultrasonic sensor interfacing with an Ardiuno Uno.
 */
 
// library for interfacing with liquid crystal display
#include <LiquidCrystal.h>
// library for creating a bar graph on the lcd to provide visual feedback of distance 
#include <LcdBarGraph.h>
// library for interfacing with HC-SR04 module
#include <NewPing.h>

// constant for pin 9 on ardiuno for data from trigonometric data from HC-SR04
#define TRIGGER_PIN 9
// constant for pin 10 on ardiuno for data from echo data from HC-SR04
#define ECHO_PIN 10

// constant for maximum distance HC-SR04 can measure which is 400cm or 4m
#define MAX_DISTANCE 400


// variable for interfacing with HC-SR04
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
// variable for distance
float distance;
// variable for rounding distance, ignoring decimals
int dis;

// initialize variable for liquid crystal display
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

// initalize variable for creating bar graph, set width to 16, set location to col 0 row 1
LcdBarGraph lbg(&lcd, 16, 0, 1);

/**
 * inital setup
 * initliaze ardiuno running at 9600 bits/second
 * initalize lcd interfacing with 16 columns and 2 rows
 */
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

/**
 * code that runs in loop while ardiuno is active
 */
void loop() {
  // call function ping_cm() to get distance from ultrasonic module, set distance to variable
  distance = sonar.ping_cm();
  // set lcd cursor to row 0, column 0
  lcd.setCursor(0, 0);
  // print text for user inteface
  lcd.print("Distance: ");
  // convert float from ping_cm() call to integer variable to remove decimals
  dis = distance;
  // check if distance is outside of bounds, if so, print RANGE!
  if (distance >= MAX_DISTANCE || distance <= 2){
    lcd.print("RANGE!");
  } else {
    // if distance is within bounds, print value and append 'cm'
    lcd.print(dis);
    lcd.print("cm");
    if (dis < 10){
      // if distance is one-digit value, append 4 spaces to clear any leftover lcd data
      lcd.print("   ");
    } else if (dis > 10 && dis < 100){
      // if distance is two-digit value, append 3 spaces to clear any leftover lcd data
      lcd.print("  ");
    } else {
      // if distance is three-digit value, append 1 space to clear any leftover lcd data
      lcd.print(" ");
    }
    // draw the bar graph showing current distance from a scale of 0 to max distance
    lbg.drawValue(distance, MAX_DISTANCE);
  }
  // wait 500ms before checking distance again
  delay(500);
}
