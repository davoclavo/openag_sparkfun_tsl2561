#ifndef OPENAG_SPARKFUN_TSL2561_H
#define OPENAG_SPARKFUN_TSL2561_H

#include <Wire.h>
#include <SparkFunTSL2561.h>

#include <openag_module.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>

class SparkfunTSL2561 : public Module {
  public:
    // Constructor
    SparkfunTSL2561(int i2c_address);

    void begin();
    void update();
    bool get_light_illuminance(std_msgs::Float32 &msg);
    void set_gain(std_msgs::Bool msg);
    void set_time_setting(std_msgs::Int32 msg);
    void set_integration_time(std_msgs::Int32 msg);

  private:
    SFE_TSL2561 _sensor;
    char _i2c_address;          // Default 0x39
    boolean _gain;              // 0 = low gain (1X), 1 =  high gain (16X)
    unsigned int _time_setting; // 0 = 13.7ms, 1 = 101ms, 2 = 402ms, 3 = manual shutter (integration, default 0ms)
    unsigned int _integration_time; // Mutated by `setTiming(gain, time_setting, integration_time)`

    double _illuminance;
    bool _send_illuminance;
    uint32_t _time_of_last_reading;

    const uint32_t _min_update_interval = 2000;


    void setTiming();
    void readData();
    void handleError();
};

#endif
