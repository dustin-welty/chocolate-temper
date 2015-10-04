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

// Listen on default port 5555, the webserver on the Yún
// will forward there all the HTTP requests for us.
YunServer server;
String startString;
long hits = 0;

int iMeltTemp = 100;
int iTemperTemp = 88;
bool bBowlOn = false;
bool bHeaterOn = false;

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}

void setup() {
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

  // get the time that this sketch started:
  Process startTime;
  startTime.runShellCommand("date");
  while (startTime.available()) {
    char c = startTime.read();
    startString += c;
  }
}
int temperature = 0;
String timeString = "";
int iCount=1;
void loop() {
  // Get clients coming from server
  YunClient client = server.accept();
  
  // There is a new client?
  if (client) {
    // read the command
    String command = client.readString();
    command.trim();        //kill whitespace
    Serial.println(command);

    if (command == "heater")
    {
      if (bHeaterOn)
      {
        client.print("On");
      }
      else
      {
        client.print("Off");
      }
    }
    if (command == "bowl")
    {
      if (bBowlOn)
      {
        client.print("On");
      }
      else
      {
        client.print("Off");
      }
    }
    if (command == "air_temp")
    {
      client.print(int(Thermistor(analogRead(0))));
    }
    if (command == "choc_temp")
    {
      client.print(int(Thermistor(analogRead(0))));
    }
    if (command == "melt_temp")
    {
      client.print(iMeltTemp);
    }
    if (command == "temper_temp")
    {
      client.print(iTemperTemp);
    }
    if (command == "heater_set")
    {
      bHeaterOn = !bHeaterOn;

      if (bHeaterOn)
      {
        client.print("On");
      }
      else
      {
        client.print("Off");
      }
    }
    if (command == "bowl_set")
    {
      bBowlOn = !bBowlOn;
      if (bBowlOn)
      {
        client.print("On");
      }
      else
      {
        client.print("Off");
      }
    }

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}


