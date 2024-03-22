#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
//Setup the LCD for WaterTemperature
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Hi HIGH
#define Lo LOW
bool waterflow = false;
bool doorClosed = false;
bool waterTempOK = false; //True if water Temp is between 10 and 30 °C
void setup() {
  sensors.begin();
  water_flows();
  door_closed();
  water_Temp_OK();
  while(waterflow == false || doorClosed == false || waterTempOK == false){
    water_flows();
    door_closed();
    water_Temp_OK();
  }
 

}

void setup_display(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
}

bool water_flows(){   //Überprüft ob das Wasser durch den Durchflussmesser fließt
  if(digitalRead(22) == Hi){ //Auf Pin 22 den Durchflussmesser mit Low-Pass-Filter anschließen
    digitalWrite(23, Hi); //Pin 23 = Grünes Bein LED
    digitalWrite(25, Lo); //Pin 25 = Rotes Bein LED
    waterflow = true;
  }
  else{ //Rot an Grün aus, Freigabe auf Falsch
    digitalWrite(23, Lo); //Pin 23 = Grünes Bein LED
    digitalWrite(25, Hi); //Pin 25 = Rotes Bein LED
    waterflow = false;
  }
}

bool door_closed(){     //Überprüft ob der / die Reed-Sensoren der Tür geschlossen sind
  if(digitalRead(26) == Hi){
    digitalWrite(24, Lo); //Rotes Bein Led
    digitalWrite(27, Hi); //Grünes Bein Led
  }
  else{
    digitalWrite(24, Hi);
    digitalWrite(27, Lo);
  }
}

void set_pins(){  

}


void loop() {
  // put your main code here, to run repeatedly:

}

float water_temp_in_C(){
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void water_Temp_OK(){
  lcd.clear();
  String temp = String((((int)(water_temp_in_C() * 100 ))/ 100.0));
  String all = "WaterTemp: " + temp + " C";
  lcd.setCursor(0, 0);
  lcd.print(all); // Gets the Temperature and displays it in the first Row
  if(water_temp_in_C() <= 10){
    lcd.setCursor(0, 1);
    lcd.print("TOO LOW TEMP!"); //Displays that the Temp is too low if it is below 10 °C
    waterTempOK = false;
  }
  else if(water_temp_in_C() >= 30){
    lcd.setCursor(0, 1);
    lcd.print("TOO HIGH TEMP!"); //Displays that the Temp is too high if it is above 30 °C
    waterTempOK = false;
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print("Temp OK"); //Displays that the Temperature is OK if it is between the two above
    waterTempOK = true;
  }
}


