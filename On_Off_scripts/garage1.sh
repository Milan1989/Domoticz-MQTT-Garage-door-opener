#!/bin/sh
sudo mosquitto_pub -h 1.1.1.5 -t "domoticz/garage" -m '1'