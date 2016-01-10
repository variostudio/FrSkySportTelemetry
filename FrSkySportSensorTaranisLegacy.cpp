/*
  FrSky legacy telemetry (converted to S.Port by Taranis radio) decoder class for Teensy 3.x and 328P based boards (e.g. Pro Mini, Nano, Uno)
  (c) Pawelsky 20151020
  Not for commercial use

  Note that only that this special sensor class can only be used for decoding.
*/

#include "FrSkySportSensorTaranisLegacy.h" 

FrSkySportSensorTaranisLegacy::FrSkySportSensorTaranisLegacy(SensorId id) : FrSkySportSensor(id) { }

uint16_t FrSkySportSensorTaranisLegacy::decodeData(uint8_t id, uint16_t appId, uint32_t data)
{
  if((sensorId == id) || (sensorId == FrSkySportSensor::ID_IGNORE))
  {
    switch(appId)
    {
      case 0x0028:
        current = data / 10.0;
        return appId;
      case 0x003A:
        voltBD = data;
        return appId;
      case 0x003B:
        // DEVIATION FROM SPEC: FrSky protocol spec suggests 0.5 ratio, but in reality this ratio is 0.5238 (based on the information from internet).
        voltAD = data;
        voltage = (voltAD / 10.0 + voltBD);
        voltage /= 0.5238;
        return appId;
      case 0x0004:
        fuel = data;
        return appId;
      case 0x0006:
        // DEVIATION FROM SPEC: in reality cells are numbered from 0 not from 1 like in the FrSky protocol spec
        if((data & 0xF000) == 0x0) cell[0]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x1) cell[1]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x2) cell[2]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x3) cell[3]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x4) cell[4]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x5) cell[5]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x6) cell[6]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x7) cell[7]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x8) cell[8]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0x9) cell[9]  = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0xA) cell[10] = (data & 0x0FFF) / 500.0; 
        if((data & 0xF000) == 0xB) cell[11] = (data & 0x0FFF) / 500.0; 
        return appId;
      case 0x0010:
        altBD = (int16_t)data;
        return appId;
      case 0x0021:
        altAD = data;
        altitude = altBD + altAD / 100.0;
        return appId;
      case 0x0001:
        gpsAltBD = (int16_t)data;
        return appId;
      case 0x0009:
        gpsAltAD = (int16_t)data;  
        gpsAltitude = gpsAltBD + gpsAltAD / 100.0;
      case 0x0011:
        speedBD = data;
        return appId;
      case 0x0019:
        speedAD = data;  
        speed = speedBD + speedAD / 100.0;
        speed *= 0.51444; // Convert knots to m/s
        return appId;
      case 0x0012:
        // DEVIATION FROM SPEC: FrSky protocol spec says lat shall be sent as big endian, but it reality little endian is sent
        lonBD = data;
        return appId;
      case 0x001A:
        // DEVIATION FROM SPEC: FrSky protocol spec says lat shall be sent as big endian, but it reality little endian is sent
        lonAD = data;
        return appId;
      case 0x0022: 
        lonEW = (char)data;
        if(lonEW == 'W') lon = -((uint16_t)(lonBD / 100) + ((lonBD % 100) + (lonAD / 10000.0)) / 60.0);
        else if(lonEW == 'E') lon = (uint16_t)(lonBD / 100) + ((lonBD % 100) + (lonAD / 10000.0)) / 60.0;
        else lon = 0;
        return appId;
      case 0x0013:
        // DEVIATION FROM SPEC: FrSky protocol spec says lat shall be sent as big endian, but it reality little endian is sent
        latBD = data;
        return appId;
      case 0x001B:
        // DEVIATION FROM SPEC: FrSky protocol spec says lat shall be sent as big endian, but it reality little endian is sent
        latAD = data;
        return appId;
      case 0x0023:
        latNS = (char)data;
        if(latNS == 'S') lat = -((uint16_t)(latBD / 100) + ((latBD % 100) + (latAD / 10000.0)) / 60.0);
        else if(latNS == 'N') lat = (uint16_t)(latBD / 100) + ((latBD % 100) + (latAD / 10000.0)) / 60.0;
        else lat = 0;
        return appId;
      case 0x0014:
        cogBD = data; 
        return appId;
      case 0x001C:
        cogAD = data;
        cog = cogBD + cogAD / 100.0;
        return appId;
      case 0x0015:
        day = data & 0x00FF; data >>= 8;
        month = data & 0x00FF;
        return appId;
      case 0x0016:
        year = data;
        return appId;
      case 0x0017:
        hour = data & 0x00FF; data >>= 8;
        minute = data & 0x00FF;
        return appId;
      case 0x0018:
        second = data;  
        return appId;
      case 0x0024:
        accX = ((int16_t)data) / 1000.0;  
        return appId;
      case 0x0025:
        accY = ((int16_t)data) / 1000.0;  
        return appId;
      case 0x0026:
        accZ = ((int16_t)data) / 1000.0;  
        return appId;
      case 0x0002:
        t1 = (int16_t)data;  
        return appId;
      case 0x0005:
        t2 = (int16_t)data;
        return appId;
      case 0x0003:
        rpm = data * 30.0;
        return appId;
    }
  }
  return SENSOR_NO_DATA_ID;
}

