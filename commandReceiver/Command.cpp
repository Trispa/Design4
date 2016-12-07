#include "Arduino.h"
#include "Command.h"
Command com ();
int pinErr1 = 18; // digital pin retour signal erreur driver1
int pinErr2 = 19; // digital pin retour signal erreur driver2
int pinErr3 = 20; // digital pin retour signal erreur driver3
int pinFreq = 50; // digital pin pour la frequence de modulation 
int onOffPin = 2; // digital pin pour demarrer la commande 
int internExterneMode = 3; // digital pin 
int relaisPin = 8; //digital pin
volatile unsigned int IntensiteMAx = 100; //valeur a changer par la bonne quand on le saura. juste dans le but de test
volatile unsigned int stateError = 0;
volatile unsigned int allowCommande = 0;
volatile bool dePeriode = false;// microsecondes
int tensionCondensateur ;
int valPin;
int margeErreur = 10;
Command::Command()
{
  pinMode(pinErr1, INPUT);
  pinMode(pinErr2, INPUT);
  pinMode(pinErr3, INPUT);
  pinMode(pinFreq, INPUT);
  _stateErr = 0;
  _signalSurtension =0;
  _allowCommande = 0;
  _amp = 1;
  attachInterrupt(digitalPinToInterrupt(pinErr1), errorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinErr2), errorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinErr3), errorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(onOffPin), onOff, HIGH);
  attachInterrupt(digitalPinToInterrupt(internExterneMode), modeCommande, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinFreq), switchFreq, HIGH);

  }

void Command::onOff(){
  digitalWrite(relaisPin, HIGH);//demarre la precharge
}

void Command::demarrerCommand(){
	//autoriser la generation de la commande
	_allowCommande = 1;
}

void Command::arreterCommand()
{
	digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}
	
void Command::modeCommande(){
	//TODO mode externe
	// allready done : mode inerne par defaut
}



int Command::getAllowCommande()
{
    _allowCommande = allowCommande;
    return this->_allowCommande;
}

int Command::getStatError()
{
    this->_stateErr = stateError;
    return this->_stateErr;
}
void Command::setStatError(int val)
{
	this->_stateErr = val;
}
void Command::verifieSurIntensite(unsigned int pin){
    valPin = analogRead(pin);
    if(valPin >= IntensiteMAx + margeErreur ){
        this->_signalSurtension = 1;;
    }else{
        this->_signalSurtension = 0;
		}
}

void Command::demarrerVentilateur(unsigned int pinVal){
	digitalWrite(pinVal, HIGH);
}

int Command::getSignalSurtension (){
    return this->_signalSurtension;
}


int Command::lireTension(unsigned int pin){
    valPin = analogRead(pin);
    return valPin;
}

void Command::errorInterrupt(){
	if(digitalRead(pinErr1) == HIGH || digitalRead(pinErr2) == HIGH || digitalRead(pinErr2)== HIGH)
        stateError = 1;
    /*if(digitalRead(pinErr1) == LOW && digitalRead(pinErr2) == LOW && digitalRead(pinErr2)== LOW)
        stateError = 0;
    else
        stateError = 1;
	*/
}
void Command::switchFreq(){
	dePeriode = true;
	/*if (digitalRead(pinFreq) == HIGH ) 
		dePeriode = true; // pour avoir 12 Khz comme frequence PWM
	else
		dePeriode = false;
	*/
}

bool Command::defaultPeriode(){
	return dePeriode;
}