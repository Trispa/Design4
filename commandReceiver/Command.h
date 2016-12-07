#ifndef Command_h
#define Command_h
class Command
{
  public :
    Command();
	
	static void onOff();
    void arreterCommand();
    void demarrerCommand();
	
	static void modeCommande(); // interne ou externe
    void demarrerVentilateur(unsigned int pin);
	int getAllowCommande();
    void verifieSurIntensite(unsigned int pin);
	void allumerLed();
	static void  switchFreq();
    int lireTension(unsigned int pin);
    int getStatError();
	void setStatError(int val);
    int getSignalSurtension();
	int getAmp();
	bool defaultPeriode();
    static void errorInterrupt();
  private:
    int _stateErr;
    int _signalSurtension;
    int _allowCommande;
	int _amp;
};

#endif
