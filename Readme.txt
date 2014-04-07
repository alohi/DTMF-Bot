This is DTMF based landlover vehicle, It uses
1) GSM Modem (SIM900) with firmware 1137B08SIM900M64_ST_DTMF_JD_MMS
2) IR Obstacle Sensor,IR Fire Sensor,Smoke Sensor
3) When smoke or fire detected it will send alert sms to user
4) User can control forward,backward,left,right and stop. When obstacle is detected it will stop
5) It doesn't uses any external dtmf decoder, With above mentioned firmware we can get dtmf through uart

TODO
1) Intelligence has to add when obstacle is detected
2) Webserver,sms control has to add
3) Speed control through enable pin
4) Settings from webserver that shpould be store when updated in arduino EEPROM

Software Required
1) AVR-GCC Compiler
2) SIM900-customer-flash-loader (Included in repository)
3) SIM900 DTMF Firmware (Included in repository)
4) Project Source Code 
5) Opensource AVR Library by Sriharsha Clone by next mentioned url (git clone https://github.com/zunaadmin/AVR.git)