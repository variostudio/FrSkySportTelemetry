/*
  FrSky Inav S.Port output decoder class for Teensy 3.x/LC and 328P based boards (e.g. Pro Mini, Nano, Uno)
  (c) Pashko Dmytro 2019
  Not for commercial use

  Note that this special sensor class can only be used for decoding.
*/

#include "FrSkySportSensorInav.h" 

FrSkySportSensorInav::FrSkySportSensorInav(SensorId id) : FrSkySportSensor(id) { }

uint16_t FrSkySportSensorInav::decodeData(uint8_t id, uint16_t appId, uint32_t data)
{
  //if((sensorId == id) || (sensorId == FrSkySportSensor::ID_IGNORE))
  //{
    switch(appId)
    {
      case INAV_RSSI_DATA_ID:
        rssi = (uint8_t)data;
        return appId;
      case INAV_RXBATT_DATA_ID:
        rxBatt = ((uint8_t)data) * (3.3 / 255.0) * 4.0;
        return appId;
      case INAV_CURRENT_DATA_ID:
        current = data/10.0;
        return appId;
      case INAV_FUEL_DATA_ID:
        fuel = data;
        return appId;
      case INAV_ALTITUDE_DATA_ID:
        altitude = (int16_t)data;
        return appId;
      case INAV_VARIO_DATA_ID:
        vario = data / 100.0;
        return appId;
      case INAV_LON_LAT_DATA_ID:
        latLon = ((uint32_t)data);
        if (latLon & 0x80000000) {
			inavLon = (latLon & ~0x80000000)*50/3;
		} else {
			inavLat = latLon*50/3;
		}
        return appId;
      case INAV_GPS_STATE_DATA_ID:
        gpsState = (uint8_t)data; 
        break;        
      case INAV_ACC_X_DATA_ID:
        accX = ((int16_t)data) / 1000.0;  
        return appId;
      case INAV_ACC_Y_DATA_ID:
        accY = ((int16_t)data) / 1000.0;  
        return appId;
      case INAV_ACC_Z_DATA_ID:
        accZ = ((int16_t)data) / 1000.0;  
        return appId;
      case INAV_FLIGHT_MODE_DATA_ID:
        fMode = (uint8_t)data;
        return appId;
      case INAV_HEADING_DATA_ID:
        heading = (uint32_t)data/100.0;
        return appId;
      case INAV_PITCH_DATA_ID:
        pitch = (uint32_t)data/100.0;
        return appId;
      case INAV_ROLL_DATA_ID:
        roll = (uint32_t)data/100.0;
        return appId;
      case INAV_CAP_USED_DATA_ID:
        capUsed = (uint32_t)data;
        return appId;
      case INAV_VOLTAGE_DATA_ID:
        voltage = (uint32_t)data/100.0;
        return appId;
        
        
    }
  //}
  return appId;
}

uint8_t FrSkySportSensorInav::getRssi() { return rssi; }
float FrSkySportSensorInav::getRxBatt() { return rxBatt; }
float FrSkySportSensorInav::getFuel() { return fuel; }
float FrSkySportSensorInav::getCurrent() { return current; }
float FrSkySportSensorInav::getVoltage() { return voltage; }
float FrSkySportSensorInav::getAltitude() { return altitude; }
float FrSkySportSensorInav::getVario() { return vario; }
int32_t FrSkySportSensorInav::getLat() { return inavLat; }
int32_t FrSkySportSensorInav::getLon() { return inavLon; }
float FrSkySportSensorInav::getSpeed() { return speed; }
float FrSkySportSensorInav::getAccX() { return accX; }
float FrSkySportSensorInav::getAccY() { return accY; }
float FrSkySportSensorInav::getAccZ() { return accZ; }
float FrSkySportSensorInav::getHeading() { return heading; }
float FrSkySportSensorInav::getPitch() { return pitch; }
float FrSkySportSensorInav::getRoll() { return roll; }
int32_t FrSkySportSensorInav::getCapacityUsed() { return capUsed; }
uint8_t FrSkySportSensorInav::getFlightMode() { return fMode; }
uint8_t FrSkySportSensorInav::getGpsState() { return gpsState; }
