/*
  FrSky Inav S.Port output decoder class for Teensy 3.x/LC and 328P based boards (e.g. Pro Mini, Nano, Uno)
  (c) Pashko Dmytro 2019
  Not for commercial use

  Note that this special sensor class can only be used for decoding.
*/

#ifndef _FRSKY_SPORT_SENSOR_INAV_H_
#define _FRSKY_SPORT_SENSOR_INAV_H_

#include "FrSkySportSensor.h"

#define INAV_DEFAULT_ID                     ID28

#define INAV_RSSI_DATA_ID                   0xF101
#define INAV_RXBATT_DATA_ID                 0xF104
#define INAV_LON_LAT_DATA_ID                0x0800
#define INAV_GPS_STATE_DATA_ID              0x0410
#define INAV_FLIGHT_MODE_DATA_ID            0x0400
#define INAV_CURRENT_DATA_ID                0x0200
#define INAV_ACC_X_DATA_ID                  0x0700
#define INAV_ACC_Y_DATA_ID                  0x0710
#define INAV_ACC_Z_DATA_ID                  0x0720
#define INAV_HEADING_DATA_ID                0x0840
#define INAV_PITCH_DATA_ID                  0x0430
#define INAV_ROLL_DATA_ID                   0x0440
#define INAV_CAP_USED_DATA_ID               0x0610
#define INAV_FUEL_DATA_ID                   0x0600
#define INAV_ALTITUDE_DATA_ID               0x0100
#define INAV_VARIO_DATA_ID                  0x0110
#define INAV_VOLTAGE_DATA_ID                0x0210

class FrSkySportSensorInav : public FrSkySportSensor
{
  public:
    FrSkySportSensorInav(SensorId id = INAV_DEFAULT_ID);
    virtual uint16_t decodeData(uint8_t id, uint16_t appId, uint32_t data);

    // System data
    uint8_t getRssi();
    float getRxBatt();

    float getFuel();

    float getCurrent();
    float getVoltage();

    float getAltitude();
    int32_t getCapacityUsed();

    int32_t getLat();
    int32_t getLon();
    float getGpsAltitude();
    float getSpeed();
    float getVario();

    float getAccX();
    float getAccY();
    float getAccZ();
    
    float getHeading();
        
    int16_t getFlightMode();
    int32_t getGpsState();
    
  private:
    // Temporary variables for collecting telemetry values that are combined from multiple data IDs
    int16_t fMode;
    int32_t gpsState;
    int32_t latLon;
    int32_t inavLon;
    int32_t inavLat;
    int32_t capUsed;

    // Variables holding decoded telemetry data
    uint8_t rssi;
    float rxBatt;
    float fuel;
    float current;
    float voltage;
    float altitude;
    float vario;
    float lat;
    float lon;
    float gpsAltitude;
    float speed;
    float accX;
    float accY;
    float accZ;
    float heading;
};

#endif // _FRSKY_SPORT_SENSOR_INAV_H_
