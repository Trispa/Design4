import  SerialPortCommunicator
import sys
import time
from socketIO_client import SocketIO
from threading import Thread
socketIO = SocketIO('localhost', 8080)
spc = SerialPortCommunicator.SerialPortCommunicator()


def verifierError():
    spc.verifierError()
def resetArduino(self):
    spc.resetArduino()

def verifierSurtention():
    spc.verifierSurtention()
def valeurTension():
    spc.lireTension()
def refresh ():
    while(True):
        tensions = spc.lireTension()
        error = spc.verifierError()
        surtention = spc.verifierSurtention()
        socketIO.emit('sendInfo',tensions)
        socketIO.emit('verifierSurtention',surtention)
        socketIO.emit('verifierError', error)
        print('envoi des tensions , verification urtension, et verification erreur driver')
        time.sleep(2)


def precharger():
    # TODO
    print("precharger")
# Thread(target=verifierError).start()
# Thread(target=verifierSurtention).start()
Thread(target=refresh).start()



#socketIO.emit('verifierError', verifierError)
#socketIO.emit('verifierSurtention', verifierSurtention)
socketIO.emit('sendCommandClientStatus', 'Connected')
# socketIO.emit('sendInfo', valeurTension)

socketIO.wait()