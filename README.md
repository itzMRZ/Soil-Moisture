# Plant Moisture Monitor

Example Arduino project with a resistive soil probe, a 16x2 I2C LCD, and an SSD1306 OLED.

[Read the sensor guide](docs/soil-moisture-basics.md) for a plain-language explanation of AO, DO, and calibration.

## Get the code and tools

Clone the repository once:

```sh
git clone https://github.com/itzMRZ/Soil-Moisture.git
cd Soil-Moisture
```

To get later changes, run `git pull` from this folder.

This guide uses Arduino CLI to keep setup to a few terminal commands. The IDE can sit this one out.

Check whether it is installed:

```sh
arduino-cli version
```

If the command is missing, follow the [official install guide](https://arduino.github.io/arduino-cli/latest/installation/) for your operating system. Then install the Uno board support and the two libraries, skipping anything you already have:

```sh
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install U8g2 "LiquidCrystal I2C"
```

## Wiring

These are the connections expected by the example sketch. Check your module labels and instructions first. Different boards may use different pins, voltages, or addresses.

| Signal | Arduino Uno R3 |
|---|---|
| Sensor analog output (AO) | A0 |
| LCD and OLED SDA | A4 |
| LCD and OLED SCL | A5 |
| VCC | 5V, if supported by the module |
| GND | Common GND |

The displays share SDA and SCL. The example LCD address is `0x27`; the OLED address is `0x3C`.

## Build and upload

Compile the sketch:

```sh
arduino-cli compile --fqbn arduino:avr:uno soil_monitor
```

Connect the Uno with a USB data cable and find its port:

```sh
arduino-cli board list
```

Replace `YOUR_PORT` with the port shown above:

```sh
arduino-cli upload -p YOUR_PORT --fqbn arduino:avr:uno soil_monitor
```

Close any Serial Monitor before uploading, since it can keep the port busy. If the board list is empty, check the cable and connection.

## Calibration

Before using the percentage for plant care, take readings with your probe in dry soil and in the same soil after watering. Set `RAW_DRY` and `RAW_WET` in `soil_monitor/soil_monitor.ino` to those readings. They vary by sensor and soil, so the sketch's defaults are only starting points. The percentage is a relative estimate, not a direct measure of water content.
