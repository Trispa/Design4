#include "generateurPWM.h"

 

void GenerateurPWM::init_pwm_timer1(uint32_t period) {
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

        
void GenerateurPWM::set_sinus_table(float amp) {
  int i;
  float dt = 2*3.1415926/NECHANT;
  for(i=0; i<NECHANT; i++) {
    table_onde[i] = icr*0.5*(1.0+amp*sin(i*dt));
    table_onde2[i] = icr*0.5*(1.0+amp*sin(i*dt + 0.5)); // Par essai erreur la valeur de 0,5 donne le bon dephasage du signal 1 par rapport au signal 2
    table_onde3[i] = icr*0.5*(1.0+amp*sin(i*dt - 2.1)); // Par essai erreur la valeur de - 2.1 donne le bon dephasage du signal 1 par rapport au signal 2
    //Serial.println(table_onde3[i]); 
  } 
}