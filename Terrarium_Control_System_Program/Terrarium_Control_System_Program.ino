/* ##################### Temp and Humidity Relay System for Terrerium #########################
############################ Written By Matthew Paddock 3/28/2020 ###########################*/
// System uses SHT20 sensor to measure humidity and temperature and maintain them in a specific range 
// Using 2 120 V relays. A RTC is used to "spray" plants daily with fresh water and "refresh" air
// (RH [70-85+%]
// (T [up to 35 C])


//#### WIRING ####

// SHT20 I2C TEMPERATURE & HUMIDITY SENSOR (WATERPROOF PROBE)
// RobotShop # RB-Dfr-768
// RED to 3.3V
// GREEN to GND
// BLACK to A5
// WHITE to A4

// I2C SERIAL LCD SCREEN
// SunFounder # B019K5X53O
// SCL to A5
// SDA to A4
// GND to GND
// VCC to 5V

// 4 CHANNEL 5V 10A RELAY
// RobotShop # RB-Elf-156
// VCC to 5V
// GND to GND
// IN 1 N/C
// IN 2 N/C
// IN 3 to pin 7
// IN 4 to pin 8

// HUMIDIFIER RELAY
// COM to 120V AC from Wall (White wire)
// NO to 120V AC on Humidifier (White Wire)
// GND to GND (Black)

// FAN RELAY
// COM to 120V AC from Wall (White wire)
// NO to 120V AC on Humidifier (White Wire)
// GND to GND (Black)
// Plug in appropiate adapter to convert voltage to appropiate input for cooling fan.

// DATALOGGER BOARD WITH RTC
// RobotDyne # B072Q1584B
// Place on top of Arduino Uno

// SCREW TERMINAL SHIELD
// RobotDyn # B071JK13DP
// Place on top of Datalogger Board. Only need to use Analog side to connect SHT20 Probe to.


//#### DEPENDENCIES ####

#include <Wire.h>

// SHT20 
#include "DFRobot_SHT20.h"

// Datalogger Board
// #include "SD.h"                                      // Not using SD card function
#include "RTClib.h"

// I2C Screen
#include <LiquidCrystal_I2C.h>


//#### SETUP ####

// SHT 20
DFRobot_SHT20    sht20;                                 // Define SHT20

// I2C Screen
LiquidCrystal_I2C lcd(0x27,20,4);                       // set the LCD address to 0x27 for a 16 chars and 2 line display

// Datalogger
  // RTC
RTC_DS1307 RTC;                                         // Define RTC
int hourOn = 8;                                         // Hour to turn on relay
int minOn = 0;                                          // Hour to turn on relay
int hourOff = hourOn;                                   // Turn relay off at same hour as on
int minOff = 8;                                         // Hour to turn off

  // Set when to turn on
const int onHour = 10;                                  // Turn on at 10 AM
const int onMin = 0;                                    // Start at the start of the hour
  // Set when to turn on
const int offMin = 1;                                    // Run for 1 minute if use onHour as offHour

// Relays
int humidityRelay = 7;
int tempRelay = 8;

void setup() {
  // Run system to set up RTC, SHT20, LCD Screen, and set Relay Pins
  Serial.begin(9600);
  
  //#### Datalogger RTC ####
  RTC.adjust(DateTime(2020,03,28,13,13,0)); // Set time manually ONCE as above
    
  //#### SHT20 ####
  sht20.initSHT20();                                  // Init SHT20 Sensor
  delay(100);
  sht20.checkSHT20();                                 // Check SHT20 Sensor
  
  //#### I2C LCD SCREEN VOID SETUP ####
  lcd.init();                                         // Initialize LCD
 
  // Format Screen
  lcd.backlight();                                     // Fill Screen with contant variables
  lcd.setCursor(1,0);
  lcd.print("Temp: ");
  lcd.setCursor(12,0);
  lcd.print((char)223);
  lcd.setCursor(13,0);
  lcd.print("C");
  lcd.setCursor(1,1);
  lcd.print("RH: ");
  lcd.setCursor(10,1);
  lcd.print("%");
  
  //#### DATALOGGER VOID SETUP ####
  RTC.begin();                                        // initialize RTC 24H format
 
  //## RELAY VOID SETUP ####
  pinMode(humidityRelay, OUTPUT);                   // Set relay pins as output
  pinMode(tempRelay, OUTPUT);
  digitalWrite(humidityRelay, LOW);                 // Turn relays off initially
  digitalWrite(tempRelay, LOW);
}

void loop() {
  // Collect Humidity and Temperature every 5 seconds and display on LCD. Run series of conditions to control
  // relay to turn on humidifier to increase humidity and fan to decrease temperature. Condition in place to 
  // turn humidifier on if temperature goes about 32 C

  //##### SHT 20 ####                               // Read the humidity and temperature
  float RH = sht20.readHumidity();                        
  float Temp = sht20.readTemperature();

  DateTime now = RTC.now();


  //#### HUMIDITY CONTROL SYSTEM ####
  if(RH <70){                                       // Turn on for RH less than 60%
        digitalWrite(humidityRelay,HIGH);
            }
  
    else if(RH >85) {                               // Turn off for RH greater than 80%
        digitalWrite(humidityRelay,LOW);
            }
    
    else if(now.hour() == hourOn && now.minute() == minOn){     // Turn on daily even if the humidity isnt less than 70
        digitalWrite(humidityRelay,HIGH);
        digitalWrite(tempRelay,HIGH);
            }
    
    else if(now.hour() == hourOff && now.minute() == minOff){    // Turn off after 1 minute of running.
        digitalWrite(humidityRelay,LOW);
        digitalWrite(tempRelay,LOW);
            }

                    
  //#### TEMPERATURE CONTROL SYSTEM ####
  if(Temp > 30){                                    // Turn on fan for temperatures greater than 30C
        digitalWrite(tempRelay,HIGH);
            }
            
      else if(Temp > 34){
        digitalWrite(tempRelay,HIGH);
        digitalWrite(humidityRelay,HIGH);          // Turn on humidity if temperature reaches 35C
            }


    //#### I2C LED SCREEN VOID LOOP ####
    lcd.setCursor(7,0);                            // Display Temperature and Humidity on LCD Screen
    lcd.print(Temp,1);
    lcd.setCursor(5,1);
    lcd.print(RH,1);


//    Serial.print(" T:");                            // Serial Print the Temperature and Humidity to check outputs
//    Serial.print(Temp, 1);
//    Serial.print("C");
//    Serial.print(" RH:");
//    Serial.print(RH, 1);
//    Serial.print("%");
//    Serial.println();
    
    delay(5000);;                                // Time delay between Loop
        }
