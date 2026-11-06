/*
 * Soil moisture monitor
 *   FC-28 AO  -> A0
 *   16x2 LCD  -> PCF8574 @ 0x27, SDA=A4 SCL=A5
 *   SSD1306   -> 128x32, 0x3C, SDA=A4 SCL=A5
 *
 * Confirmed hardware:
 *   OLED controller = SSD1306, 128x32 (UNIVISION init)
 *   LCD backpack    = PCF8574 @ 0x27
 */
#include <Wire.h>
#include <U8g2lib.h>
#include <LiquidCrystal_I2C.h>

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Soil calibration (raw ADC): dry air ~1023, wet ~300.
const int RAW_DRY = 1023;
const int RAW_WET = 293;

static void scanBus() {
  Serial.println("I2C_SCAN");
  uint8_t n = 0;
  for (uint8_t a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) {
      n++;
      Serial.print("  ACK 0x");
      if (a < 16) Serial.print('0');
      Serial.println(a, HEX);
    }
  }
  Serial.print("I2C_TOTAL "); Serial.println(n);
}

static int moisturePct(int raw) {
  int p = map(raw, RAW_DRY, RAW_WET, 0, 100);
  return constrain(p, 0, 100);
}

static const char *stateFor(int pct) {
  if (pct < 10) return "BONE DRY";
  if (pct < 25) return "DRY";
  if (pct < 40) return "MOIST";
  if (pct < 60) return "WET";
  if (pct < 80) return "SOAKED";
  return "FLOODED";
}

static void splash() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Soil Monitor");
  lcd.setCursor(0, 1); lcd.print("Init...");

  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0, 10, "SOIL MONITOR");
  oled.drawStr(0, 22, "OLED 128x32 0x3C");
  oled.drawStr(0, 31, "LCD 0x27");
  oled.sendBuffer();
  delay(1500);
}

void setup() {
  Serial.begin(115200);
  delay(1200);
  Serial.println();
  Serial.println("=== SOIL MONITOR BOOT ===");
  Wire.begin();
  Wire.setClock(100000);
  scanBus();

  lcd.init();
  lcd.backlight();
  oled.begin();
  oled.setContrast(255);
  Serial.println("displays ready");
  splash();
}

void loop() {
  int raw = analogRead(A0);
  int pct = moisturePct(raw);
  const char *state = stateFor(pct);

  // track min/max raw
  static int minRaw = 1023, maxRaw = 0;
  if (raw < minRaw) minRaw = raw;
  if (raw > maxRaw) maxRaw = raw;

  // ---- LCD ----
  lcd.setCursor(0, 0);
  lcd.print("R");
  lcd.print(raw);
  lcd.print(" ");
  lcd.print(pct);
  lcd.print("% ");
  lcd.print(state);
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print("MN");
  lcd.print(minRaw);
  lcd.print(" MX");
  lcd.print(maxRaw);
  lcd.print("    ");

  // ---- OLED ----
  char l1raw[32], l2mm[32], l3st[32];
  snprintf(l1raw, sizeof(l1raw), "RAW %4d  PCT %3d%%", raw, pct);
  snprintf(l2mm, sizeof(l2mm), "MIN %4d  MAX %4d", minRaw, maxRaw);
  snprintf(l3st, sizeof(l3st), "%s", state);

  oled.firstPage();
  do {
    oled.setFont(u8g2_font_6x10_tf);
    oled.drawStr(0, 9, l1raw);
    oled.drawStr(0, 19, l2mm);
    oled.drawStr(0, 29, l3st);
  } while (oled.nextPage());

  Serial.print("RAW "); Serial.print(raw);
  Serial.print("  PCT "); Serial.print(pct);
  Serial.print("  "); Serial.println(state);

  delay(500);
}
