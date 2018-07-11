# -*- coding: utf-8 -*-
"""
Created on Tue May 22 10:33:04 2018

@author: Usuario
"""

import serial

puerto_serie=serial.Serial('COM6',9600)

while True:
    sArduino = puerto_serie.readline()
    print "Valor Arduino: " + sArduino.rstrip('\n')