# Plant Moisture Monitor

Example Arduino project using a resistive soil probe, a 16x2 I2C LCD, and an SSD1306 OLED.

## Documentation

- [How resistive sensors work, AO vs DO, and calibration](docs/soil-moisture-basics.md)

## Wiring used by the example sketch

| Signal | Arduino Uno R3 |
|---|---|
| FC-28 analog output (AO) | A0 |
| LCD and OLED SDA | A4 |
| LCD and OLED SCL | A5 |
| Display and sensor VCC | 5V, subject to module requirements |
| GND | Common GND |

These are the connections expected by the example sketch. Sensor boards and displays can use different pins, voltages, or addresses, so check their labels and instructions before connecting them.

The displays share SDA and SCL. Their addresses let the Arduino tell them apart: `0x27` for the example LCD and `0x3C` for the example OLED.

## Build and upload

With Arduino CLI, Uno board support, U8g2, and LiquidCrystal_I2C installed, find the board's port and build the sketch:

```sh
arduino-cli board list
arduino-cli compile --fqbn arduino:avr:uno soil_monitor
```

Use the port shown by the first command in place of `YOUR_PORT`:

```sh
arduino-cli upload -p YOUR_PORT --fqbn arduino:avr:uno soil_monitor
```

## Calibration

Before relying on the displayed percentage, take readings with your own probe in dry soil and in the same soil after watering. Enter those readings as `RAW_DRY` and `RAW_WET` in `soil_monitor/soil_monitor.ino`. Sensor and soil readings vary, so the values in the sketch are starting points, not universal settings. The percentage is a relative estimate, not a direct measurement of water content.
