#ifndef Command_h
#define Command_h
class Command
{
  public :
    Command();
    void arreterCommand();
    void demarrerCommand();
    void precharger();
    int lireTension(unsigned int pin);
    void verifieSurIntensite(unsigned int pin);
    void demarrerVentilateur(int pin);
    int getStatError();
    int getSignalSurtension();
    static void errorInterrupt();
  private:
    int _stateErr;
    int _signalSurtension;
     
};

#endif
