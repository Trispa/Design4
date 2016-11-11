#include "commandReceiver.h"
#include <stdlib.h>
#define StandardHeaderLenght 5
#define NumberOfBytesInLong 4
#define ASCIIOffset 48
#define NumberOfPIDParameters 4
#define HalfTurnTicks 2064
#define MilimetersToTicks 7.69
#define endingLEDPin 13
String  tensions = "";
CommandReceiver::CommandReceiver()
{

}

CommandReceiver::CommandReceiver(Command* cmd)
{
  cm = cmd;
}


void CommandReceiver::decomposeParameters() {
	byte numberOfParameters = Serial.read() - ASCIIOffset;

	while(Serial.available() < (numberOfParameters * NumberOfBytesInLong) ) {}

	long buffer = 0;
	int index = 0;

	while(index < numberOfParameters) {
		parameters[index] = readULongFromBytes();
		index++;
	}
}


void CommandReceiver::decomposeCommand() {
	commandIndex = Serial.read() - ASCIIOffset;

	callbackRequested = Serial.read() - ASCIIOffset;

	decomposeParameters();
}

void CommandReceiver::process() {
	executeCommand();
}

void CommandReceiver::readPort() {
	if(Serial.read() == 'C') {
		while(Serial.available() < StandardHeaderLenght) {}
		decomposeCommand();
		commandWaitingFlag = 1;
	}
}

void CommandReceiver::dispatchCommand() {



	switch (commandIndex) {
	case 1: //lightEndingLED

		break;

	case 2: //Precharger
		digitalWrite(endingLEDPin, LOW);
		break;

  	case 3: //Arreter Commande
             if(callbackRequested == 1){
                if(cm->getStatError() == 1){
                    cm->arreterCommand();
                    sendCallback("ErrorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrError!");
                }
                else{
                    sendCallback("Noooooooooooooooooo Error000000000000000000000000000000000000NoError!");
                }
             }
        break;


	case 4: // lire les tensions
        //TODO A revoir !!!!!!!!!!!11
           tensions += cm->lireTension(A0);tensions +="!";
           tensions += cm->lireTension(A1);tensions +="!";
           tensions += cm->lireTension(A2);tensions +="!";
           tensions += cm->lireTension(A3);tensions +="!";
           if(callbackRequested == 1) {
			    sendCallback('rrrrrrrrrrrrrrrrrrr'+tensions);
		    }

        break;
 	case 5: // demarrer les ventilos
        break;
    case 6: // surtension
        cm->verifieSurIntensite(A1);
        break;
 	default: //for test purposes
		if(callbackRequested == 1) {
			sendCallback(parameters[0]);
		}
		break;
 }
 }

void CommandReceiver::sendCallback(long callbackData) {
	Serial.print('R');
	Serial.print(callbackData, DEC);
}


void CommandReceiver::sendCallback(char* callbackData) {
  Serial.print('R');
  Serial.print(callbackData);
}
void CommandReceiver::sendCallback(String callbackData) {
  Serial.print('R');
  Serial.print(callbackData);
}

void CommandReceiver::executeCommand() {
	readPort();

	if(commandWaitingFlag == 1) {
		dispatchCommand();
		commandWaitingFlag = 0;
	}
}

long CommandReceiver::readULongFromBytes() {
	union u_tag {
		byte bytes[NumberOfBytesInLong];
		long returnLong;
	} bytesToLong;

	bytesToLong.bytes[0] = Serial.read();
	bytesToLong.bytes[1] = Serial.read();
	bytesToLong.bytes[2] = Serial.read();
	bytesToLong.bytes[3] = Serial.read();
	return bytesToLong.returnLong;
}