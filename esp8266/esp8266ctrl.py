#!/usr/bin/env python

import collections
import argparse


from classes.command import Command, CommandType
from classes.esp8266wlanreal import Esp8266CommandTriggerExecutor
from classes.esp8266wlansim import Esp8266ResposeSimExecutor


class Esp8266Ctrl:
  def __init__(self, executor):
    self.executor = executor
    self.commands = collections.OrderedDict()
    self.commands[CommandType.FirmwareVersion] = Command("Check firmware version", Esp8266Ctrl.firmware_version)
    self.commands[CommandType.ConnectAccessPoint] = Command("Connect access point", Esp8266Ctrl.connect_access_point)
    self.commands[CommandType.GetIp] = Command("Get Ip", Esp8266Ctrl.get_ip)
    self.commands[CommandType.EnableMultipleConnections] = Command("Enable multiple connections", Esp8266Ctrl.enable_multiple_connections)
    self.commands[CommandType.ConnectHost] = Command("Connect host", Esp8266Ctrl.connect_host)
  
  def firmware_version(self):
    print("Firmware version")
    self.executor.firmware_version()

  def connect_access_point(self):
    print("Connect access point")
    self.executor.connect_access_point("UPC9090595", "sp7ahfb4vtHC")

  def get_ip(self):
    print("GetIp")
    self.executor.get_ip()

  def enable_multiple_connections(self):
    print("Enable multiple connections")
  
  def connect_host(self):
    print("Connect host")

  def get_commands(self):
    return self.commands


def process(ctrl):
  while True:
    commands = ctrl.get_commands()

    for key, command in commands.items():
      print("{0}. -> {1}".format(key.value, command.description))

    
    command_id = CommandType(int(input("> ")))

    command = commands[command_id]
    command.handle(ctrl)

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("--sim", help="Simulate resposes from AT commands.", action='store_true')
  parser.add_argument("--dev", help="Serial port device.")
  args = parser.parse_args()

  serial_device = "/dev/ttyUSB0"
  
  if args.dev:
    serial_device = args.dev

  print("Serial device: {0}".format(serial_device))

  if args.sim:
    print("SIM selected.")
    ctrl = Esp8266Ctrl(Esp8266ResposeSimExecutor(serial_device))
    process(ctrl)
  else:
    print("Real selected.")
    ctrl = Esp8266Ctrl(Esp8266CommandTriggerExecutor(serial_device))
    process(ctrl)
if __name__ == "__main__":
  main()