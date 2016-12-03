OpenAg Sparkfun TSL2561
=============

This repository contains an OpenAg firmware module for the [Sparkfun TSL2561 Light Illuminance Sensor](https://www.sparkfun.com/products/12055). The module defines a single output, `light_illuminance`, which constantly outputs a float value representing the light illuminance measured with the calibration values `gain`, `time_setting` and `integration_time`. By default the `time_setting` is set to fixed integraton time of 402ms.

The module will enter an WARN state if its value is saturated, which requires reconfiguration of gain or time_setting/integration_time.
The module will enter an ERROR state whenever it fails to read from the sensor.


Error Codes
-------------

The error codes are passed directly from Sparkfun's library

  - "0":  Success (??)
  - "1":  Data too long for transmit buffer
  - "2":  Received NACK on address (disconnected?)
  - "3":  Received NACK on data
  - "4":  Other error


Development
-----------

Install [openag_python](https://github.com/OpenAgInitiative/openag_python) and [PlatformIO](https://platformio.org)

    pip2 install openag
    pip2 install platformio==2.11.2
    platformio platforms install atmelavr

Then this module can be compiled using the CSV plugin (to print outputs and status via the Serial port) and then uploaded to the Arduino. Run as follows:

    openag firmware run_module -p csv -t upload

Note: be sure to plug an Arduino via USB before running this command, or you will see an error.

Open up your serial monitor

    platformio serialports monitor

You should see values like these:

    data,module,light_illuminance,1199.52
    data,module,light_illuminance,659.83
    status,module,0,

