# Plant Moisture Monitor

Arduino sketch for reading soil moisture with an FC-28 sensor and showing it on a 16x2 LCD and a 128x32 SSD1306 OLED.

## How it works

The FC-28 probe measures soil moisture by electrical resistance between two electrodes.

- Dry soil gives high resistance and a high ADC value
- Wet soil gives low resistance and a low ADC value

The ADC reading is mapped to a 0-100% moisture value. Min and max raw values are tracked since boot.

Learn more: [How soil moisture sensors work](https://learn.sparkfun.com/tutorials/soil-moisture-sensor-hookup-guide)

## Wiring

| Signal | Arduino |
|---|---|
| FC-28 AO | A0 |
| SDA (LCD + OLED) | A4 |
| SCL (LCD + OLED) | A5 |
| VCC | 5V |
| GND | GND (common) |

## Addresses

- LCD (PCF8574): 0x27
- OLED (SSD1306): 0x3C, 128x32

## Build / upload

```bash
arduino-cli compile --fqbn arduino:avr:uno soil_monitor
arduino-cli upload  -p /dev/ttyACM0 --fqbn arduino:avr:uno soil_monitor
```

Libraries: U8g2, LiquidCrystal I2C.

## Calibration

Edit in soil_monitor/soil_monitor.ino:

```cpp
const int RAW_DRY = 1023;   // dry air
const int RAW_WET = 293;    // measured in water
```

## Tiers

| Tier | Moisture % |
|---|---|
| BONE DRY | < 10 |
| DRY | 10-24 |
| MOIST | 25-39 |
| WET | 40-59 |
| SOAKED | 60-79 |
| FLOODED | >= 80 |
