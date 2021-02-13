#!/usr/bin/env python

import serial
  
class Esp8266CommandTriggerExecutor:
  def __init__(self, dev):
    self.serial = serial.Serial(dev, 115200)

  def firmware_version(self):
    self.serial.write(b"AT+GMR\r\n")

  def connect_access_point(self, ssid, password):
    payload = (
      "AT+CWJAP=\"{0}\",\"{1}\"\r\n"
    ).format(ssid, password)

    self.serial.write(b"{0}".format(payload))
  
  def get_ip(self):
    self.serial.write(b"AT+CIFSR\r\n")