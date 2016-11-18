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

def affichage ():
    while(True):
        tensions = spc.lireTension()
        socketIO.emit('senInfo',tensions)
        print('envoi des tensions')
        time.sleep(5)


def precharger():
    # TODO
    print("precharger")
Thread(target=verifierError).start()
Thread(target=verifierSurtention).start()
Thread(target=affichage).start()



socketIO.emit('verifierError', verifierError)
socketIO.emit('verifierSurtention', verifierSurtention)
socketIO.emit('sendCommandClientStatus', 'Connected')
# socketIO.emit('sendInfo', affichage)

socketIO.wait()