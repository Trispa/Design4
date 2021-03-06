
import serial
from time import sleep
import struct
import platform

class SerialPortCommunicator:
    COMMAND_INDICATOR = "C"
    FALSE = 0
    TRUE = 1
    ONE_SECOND_DELAY = 2
    ONE_MINUTE_DELAY = 60

    LED_FUNCTION_ON = 1
    PRECHARGER = 2
    ARRETER_DRIVERS = 3
    LIRE_TENSIONS = 4
    DEMARRER_VENTILO = 5
    CHECKSURTENTION = 6
    ARRETER_COMMANDE = 7
    # CHANGE_SPEED_LINE = 7
    # CHANGE_SPEED_ROTATION = 8
    # CHANGE_CONDENSATOR_MODE = 9
    # READ_VOLTAGE = 10
    #
    # CW = 0
    # CCW = 1
    #
    # tensionCondensateur = 0



    def __init__(self, bitrateArduino = 115200, arduinoPort = "COM24"):
        # if platform.linux_distribution()[0].lower() == "Ubuntu".lower():
        #     arduinoPort = "/dev/serial/by-id/pci-FTDI_FT232R_USB_UART_A7007dag-if00-port0"
        # elif platform.linux_distribution()[0].lower() == "Fedora".lower():
        #     arduinoPort = "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A7007dag-if00-port0"
        self.arduino = serial.Serial(arduinoPort, bitrateArduino, timeout = 1)
        #self.polulu = serial.Serial(poluluPort, bitratePolulu, timeout = 1)
        sleep(1)

    def sendCommand(self, functionName, waitForCallback = 0, timeoutDelay = 1, *functionArgs):
        command = self.COMMAND_INDICATOR + str(functionName) + str(waitForCallback) + str(len(functionArgs))
        self.arduino.write(command.encode())

        for arguments in functionArgs:
            self.arduino.write(self._packIntegerAsLong(arguments))
        #self.arduino.write(str(arguments))

        if waitForCallback:
            return self._readCallback(timeoutDelay)

    def _readCallback(self, timeoutDelay):
        waitedTime = 0
        while self.arduino.read() != "R" and waitedTime < timeoutDelay:
            sleep(0.1)
            waitedTime += 0.1

        if waitedTime < timeoutDelay:
            receivedCallback = self.arduino.readline()
        else:
            # receivedCallback = -1
            receivedCallback = self.arduino.readline()

        return receivedCallback

    def _packIntegerAsLong(self, value):
        return struct.pack('i', value)


    ################# Commandes functions###################3

    def verifierError(self):
        rep = self.sendCommand(self.ARRETER_DRIVERS, self.TRUE, self.ONE_SECOND_DELAY, 1);
        print(rep)

    def arreterCommande(self):
        self.sendCommand(self.ARRETER_COMMANDE, self.FALSE, self.ONE_SECOND_DELAY, 1);

    def resetArduino (self):
        self.arduino.setDTR(False)
        sleep(1)
        # toss any data already received, see
        # http://pyserial.sourceforge.net/pyserial_api.html#serial.Serial.flushInput
        self.arduino.flushInput()
        self.arduino.setDTR(True)

    def verifierSurtention(self):
        rep = self.sendCommand(self.CHECKSURTENTION, self.TRUE, self.ONE_SECOND_DELAY, 1);
        print(rep)

    def lireTension(self):
        #rep = self.sendCommand(self.LIRE_TENSIONS, self.TRUE, self.ONE_SECOND_DELAY, 1);
        rep = {'tensionA4':12,'tensionA5':1652,'tensionA6':32,'tensionA7':162,'temperature':132}
        return (rep)



if __name__ == "__main__":
    spc = SerialPortCommunicator()
    while(1):
        #spc.lireTension()
        #spc.verifierSurtention()
        spc.verifierError()
