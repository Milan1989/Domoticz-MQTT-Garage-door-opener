#!/bin/sh
sudo mosquitto_pub -h your domoticz server ip -t "domoticz/garage" -m '1'