float FrSkySportSensorTaranisLegacy::getFuel() { return fuel; }
float FrSkySportSensorTaranisLegacy::getCell1() { return cell[0]; }
float FrSkySportSensorTaranisLegacy::getCell2() { return cell[1]; }
float FrSkySportSensorTaranisLegacy::getCell3() { return cell[2]; }
float FrSkySportSensorTaranisLegacy::getCell4() { return cell[3]; }
float FrSkySportSensorTaranisLegacy::getCell5() { return cell[4]; }
float FrSkySportSensorTaranisLegacy::getCell6() { return cell[5]; }
float FrSkySportSensorTaranisLegacy::getCell7() { return cell[6]; }
float FrSkySportSensorTaranisLegacy::getCell8() { return cell[7]; }
float FrSkySportSensorTaranisLegacy::getCell9() { return cell[8]; }
float FrSkySportSensorTaranisLegacy::getCell10() { return cell[9]; }
float FrSkySportSensorTaranisLegacy::getCell11() { return cell[10]; }
float FrSkySportSensorTaranisLegacy::getCell12() { return cell[11]; }
float FrSkySportSensorTaranisLegacy::getCurrent() { return current; }
float FrSkySportSensorTaranisLegacy::getVoltage() { return voltage; }
float FrSkySportSensorTaranisLegacy::getAltitude() { return altitude; }
float FrSkySportSensorTaranisLegacy::getLat() { return lat; }
float FrSkySportSensorTaranisLegacy::getLon() { return lon; }
float FrSkySportSensorTaranisLegacy::getGpsAltitude() { return gpsAltitude; }
float FrSkySportSensorTaranisLegacy::getSpeed() { return speed; }
float FrSkySportSensorTaranisLegacy::getCog() { return cog; }
uint16_t FrSkySportSensorTaranisLegacy::getYear() { return year; }
uint8_t FrSkySportSensorTaranisLegacy::getMonth() { return month; }
uint8_t FrSkySportSensorTaranisLegacy::getDay() { return day; }
uint8_t FrSkySportSensorTaranisLegacy::getHour() { return hour; }
uint8_t FrSkySportSensorTaranisLegacy::getMinute() { return minute; }
uint8_t FrSkySportSensorTaranisLegacy::getSecond() { return second; }
float FrSkySportSensorTaranisLegacy::getAccX() { return accX; }
float FrSkySportSensorTaranisLegacy::getAccY() { return accY; }
float FrSkySportSensorTaranisLegacy::getAccZ() { return accZ; }
float FrSkySportSensorTaranisLegacy::getT1() { return t1; }
float FrSkySportSensorTaranisLegacy::getT2() { return t2; }
float FrSkySportSensorTaranisLegacy::getRpm() { return rpm; }
