#include <Command.h>

#include <generateurPWM.h>

Command  com;   
int pinLEDBreaker = 27;
GenerateurPWM genererateurpwm;
int pinAD = 41; // pin allimention drivers
int Vprech = 23 ; // doit etre mis a 1 si pinVDCBus est a 1 pour fermer les relais afin de court circuiter les resistance
int vMod = A2;//pin analog relier au potentiometre
float  sensorAmpValue;
int allowCommand =0;

  ISR(TIMER1_OVF_vect) {
      if(allowCommand == 1){
      genererateurpwm.accum1 += genererateurpwm.increm;
      genererateurpwm.accum2 += genererateurpwm.increm;
      
      #if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
        genererateurpwm.accum3 += genererateurpwm.increm;
        OCR1C = genererateurpwm.table_onde3[genererateurpwm.accum3 >> SHIFT_ACCUM];
      #endif
        OCR1A = genererateurpwm.table_onde[genererateurpwm.accum1  >> SHIFT_ACCUM];
        OCR1B = genererateurpwm.table_onde2[genererateurpwm.accum2 >> SHIFT_ACCUM];
  }
}

void setup() {
    Serial.begin(115200);
    //pinMode(pinFreq, INPUT);
#if defined(__AVR_ATmega2560__)
    pinMode(11,OUTPUT);// pin 11 : pwm1
    pinMode(12,OUTPUT);// pin 12 : pwm2
    pinMode(13,OUTPUT);// pin 13 : pwm3
#endif
    pinMode(Vprech,OUTPUT);
    pinMode(pinAD,OUTPUT);
    pinMode(pinLEDBreaker, OUTPUT);
    pinMode(vMod, INPUT);
    initialize();
    delay(3000);
    if((genererateurpwm.get_period_pwm() != 0) && (digitalRead(Vprech) == LOW)&& (digitalRead(pinAD) == LOW)){
        allumerLedBreaker(pinLEDBreaker);  
        delay(3000);
        allowCommand = 1;
       
    }
    genererateurpwm.init_pwm_timer1();
    genererateurpwm.set_sinus_table(0.5);
    
}

void loop() {
  com.process();
  sensorAmpValue = analogRead(vMod);
  if(com.getAllowModulation()){
  genererateurpwm.set_sinus_table(sensorAmpValue/1024);
  }
}
void initialize(){
  allowCommand = 0;
  digitalWrite(Vprech, LOW);
  digitalWrite(pinAD, LOW);
}
void allumerLedBreaker(int pinVal){
 digitalWrite(pinVal,HIGH); 
}

