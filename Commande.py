import  SerialPortCommunicator
import socket
import sys
from socketIO_client import SocketIO
from threading import Thread
spc = SerialPortCommunicator.SerialPortCommunicator()
socketIO = SocketIO('localhost', 8080)


def verifierError():
    spc.verifierError()
def resetArduino(self):
    spc.resetArduino()

def verifierSurtention():
    spc.verifierSurtention()

def affichage ():
    print("affichage des tension")
    socketIO.emit('sendInfo',spc.lireTension())


def precharger():
    # TODO
    print("precharger")
Thread(target=verifierError).start()
Thread(target=verifierSurtention).start()
Thread(target=affichage).start()



socketIO.emit('verifierError', verifierError)
socketIO.emit('verifierSurtention', verifierSurtention)