import  SerialPortCommunicator
import sys
import time
from socketIO_client import SocketIO
from threading import Thread
socketIO = SocketIO('localhost', 8080)
spc = SerialPortCommunicator.SerialPortCommunicator()


def arreterCommande():
    spc.arreterCommande()
def verifierError():
    spc.verifierError()
def resetArduino(self):
    spc.resetArduino()

def verifierSurtention():
    spc.verifierSurtention()
def valeurTension():
    spc.lireTension()
def affichage ():
    while(True):
        tensions = spc.lireTension()
        socketIO.emit('sendInfo',tensions)
        print('envoi des tensions')
        time.sleep(2)


def precharger():
    # TODO
    print("precharger")
# Thread(target=verifierError).start()
# Thread(target=verifierSurtention).start()
Thread(target=affichage).start()



#socketIO.emit('verifierError', verifierError)
#socketIO.emit('verifierSurtention', verifierSurtention)
socketIO.emit('sendCommandClientStatus', 'Connected')
# socketIO.emit('sendInfo', valeurTension)

socketIO.on('arreterCommande',arreterCommande)
socketIO.wait()