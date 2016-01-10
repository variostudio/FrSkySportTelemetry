/*
  FrSky telemetry class for Teensy 3.x and 328P based boards (e.g. Pro Mini, Nano, Uno)
  (c) Pawelsky 20151008
  Not for commercial use
*/

#include "FrSkySportTelemetry.h"

void FrSkySportTelemetry::begin(FrSkySportSingleWireSerial::SerialId id,
                                FrSkySportSensor* sensor1, FrSkySportSensor* sensor2,
                                FrSkySportSensor* sensor3, FrSkySportSensor* sensor4,
                                FrSkySportSensor* sensor5, FrSkySportSensor* sensor6,
                                FrSkySportSensor* sensor7, FrSkySportSensor* sensor8,
                                FrSkySportSensor* sensor9, FrSkySportSensor* sensor10)
{
  // Store sensor references in array
  sensors[0] = sensor1;
  sensors[1] = sensor2;
  sensors[2] = sensor3;
  sensors[3] = sensor4;
  sensors[4] = sensor5;
  sensors[5] = sensor6;
  sensors[6] = sensor7;
  sensors[7] = sensor8;
  sensors[8] = sensor9;
  sensors[9] = sensor10;

  // Count sensors (stops at first NULL)
  for(sensorCount = 0; sensorCount < FRSKY_TELEMETRY_MAX_SENSORS; sensorCount++)
  {
    if(sensors[sensorCount] == NULL) break;
  }

  FrSkySportTelemetry::serial.begin(id, false);
}

void FrSkySportTelemetry::send()
{
  if((serial.port != NULL) && (serial.port->available()))
  {
    uint8_t data = serial.port->read();
    if(prevData == FRSKY_TELEMETRY_START_FRAME)
    {
      uint32_t now = millis();
      // Send the actual data
      for(uint8_t i = 0; i < sensorCount; i++)
      {
        sensors[i]->send(serial, data, now);
      }
    }
    prevData = data;
  }
}
