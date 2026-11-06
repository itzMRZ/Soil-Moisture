# Plant Moisture Monitor

Arduino Uno R3 + FC-28 soil sensor + 16×2 I2C LCD + SSD1306 OLED.

## Wiring

| Signal | Arduino |
|---|---|
| FC-28 AO | A0 |
| SDA (LCD + OLED) | A4 |
| SCL (LCD + OLED) | A5 |
| VCC | 5V |
| GND | GND (common) |

## Addresses

- LCD (PCF8574): **0x27**
- OLED (SSD1306): **0x3C**, **128×32** (use the 128×32 U8g2 constructor — 128×64 garbles it)

## Build / upload

```bash
arduino-cli compile --fqbn arduino:avr:uno soil_monitor
arduino-cli upload  -p /dev/ttyACM0 --fqbn arduino:avr:uno soil_monitor
```

Libraries: **U8g2**, **LiquidCrystal I2C**.

## Calibration

Edit in `soil_monitor.ino`:

```cpp
const int RAW_DRY = 1023;   // dry air
const int RAW_WET = 300;    // measure in water/wet soil
```

Sensor is inverted: lower raw = wetter. Current probe reads 1023 (dry, 0%).
