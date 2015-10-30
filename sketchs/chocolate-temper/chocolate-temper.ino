/*
Temperature web interface

This example shows how to serve data from an analog input
via the Arduino Yún's built-in webserver using the Bridge library.

The circuit:
* TMP36 temperature sensor on analog pin A1
* SD card attached to SD card slot of the Arduino Yún

This sketch must be uploaded via wifi. REST API must be set to "open".

Prepare your SD card with an empty folder in the SD root
named "arduino" and a subfolder of that named "www".
This will ensure that the Yún will create a link
to the SD to the "/mnt/sd" path.

In this sketch folder is a basic webpage and a copy of zepto.js, a
minimized version of jQuery.  When you upload your sketch, these files
will be placed in the /arduino/www/TemperatureWebPanel folder on your SD card.

You can then go to http://arduino.local/sd/TemperatureWebPanel
to see the output of this sketch.

You can remove the SD card while the Linux and the
sketch are running but be careful not to remove it while
the system is writing to it.

created  6 July 2013
by Tom Igoe

This example code is in the public domain.

http://arduino.cc/en/Tutorial/TemperatureWebPanel

*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "TemperMachine.h"

#define CHOCOLATE_TEMP_PIN  0
#define AIR_TEMP_PIN 1

#define HEATER_PIN1 8
#define HEATER_PIN2 9

#define BOWL_PIN  10

// Listen on default port 5555, the webserver on the Yún
// will forward there all the HTTP requests for us.
YunServer server;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *pHeaterFan = AFMS.getMotor(1);
Adafruit_DCMotor *pExhaustFan = AFMS.getMotor(2);

TemperMachine machine;
 
#define     ADC_SAMPLES        10      // Number of ADC samples to average
                                      // when taking a reading.
// Temperature unit conversion functions and state.
typedef float (*TempConversion)(float);
TempConversion ToKelvin; 
TempConversion FromKelvin;

double readResistance(byte pin, byte resistor) {
  float reading = 0;
  for (int i = 0; i < ADC_SAMPLES; ++i) {
    reading += analogRead(pin);
  }
  reading /= (float)ADC_SAMPLES;
  reading = (1023 / reading) - 1;
  return resistor / reading;
}

float kelvinToFahrenheit(float kelvin) {
  return kelvin*(9.0/5.0) - 459.67;
}

float fahrenheitToKelvin(float fahrenheit) {
  return (fahrenheit + 459.67)*(5.0/9.0);
}

float kelvinToCelsius(float kelvin) {
  return kelvin - 273.15;
}

float celsiusToKelvin(float celsius) {
  return celsius + 273.15; 
}

float readTemp(byte pin, byte resistor, float A, float B, float C) {
  float R = readResistance(pin, resistor);
  float kelvin = 1.0/(A + B*log(R) + C*pow(log(R), 3.0));
  return kelvin;
}

double ThermistorChocolate() 
{
    float A = -0.004087081909;
    float B = 0.000595037555;
    float C = -0.000000514512;
    unsigned int uiResistor = 1000000;

    float Temp = readTemp(CHOCOLATE_TEMP_PIN, uiResistor, A, B, C);
    return (int)kelvinToFahrenheit(Temp);
}

double ThermistorAir() 
{
    float A = 0.001363054633;
    float B = 0.000193818082;
    float C = 0.000000257738;
    unsigned int uiResistor = 10000;

    float Temp = readTemp(AIR_TEMP_PIN, uiResistor, A, B, C);
    return (int)kelvinToFahrenheit(Temp);
}

void HeaterOnOff(bool bOn)
{
    if (bOn)
    {
        digitalWrite(HEATER_PIN1, HIGH);
        digitalWrite(HEATER_PIN2, HIGH);
    }
    else
    {
        digitalWrite(HEATER_PIN1, LOW);
        digitalWrite(HEATER_PIN2, LOW);
    }
}

void BowlOnOff(bool bOn)
{
    if (bOn)
    {
        digitalWrite(BOWL_PIN, HIGH);
    }
    else
    {
        digitalWrite(BOWL_PIN, LOW);
    }
}

void HeaterFanOn(bool bOn)
{
    if (bOn)
    {
        pHeaterFan->run(FORWARD);
    }
    else
    {
        pHeaterFan->run(RELEASE);
    }
}

void ExhaustFanOn(bool bOn)
{
    if (bOn)
    {
        pExhaustFan->run(FORWARD);
    }
    else
    {
        pExhaustFan->run(RELEASE);
    }
}

void setup()
{
    Serial.begin(9600);

    // Bridge startup
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Bridge.begin();
    digitalWrite(13, HIGH);

    // Listen for incoming connection only from localhost
    // (no one from the external network could connect)
    server.listenOnLocalhost();
    server.begin();

    AFMS.begin();

    pHeaterFan->setSpeed(255);
    pExhaustFan->setSpeed(255);

    HeaterFanOn(false);
    ExhaustFanOn(false);

    //setup the pin0, pin1 for out put to control heater
    pinMode(HEATER_PIN1, OUTPUT);
    pinMode(HEATER_PIN2, OUTPUT);

    pinMode(BOWL_PIN, OUTPUT);
    //make sure the heater is off
    HeaterOnOff(false);
    BowlOnOff(false);

    //set up the Thermistor pins
    analogReference(DEFAULT);
    
    machine.Init(false, false, false, false);

    machine.SetCurrentChocolateTemp(int(ThermistorChocolate()));
    machine.SetCurrentAirTemp(int(ThermistorAir()));
}

void loop() 
{
    // Get clients coming from server
    YunClient client = server.accept();

    // There is a new client?
    if (client)
    {
        // read the command
        char scResult[30];
        String sCommand = client.readString();
        sCommand.trim();        //kill whitespace
        Serial.println(sCommand);

        if (machine.bCommand(sCommand.c_str(), scResult))
        {
            client.print(scResult);
        }

        // Close connection and free resources.
        client.stop();
    }

    machine.SetCurrentChocolateTemp(int(ThermistorChocolate()));
    machine.SetCurrentAirTemp(int(ThermistorAir()));

    bool bHeaterOn = false;
    bool bHeaterFanOn = false;
    bool bExhaustFanOn = false;
    bool bBowlOn = false;

    machine.GetValuesToSet(&bHeaterOn, &bHeaterFanOn, &bExhaustFanOn, &bBowlOn);

    HeaterFanOn(bHeaterFanOn);
    ExhaustFanOn(bExhaustFanOn);
    HeaterOnOff(bHeaterOn);
    BowlOnOff(bBowlOn);

    delay(50); // Poll every 50ms
}



