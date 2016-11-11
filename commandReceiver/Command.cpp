#include "Arduino.h"
#include "Command.h"
Command com ();
int pinErr1 = 19;
int pinErr2 = 20;
int pinErr3 = 21;
volatile unsigned int IntensiteMAx = 100;
volatile unsigned int stateError = 0;
int valPin;
int margeErreur = 10;
Command::Command()
{
  pinMode(pinErr1, INPUT);
  pinMode(pinErr2, INPUT);
  pinMode(pinErr3, INPUT);
  _stateErr = 0;
  _signalSurtension =0;
  attachInterrupt(digitalPinToInterrupt(pinErr1), errorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinErr2), errorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinErr3), errorInterrupt, CHANGE);

}
void Command::arreterCommand()
{
	digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}

int Command::getStatError()
{
    _stateErr = stateError;
    return this->_stateErr;
}
void Command::verifieSurIntensite(unsigned int pin){
    valPin = analogRead(pin);
    if(valPin >= IntensiteMAx + margeErreur ){
        this->_signalSurtension = 1;
        Serial.println("ErrorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrSurtention!");
    }else
        Serial.println("ErrorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrSurtentionNooooooooooooooo!");
}
int Command::getSignalSurtension (){
    return this->_signalSurtension;
}
int Command::lireTension(unsigned int pin){
    valPin = analogRead(pin);
    return valPin;
}
void Command::errorInterrupt(){
    if(digitalRead(pinErr1) || digitalRead(pinErr2)||digitalRead(pinErr2)== HIGH)
        stateError = 1;
    else
        stateError = 0;
}