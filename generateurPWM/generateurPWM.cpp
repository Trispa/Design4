#include "generateurPWM.h"

 
GenerateurPWM::GenerateurPWM(){
	this->_period_pwm = (digitalRead(50) == HIGH)?80:160;
	this->_frequence = 60;
	this->accum1 = 0;
	this->accum2 = ((uint32_t)(NECHANT * 0.25)) << SHIFT_ACCUM;
	this->accum3 = 0;
	this->increm = (uint32_t) (((float)(0xFFFFFFFF))*((float)(this->_frequence)*1e-6*(float)(this->_period_pwm))); // incrément de l'accumulateur de phase		
}

void GenerateurPWM::set_period_pwm(uint32_t period_pwm){
	this->_period_pwm = period_pwm;
}
uint32_t GenerateurPWM::get_period_pwm(){
	return this->_period_pwm;
}
void GenerateurPWM::set_frequence(uint32_t frequence){
	this->_frequence = frequence;
}
	
void GenerateurPWM::init_pwm_timer1() {
    char clockBits;
    TCCR1A = 0;
    TCCR1A |= (1 << COM1A1); //Clear OC1A on compare match when upcounting, set OC1A on compare match when downcounting
    TCCR1A |= (1 << COM1B1);
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
    TCCR1A |= (1 << COM1C1);
#endif
    TCCR1B = 1 << WGM13; // phase and frequency correct pwm mode, top = ICR1
    int d = 1;
    icr = (F_CPU/1000000*this->_period_pwm/2);
    while ((icr>0xFFFF)&&(d<6)) { // choix du diviseur d'horloge
        d++;
        icr = (F_CPU/1000000*this->_period_pwm/2/diviseur[d]);
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