#include <LiquidCrystal.h> 
int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
const int trigPin = A3;
const int echoPin = A2;
#define uv1 10
#define uv2 9
#define irU 7
#define irD 8
# define m1 A0
# define m2 A1



void setup() 
{
     analogWrite(6,Contrast);
     lcd.begin(16, 2);
     pinMode(trigPin, OUTPUT);
     pinMode(echoPin, INPUT);
     pinMode(irU, INPUT);
     pinMode(irD, INPUT);
     pinMode(uv1, OUTPUT);
     pinMode(uv2, OUTPUT);
     Serial.begin(9600);
}

void loop() 
{
  dispMsg(1);
  if (irD == 1)
  {
    dispMsg(2);
    lidOpen();
    delay(2000);
    dispMsg(3);
    uvOn();
  }
}
int distanceCalc()
{ long duration; // variable for the duration of sound wave travel
  int distance;
  ̥̥̥̥̥̥digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  return distance;
}

void dispMsg(int x)
{
  if (x == 1)
  { char str = "Put Your Hand in Front Of box" ;
    lcd.autoscroll();
    lcd.setCursor(0, 0);
    lcd.print("Put Your Hand in Front Of")
  }
  if (x == 2)
  {
    lcd.autoscroll();
    lcd.setCursor(0, 0);
    lcd.print("box is opening");
  }
  if (x == 3)
  {
    lcd.autoscroll();
    lcd.setCursor(0, 0);
    lcd.print("Put Objects In Box");
  }
  if (x == 4)
  {
    lcd.autoscroll();
    lcd.setCursor(0, 0);
    lcd.print("Sanitization in progress");
  }
   if (x == 5)
  {
    lcd.autoscroll();
    lcd.setCursor(0, 0);
    lcd.print("Sanitization copleted");
  }
  if (x == 6)
  {
    lcd.setCursor(0, 0);
    lcd.print("Wait few seconds");
  }
  

  
}


void uvOn()
{
    if (digitalRead(irU)==0)
    {
      int d;
      d = distanceCalc();
      if (d < 10)
      {
        delay(2000);
        lidClose();
        dispMsg(4);
        digitalWrite(uv1, HIGH);
        digitalWrite(uv2, HIGH);
        delay(10000);
        uvOff();
      }  
    } 
}

void uvOff()
{
  digitalWrite(uv2, LOW);
  digitalWrite(uv2, LOW);
  dispMsg(5);
  lidOpen();
  
}
void lidClose()
{
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  delay(3000);
}
 
void lidOpen()
{
  if(digitalRead(uv1)==1 && digitalRead(uv2) == 1)
  {
    digitalWrite(m2, HIGH);
    digitalWrite(m1, LOW);
    delay(3000);
  }
  else
  {
    dispMsg(6);
    delay(3000);
  }
}

