# Plant Moisture Monitor

Arduino Uno project that reads an FC-28 resistive soil probe and shows the reading on a 16x2 I2C LCD and a 128x32 SSD1306 OLED.

## Documentation

- [How the sensor works, analog and digital outputs, calibration, and displays](docs/soil-moisture-basics.md)
- [Sensor principle figure](docs/figures/resistive-sensor.svg)
- [Reading and display flow figure](docs/figures/reading-flow.svg)

## Hardware and wiring

| Signal | Arduino Uno R3 |
|---|---|
| FC-28 analog output (AO) | A0 |
| LCD and OLED SDA | A4 |
| LCD and OLED SCL | A5 |
| Display and sensor VCC | 5V, subject to module requirements |
| GND | Common GND |

The LCD backpack uses I2C address `0x27`. The SSD1306 OLED is 128x32 at address `0x3C`.

## Build and upload

Install the Arduino AVR core and the U8g2 and LiquidCrystal_I2C libraries, then run:

```sh
arduino-cli compile --fqbn arduino:avr:uno soil_monitor
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno soil_monitor
```

Change the serial port if the board appears at a different path.

## Calibration values in this sketch

`soil_monitor/soil_monitor.ino` currently maps raw ADC 1023 to dry air and 293 to the water measurement used during setup. These are project-specific reference readings, not universal FC-28 values. The displayed percentage is a relative estimate, not a laboratory measurement of water content.
