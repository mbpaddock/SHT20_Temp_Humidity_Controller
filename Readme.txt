Temp and Humidity Relay System for Terrerium
Written By Matthew Paddock 3/28/2020
System uses SHT20 sensor to measure humidity and temperature and maintain them in a specific range 
Using 2 120 V relays. A RTC is used to "spray" plants daily with fresh water and "refresh" air
(RH [70-85+%]
(T [up to 35 C])

Note, this program is not intended for commercial purposes

WIRING

SHT20 I2C TEMPERATURE & HUMIDITY SENSOR (WATERPROOF PROBE)
RobotShop # RB-Dfr-768
RED to 3.3V
GREEN to GND
BLACK to A5
WHITE to A4

I2C SERIAL LCD SCREEN
SunFounder # B019K5X53O
SCL to A5
SDA to A4
GND to GND
VCC to 5V

4 CHANNEL 5V 10A RELAY
RobotShop # RB-Elf-156
VCC to 5V
GND to GND
IN 1 N/C
IN 2 N/C
IN 3 to pin 7
IN 4 to pin 8

HUMIDIFIER RELAY
COM to 120V AC from Wall (White wire)
NO to 120V AC on Humidifier (White Wire)
GND to GND (Black)

FAN RELAY
COM to 120V AC from Wall (White wire)
NO to 120V AC on Humidifier (White Wire)
GND to GND (Black)
Plug in appropiate adapter to convert voltage to appropiate input for cooling fan.

DATALOGGER BOARD WITH RTC
RobotDyne # B072Q1584B
Place on top of Arduino Uno

SCREW TERMINAL SHIELD
RobotDyn # B071JK13DP
Place on top of Datalogger Board. Only need to use Analog side to connect SHT20 Probe to.