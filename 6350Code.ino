#include <LiquidCrystal.h>

int HR_Dig_Pin = A1;
int RR_Dig_Pin = A3;

int E=10;
int RW=9;
int RS=8;

int DBPins[] = {0, 1, 2, 3, 4, 5, 6, 7};
/*
int DB7=7;
int DB6=6;
int DB5=5;
int DB4=4;
int DB3=3;
int DB2=2;
int DB1=1;
int DB0=0;
*/

LiquidCrystal lcd(RS, RW, E, 4, 5, 6, 7);

int HR_Dig_State_Old=0;
int HR_Dig_State=0;
int RR_Dig_State_Old=0;
int RR_Dig_State=0;
int HR;
int RR;
int SUMHR=0;
int SUMRR=0;
int n = 1;
int j = 1;
int x = 1;

float end_time=0.0;
float begin_time=0.0;
float end_time2=0.0;
float begin_time2=0.0;


void setup() {
  Serial.begin(9600);
  pinMode(HR_Dig_Pin, INPUT);
  pinMode(RR_Dig_Pin, INPUT);
  /*
  pinMode(E, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(DB7, OUTPUT);
  pinMode(DB6, OUTPUT);
  pinMode(DB5, OUTPUT);
  pinMode(DB4, OUTPUT);
  pinMode(DB3, OUTPUT);
  pinMode(DB2, OUTPUT);
  pinMode(DB1, OUTPUT);
  pinMode(DB0, OUTPUT);
  */


  lcd.begin(8, 2);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("6350");
  lcd.setCursor(0, 1);
  lcd.print("PPG--HR");  
}

void loop() {
  HR_Dig_State_Old=HR_Dig_State;
  RR_Dig_State_Old=RR_Dig_State;
  HR_Dig_State=analogRead(HR_Dig_Pin);
  RR_Dig_State=analogRead(RR_Dig_Pin); 

  if(HR_Dig_State-HR_Dig_State_Old>=200){
    if(n<=3&&n>=2){
      lcd.setCursor(0,0);
      lcd.print("Wait....");
    }

    end_time=begin_time;
    begin_time=(float) millis();

    if(n>=2&&60000/(begin_time-end_time)>=60&&60000/(begin_time-end_time)<=140){
      //lcd.clear();
      SUMHR=60000/(begin_time-end_time)+SUMHR;
      HR=SUMHR/j;
      j=j+1;
      Serial.println("HEART=");
      Serial.println(HR);
      lcd.setCursor(0,0);
      lcd.print("HR");
      lcd.print(HR);
      lcd.print("bpm");
    }
    n=n+1;
  }
  
  if(RR_Dig_State-RR_Dig_State_Old>=200){
    if(x<=3&&x>=2){
      lcd.setCursor(0,1);
      lcd.print("Wait....");
    }
    end_time2=begin_time2;
    begin_time2=(float) millis();
    RR = 60000.0/(begin_time2-end_time2);
    if(x>=2&&60000/(begin_time2-end_time2)>=5&&60000/(begin_time2-end_time2)<=25){
      //lcd.clear();
      Serial.println("BREATHE=");
      Serial.println(RR);
      lcd.setCursor(0,1);
      lcd.print("RR");
      lcd.print(RR);
      lcd.print("brpm");
    }
  x=x+1;
  }
}
