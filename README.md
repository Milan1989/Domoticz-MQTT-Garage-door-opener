# Garge door opener Domoticz-MQTT

<img align="right" width="100" src="pictures/Domoticz.png">

Let me introduce my garage door opener for Domoticz. This project handles two garage doors simultaneously and monitors the real status of doors with magnetic contact reed switch via MQTT protocol. If you use your own remote controll for the garage door opener, the status of the doors will be updated in Domoticz too.

**Components:**

- Arduino Leonardo ETH PoE
- 5V 2 Channel Relay Board Module
- 2 pcs Magnetic Contact Reed Switch

**Domoticz configuration:**

- Add MQTT Client Gateway with LAN interface
- Add Dummy virtual switch
- Create 2 switch for two garage doors (You have to set On and Off Action for the switches)

![](pictures/Garage_opener_wiring_diagram.png)
