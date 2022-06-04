#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial mine(D6, D7); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
void setup()
{
  Serial.begin(115200);
  Serial.print("Finding Location ...");
  delay(3000);
  mine.begin(9600);
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
}

void loop()
{
  while(mine.available())//While there are characters to come from the GPS
  {
    gps.encode(mine.read());//This feeds the serial NMEA data into the library one char at a time
    }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {

    Serial.print("Latitude:");
    Serial.print(gps.location.lat(), 6);
//    double LAT = gps.location.lat();
//    Serial.println(LAT);
    
    Serial.print("Longitude:");
    Serial.print(gps.location.lng(), 6);
//    double LNG = gps.location.lng();
//    Serial.println(LNG);
//    
//    Serial.println("Speed MPH:");
//    Serial.println(gps.speed.mph());
//    Serial.println("Altitude Feet:");
//    Serial.println(gps.altitude.feet());
//    Serial.println("");
  }

}
