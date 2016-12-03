#include "openag_sparkfun_tsl2561.h"

// Default I2C Address is 0x39 (57)
SparkfunTSL2561::SparkfunTSL2561(int i2c_address) : _i2c_address(i2c_address) { }

void SparkfunTSL2561::begin() {
  _sensor.begin();

  _time_setting = 2; // 402ms by default
  _gain = false;
  _sensor.setTiming(_gain, _time_setting, _integration_time);

  if (_sensor.setPowerUp()) {
    status_level = OK;
    status_msg = "";
  } else {
    handleError();
  }

  _send_illuminance = false;
  _time_of_last_reading = 0;
}

void SparkfunTSL2561::update() {
  if (millis() - _time_of_last_reading > _min_update_interval) {
    readData();
    _time_of_last_reading = millis();
  }
}

bool SparkfunTSL2561::get_light_illuminance(std_msgs::Float32 &msg) {
  msg.data = _illuminance;
  bool res = _send_illuminance;
  _send_illuminance = false;
  return res;
}

void SparkfunTSL2561::set_gain(std_msgs::Bool msg) {
  _gain = msg.data;
  setTiming();
}

void SparkfunTSL2561::set_time_setting(std_msgs::Int32 msg) {
  _time_setting = msg.data;
  setTiming();
}

void SparkfunTSL2561::set_integration_time(std_msgs::Int32 msg) {
  _integration_time = msg.data;
  setTiming();
}

void SparkfunTSL2561::setTiming() {
  _sensor.setTiming(_gain, _time_setting, _integration_time);
}

void SparkfunTSL2561::readData() {
  _sensor.manualStart();
  delay(_integration_time);
  _sensor.manualStop();

  unsigned int data0, data1;

  if (_sensor.getData(data0, data1)) {
    if (_sensor.getLux(_gain, _integration_time, data0, data1, _illuminance)) {
      _send_illuminance = true;
    } else {
      status_level = WARN;
      status_msg = "99"; // Sensor saturated: lower gain/shutter time
    }
  } else {
    handleError();
  }
}

void SparkfunTSL2561::handleError() {
  byte error = _sensor.getError();
  status_level = ERROR;
  status_msg = error;
  // 0 - Success (??)
  // 1 - Data too long for transmit buffer
  // 2 - Received NACK on address (disconnected?)
  // 3 - Received NACK on data
  // 4 - Other error
  // X - Unknown error
}
