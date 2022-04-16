# define GREEN 2
  # define ORANGE 3
  # define RED 4
  # define Buzzer 5
  # define Sensor A0

#include <LiquidCrystal.h>
  LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

 int sensor_Input;
  float temp;
bool gasLeak = false;
bool tempHigh = false;

  void setup() {
    for (int i = 2; i < 6; i++)
      pinMode(i, OUTPUT);

    Serial.begin(9600);
    lcd.begin(16, 2);
  }

  void loop() {

    for (int i = 2; i < 6; i++)
      digitalWrite(i, LOW);

    status_Indicator();
    display_All();
  }

  void status_Indicator()
  {
    int sensor_In = analogRead(A0);
    sensor_Input = analogRead(A1);
    temp = (float)sensor_Input / 1024;
    temp = temp * 5;
    temp = temp - 0.5;
    temp = temp * 100;
    Serial.println(sensor_In);

    if ( sensor_In >=40  )
    {
      digitalWrite(RED, HIGH);
      digitalWrite(Buzzer,HIGH);
      gasLeak = true;
    }
    else if (sensor_In >=25 )
    {
      digitalWrite(ORANGE, HIGH);
    } else if (sensor_In<25 && temp<35)
    {
      digitalWrite(GREEN, HIGH);
      tempHigh = false;
      gasLeak=false;
    }
    
    if ( temp >=45  )
    {
      digitalWrite(RED, HIGH);
      digitalWrite(Buzzer,HIGH);
      digitalWrite(GREEN, LOW);
      tempHigh = true;
    }
    else if (temp >=35 )
    {
      digitalWrite(ORANGE, HIGH);

       lcd.setCursor(0, 0);
    } else if (temp<35 && sensor_In<25 )
    {
      digitalWrite(GREEN, HIGH);
      tempHigh = false;
      gasLeak = false;
    }
    delay(10);
  }


  void display_All()
  {
    lcd.setCursor(0,0);
      if (tempHigh && gasLeak)
    {
      Serial.print("Danger!Danger! Danger!");
      Serial.print(temp);
        Serial.println();
      lcd.print("Danger!Danger! Danger!");
      lcd.setCursor(5, 1);
      lcd.print(temp);
      delay(500);
    }
    else if (gasLeak)
    {
      Serial.print("Danger!Gas Leak!");
        Serial.println();
      lcd.print("Danger!Gas Leak!");
      lcd.setCursor(5, 1);
      delay(500);
    }
    else if (tempHigh)
    {
      Serial.print("Danger!High temp!");
      Serial.print(temp);
        Serial.println();
      lcd.print("Danger!High temp!");
      lcd.setCursor(5, 1);
      lcd.print(temp);
      delay(500);
    }
    else
    {
      Serial.print("Temp. in Celcius: ");
    Serial.print(temp);
    Serial.println();
    lcd.print("Temp. in Celcius: ");
    lcd.setCursor(5, 1);
    lcd.print(temp);
    delay(500);
    }
  }