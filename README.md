# Plant Moisture Monitor

Example Arduino project using a resistive soil probe, a 16x2 I2C LCD, and an SSD1306 OLED.

## Documentation

- [How resistive sensors work, AO vs DO, and calibration](docs/soil-moisture-basics.md)

## Get the code

Clone the repository:

```sh
git clone https://github.com/itzMRZ/Soil-Moisture.git
cd Soil-Moisture
```

For later updates, run `git pull` from inside the project folder.

## Why Arduino CLI?

I use Arduino CLI because it is quick and uncluttered. A few terminal commands build and upload the sketch without opening a full IDE.

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

## Install Arduino CLI and board support

Check whether Arduino CLI is installed:

```sh
arduino-cli version
```

If the command is not found, follow the [official installation instructions](https://arduino.github.io/arduino-cli/latest/installation/) for your operating system, then open a new terminal and check the version again.

Install the Uno board support and the libraries if they are not already installed:

```sh
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install U8g2 "LiquidCrystal I2C"
```

## Compile and upload

Compile first:

```sh
arduino-cli compile --fqbn arduino:avr:uno soil_monitor
```

Connect the Uno with a USB data cable and list its port:

```sh
arduino-cli board list
```

Replace `YOUR_PORT` with the port shown in that list, then upload:

```sh
arduino-cli upload -p YOUR_PORT --fqbn arduino:avr:uno soil_monitor
```

Close any Serial Monitor window before uploading, since it can keep the port busy. If `board list` shows nothing, check the USB cable and connection.

## Calibration

Before relying on the displayed percentage, take readings with your own probe in dry soil and in the same soil after watering. Enter those readings as `RAW_DRY` and `RAW_WET` in `soil_monitor/soil_monitor.ino`. Sensor and soil readings vary, so the values in the sketch are starting points, not universal settings. The percentage is a relative estimate, not a direct measurement of water content.
