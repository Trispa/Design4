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
	int switchFreq(unsigned int pin);
    int lireTension(unsigned int pin);
    int getStatError();
    int getSignalSurtension();
    static void errorInterrupt();
  private:
    int _stateErr;
    int _signalSurtension;
    int _allowCommande;
};

#endif
