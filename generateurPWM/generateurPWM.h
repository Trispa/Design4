#ifndef GENERATEURPWM_H
#define GENERATEURPWM_H
#include "Arduino.h"
#define NECHANT 128
#define SHIFT_ACCUM 25

class GenerateurPWM{
	
	public: 
		GenerateurPWM();
		void init_pwm_timer1();
		void set_sinus_table (float amp);
		uint32_t icr;
		uint32_t table_onde[NECHANT];
		uint32_t table_onde2[NECHANT];
		uint32_t table_onde3[NECHANT];
		uint32_t accum1,accum2,accum3,increm;
		uint16_t diviseur[6] = {0,1,8,64,256,1024};
		void set_period_pwm(uint32_t period_pwm);
		uint32_t get_period_pwm();
		void set_frequence(uint32_t freq);
	private:
		uint32_t  _period_pwm = 0 ;
		uint32_t _frequence ;
		
	
};

#endif