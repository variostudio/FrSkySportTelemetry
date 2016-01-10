/*
  FrSky legacy telemetry (converted to S.Port by Taranis radio) decoder class for Teensy 3.x and 328P based boards (e.g. Pro Mini, Nano, Uno)
  (c) Pawelsky 20151018
  Not for commercial use

  Note that only that this special sensor class can only be used for decoding.
*/

#ifndef _FRSKY_SPORT_SENSOR_DECODER_LEGACY_H_
#define _FRSKY_SPORT_SENSOR_DECODER_LEGACY_H_

#include "FrSkySportSensor.h"

#define LEGACY_DEFAULT_ID ID25

class FrSkySportSensorTaranisLegacy : public FrSkySportSensor
{
  public:
    FrSkySportSensorTaranisLegacy(SensorId id = LEGACY_DEFAULT_ID);
    virtual uint16_t decodeData(uint8_t id, uint16_t appId, uint32_t data);

    // FGS sensor data: fuel in percent
    float getFuel();

    // FLVS sensor data: each cell voltage in volts.
    float getCell1();
    float getCell2();
    float getCell3();
    float getCell4();
    float getCell5();
    float getCell6();
    float getCell7();
    float getCell8();
    float getCell9();
    float getCell10();
    float getCell11();
    float getCell12();

    // FAS sensor data: current in amperes, voltage in volts
    float getCurrent();
    float getVoltage();

    // FVAS sensor data: altitude in meters, can be negative
    float getAltitude();

    // GPS sensor data: lat/lon in degrees decimal (positive for N/E, negative for S/W), alt in meters (can be negative), speed in m/s, course over ground (cog) in degrees 0-359
    //                  add 2000 to year, hours in 24h format
    float getLat();
    float getLon();
    float getGpsAltitude();
    float getSpeed();
    float getCog();
    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();

    // TAS sensor data: X/Y/Z acceleration in Gs (can be negative)
    float getAccX();
    float getAccY();
    float getAccZ();

    // TEMS sensor data: t1/t2 in degrees Celsius (can be negative)
    float getT1();
    float getT2();

    // RPMS sensor data: rpm in rotations per minute. Set number of blades to 2 in your radio
    float getRpm();
    
  private:
    // Temporary variables for collecting telemetry values that are combined from multiple data IDs
    uint16_t voltBD;
    uint16_t voltAD;
    int16_t altBD;
    int16_t altAD;
    char latNS;
    uint16_t latBD;
    uint16_t latAD;
    char lonEW;
    uint16_t lonBD;
    uint16_t lonAD;
    int16_t gpsAltBD;
    int16_t gpsAltAD;
    uint16_t speedBD;
    uint16_t speedAD;
    uint16_t cogBD;
    uint16_t cogAD;

    // Variables holding decoded telemetry data
    float fuel;
    float cell[12];
    float current;
    float voltage;
    float altitude;
    float lat;
    float lon;
    float gpsAltitude;
    float speed;
    float cog;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    float accX;
    float accY;
    float accZ;
    float t1;
    float t2;
    float rpm;
};

#endif // _FRSKY_SPORT_SENSOR_DECODER_LEGACY_H_
