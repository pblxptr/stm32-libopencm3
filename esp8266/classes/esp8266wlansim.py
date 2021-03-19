#!/usr/bin/env python

import serial

class Esp8266ResposeSimExecutor:
  def __init__(self, dev):
    self.serial = serial.Serial(dev, 9600)
    
  def firmware_version(self):
    payload = (
      "AT+GMR\r\n"
      "AT version:1.1.0.0(May 11 2016 18:09:56)\r\n"
      "SDK version:1.5.4(baaeaebb)\r\n"
      "compile time:May 20 2016 15:08:19\r\n"
      "OK\r\n"
    )

    print("Sending response of firmware_version command. Total lenght: {0}".format(len(payload)))

    self.serial.write(b"{0}".format(payload))

  def connect_access_point(self, ssid, password):
    payload = (
      "AT+CWJAP=\"UPC9090595\",\"sp7ahfb4vtHC\"\r\n"
      "WIFI CONNECTED\r\n"
      "WIFI GOT IP\r\n"
      "\r\n"
      "OK\r\n"
    )
    self.serial.write(b"{0}".format(payload))

  def get_ip(self):
    payload = (
      "AT+CIFSR\r\n"
      "+CIFSR:APIP,\"192.168.4.1\"\r\n"
      "+CIFSR:APMAC,\"2e:3a:e8:27:f3:bd\"\r\n"
      "+CIFSR:STAIP,\"192.168.0.10\"\r\n"
      "+CIFSR:STAMAC,\"2c:3a:e8:27:f3:bd\"\r\n"
      "\r\n"
      "OK\r\n"
    )
    self.serial.write(b"{0}".format(payload))