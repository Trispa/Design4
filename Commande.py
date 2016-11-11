import  serialPortCommunicator
import socket
import sys
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# from socketIO_client import SocketIO
from threading import Thread
spc = serialPortCommunicator()
socketIO = sock('localhost', 63342)


def verifierError(self):
    self.serialPortCommunicator.verifierError()
def resetArduino(self):
    self.serialPortCommunicator.resetArduino()

def verifierSurtention(self):
    self.serialPortCommunicator.verifierSurtention()

def affichage (self):
    print("affichage des tension")
    socketIO.emit('sendInfo',spc.lireTension())


def precharger(self):
    # TODO
    print("precharger")
Thread(target=verifierError).start()
Thread(target=verifierSurtention).start()
Thread(target=affichage).start()



socketIO.emit('verifierError', verifierError)
socketIO.emit('verifierSurtention', verifierSurtention)