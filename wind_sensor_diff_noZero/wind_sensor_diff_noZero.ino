/* Modern Device Wind Sensor Sketch for Rev C Wind Sensor


  Hardware Setup:
  Wind Sensor Signals    Arduino
  GND                    GND
  +V                     5V
  RV                     A4`    // modify the definitions below to use other pins
  TMP                    A5    // modify the definitions below to use other pins

  Paul Badger 2014
  Original at https://github.com/moderndevice/Wind_Sensor
  Licensed for use on official Modern Device hardware
  Reproduced with the permission of Paul Badger

  Revised by John Keefe 2016

  Hardware setup:
  Wind Sensor is powered from a regulated five volt source.
  RV pin and TMP pin are connected to analog inputs.

*/

#define analogPinForRV    4   // change to pins you the analog pins are using
#define analogPinForTMP   5

const float zeroWindAdjustment =  0;
int TMP_Therm_ADunits;
float RV_Wind_ADunits;
float RV_Wind_Volts;
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float WindSpeed_MPH = 0;
float Prev_Windspeed;
float Windspeed_Diff = 0; 


void setup() {
  Serial.begin(57600);
  Serial.println(Prev_Windspeed);
  

}

void loop() {

  if (millis() - lastMillis > 100) {
    TMP_Therm_ADunits = analogRead(analogPinForTMP);
    //    Serial.print("  TMP volts ");
    //    Serial.print(TMP_Therm_ADunits * 0.0048828125);
    RV_Wind_ADunits = analogRead(analogPinForRV);
    RV_Wind_Volts = (RV_Wind_ADunits *  0.0048828125);
    // these are all derived from regressions from raw data as such they depend on a lot of experimental factors
    // such as accuracy of temp sensors, and voltage at the actual wind sensor, (wire losses) which were unaccouted for.
    TempCtimes100 = (0.005 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;
    zeroWind_ADunits = -0.0006 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172; //  13.0C  553  482.39
    zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;
    WindSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) / .2300) , 2.7265);
//    Windspeed_Diff = WindSpeed_MPH - Prev_Windspeed;
    
    if (abs(WindSpeed_MPH - Prev_Windspeed) > 0.01){
//      Serial.print((float)Prev_Windspeed);
//      Serial.print(", ");
      Serial.println((float)WindSpeed_MPH);
//      Serial.print(", ");
//      Serial.println((float)Windspeed_Diff);
    }
    else {
    }

    Prev_Windspeed = WindSpeed_MPH;
    lastMillis = millis();
  }

}
