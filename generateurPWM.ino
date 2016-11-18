#include <commandReceiver.h>

#include "Arduino.h"
#define NECHANT 128
#define SHIFT_ACCUM 25

uint32_t icr;
uint32_t table_onde[NECHANT];
uint32_t table_onde2[NECHANT];
uint32_t table_onde3[NECHANT];
uint32_t accum1,accum2,accum3,increm;
uint16_t diviseur[6] = {0,1,8,64,256,1024};

Command  com; 
CommandReceiver cmr(&com);
//const float dephasage  = 2*3.1415926/3;
//const float ph1 = 2*3.1415926/NECHANT;
//const float ph2 = ph1 + dephasage/NECHANT;
//const float ph3 = ph2 + dephasage/NECHANT;



void init_pwm_timer1(uint32_t period) {
    char clockBits;
    TCCR1A = 0;
    TCCR1A |= (1 << COM1A1); //Clear OC1A on compare match when upcounting, set OC1A on compare match when downcounting
    TCCR1A |= (1 << COM1B1);
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
    TCCR1A |= (1 << COM1C1);
#endif
    TCCR1B = 1 << WGM13; // phase and frequency correct pwm mode, top = ICR1
    int d = 1;
    icr = (F_CPU/1000000*period/2);
    while ((icr>0xFFFF)&&(d<6)) { // choix du diviseur d'horloge
        d++;
        icr = (F_CPU/1000000*period/2/diviseur[d]);
   } 
   clockBits = d;
   ICR1 = icr; // valeur maximale du compteur
   TIMSK1 = 1 << TOIE1; // overflow interrupt enable
   sei(); // activation des interruptions
   TCNT1 = 0; // mise à zéro du compteur
   TCCR1B |= clockBits; // déclenchement du compteur
}
        
ISR(TIMER1_OVF_vect) { // Timer 1 Overflow interrupt
  accum1 += increm;
  accum2 += increm;
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
  accum3 += increm;
  OCR1C = table_onde3[accum3 >> SHIFT_ACCUM];
#endif
  OCR1A = table_onde[accum1 >> SHIFT_ACCUM];
  OCR1B = table_onde2[accum2 >> SHIFT_ACCUM];
  
}
        
void set_sinus_table(float amp) {
  int i;
  float dt = 2*3.1415926/NECHANT;
  for(i=0; i<NECHANT; i++) {
    table_onde[i] = icr*0.5*(1.0+amp*sin(i*dt));
    table_onde2[i] = icr*0.5*(1.0+amp*sin(i*dt + 2.0944));
    table_onde3[i] = icr*0.5*(1.0+amp*sin(i*dt + 4.189));
    
  }  

}
       
void setup() {
  Serial.begin(115200);
#if defined(__AVR_ATmega2560__)
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
#elif defined(__AVR_ATmega32U4__)
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
#else
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
#endif
    uint32_t period_pwm = 80; // en microsecondes
    uint32_t frequence = 100; // en Hz
    accum1 = 0;
    accum2 = ((uint32_t)(NECHANT * 0.25)) << SHIFT_ACCUM;
    accum3 = 0;
    increm = (uint32_t) (((float)(0xFFFFFFFF))*((float)(frequence)*1e-6*(float)(period_pwm))); // incrément de l'accumulateur de phase
    init_pwm_timer1(period_pwm);
    set_sinus_table(1.0);
}
        
void loop() {
    cmr.process();
}
        
