from SerialPortCommunicator import  SerialPortCommunicator
import sys
import time
from socketIO_client import SocketIO
from threading import Thread
socketIO = SocketIO('localhost', 8080)
spc =SerialPortCommunicator()


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
def valeurTensions():
    spc.lireTension()

# def precharger():
#     # TODO
#     print("precharger")
# Thread(target=verifierError).start()
# Thread(target=verifierSurtention).start()
Thread(target=affichage).start()




socketIO.emit('verifierSurtention', verifierSurtention)
socketIO.emit('sendCommandClientStatus', 'Connected')
# socketIO.emit('sendInfo', valeurTensions)

socketIO.on('verifierError', verifierError)
socketIO.wait()