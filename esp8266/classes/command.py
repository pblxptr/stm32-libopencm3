#!/usr/bin/env python

from enum import Enum

class CommandType(Enum):
    FirmwareVersion = 1
    ConnectAccessPoint = 2
    GetIp = 3
    EnableMultipleConnections = 4
    ConnectHost = 5

class Command:
  def __init__(self, description, handle):
    self.description = description
    self.handle = handle
