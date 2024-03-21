#define Hi HIGH
#define Lo LOW
bool waterflow = false;
bool doorClosed = false;
void setup() {
  water_flows();
  door_closed();
  while(waterflow == false || doorClosed == false){
    water_flows();
    door_closed();
  }
 

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
