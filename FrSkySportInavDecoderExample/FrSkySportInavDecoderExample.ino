/*
  FrSky S-Port Telemetry Decoder library example for the INAV decoder class (old hub telemetry and basic RSSI/ADC1/ADC2/RxBatt/SWR data)
  (c) Dmytro Pashko
  Not for commercial use
  
  Note that you need Teensy 3.x/LC or 328P based (e.g. Pro Mini, Nano, Uno) board and FrSkySportDecoder library for this example to work
*/

// Uncomment the #define below to enable internal polling of data.
// Use only when there is no device in the S.Port chain (e.g. S.Port capable FrSky receiver) that normally polls the data.
//#define POLLING_ENABLED

#include "FrSkySportSensor.h"
#include "FrSkySportSensorInav.h"
#include "FrSkySportSingleWireSerial.h"
#include "FrSkySportDecoder.h"
#if !defined(__MK20DX128__) && !defined(__MK20DX256__) && !defined(__MKL26Z64__) && !defined(__MK66FX1M0__) && !defined(__MK64FX512__)
#include "SoftwareSerial.h"
#endif

FrSkySportSensorInav inav;          // Create Inav sensor with default ID
#ifdef POLLING_ENABLED
  FrSkySportDecoder decoder(true);  // Create decoder object with polling
#else
  FrSkySportDecoder decoder;        // Create decoder object without polling
#endif


uint32_t currentTime, displayTime;
uint16_t decodeResult;

void setup()
{
  // Configure the decoder serial port and sensors (remember to use & to specify a pointer to sensor)
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__) || defined(__MK66FX1M0__) || defined(__MK64FX512__)
  decoder.begin(FrSkySportSingleWireSerial::SERIAL_3, &inav);
#else
  decoder.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_12, &inav);
#endif
  Serial.begin(115200);
}

void loop()
{
  // Read and decode the telemetry data, note that the data will only be decoded for sensors
  // that that have been passed to the begin method. Print the AppID of the decoded data.
  decodeResult = decoder.decode();
  if(decodeResult != SENSOR_NO_DATA_ID) { Serial.print("Decoded data with AppID 0x"); Serial.println(decodeResult, HEX); }
  
  // Display data once a second to not interfeere with data decoding
  currentTime = millis();
  if(currentTime > displayTime)
  {
    displayTime = currentTime + 1000;

    Serial.println("");

    Serial.print("RSSI = "); Serial.println(inav.getRssi()); // RSSI
    Serial.print("RxBatt = "); Serial.println(inav.getRxBatt()); // RxBatt voltage in volts
    Serial.print("fuel = "); Serial.print(inav.getFuel()); Serial.println("%"); // Fuel level in percent

    // Get current/voltage sensor (FAS) data
    Serial.print("current = "); Serial.print(inav.getCurrent()); Serial.println("A"); // Current consumption in amps
    Serial.print("voltage = "); Serial.print(inav.getVoltage()); Serial.println("V"); // Battery voltage in volts

    // Get variometer sensor (FVAS) data
    Serial.print("Altitude = "); Serial.print(inav.getAltitude()); Serial.println("m"); // Altitude in m (can be nevative)
    Serial.print("Vario = "); Serial.print(inav.getVario()); Serial.println("m/s");     // Verticas speed in m/s (can be nevative)

    // Get GPS data
    Serial.print("GPS: lat = "); Serial.print(inav.getLat()); Serial.print(", lon = "); Serial.println(inav.getLon()); // Latitude and longitude in degrees decimal (positive for N/E, negative for S/W)
    Serial.print("GPS: state = "); Serial.println(inav.getGpsState());
    Serial.print("speed = "); Serial.println(inav.getSpeed()); // Speed in m/s

    // Get accelerometer sensor (TAS) data
    Serial.print("ACCX = "); Serial.print(inav.getAccX());                      // X axis acceleraton in Gs (can be negative)
    Serial.print("ACCY = "); Serial.print(inav.getAccY());                      // Y axis acceleraton in Gs (can be negative)
    Serial.print("ACCZ = "); Serial.print(inav.getAccZ()); Serial.println("G"); // Z axis acceleraton in Gs (can be negative)

    Serial.print("Heading = "); Serial.print(inav.getHeading()); Serial.println(""); 
        
    Serial.print("MODE = "); Serial.println(inav.getFlightMode()); 

    Serial.println("");
  }
}
