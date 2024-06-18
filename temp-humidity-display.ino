#include <dht.h>
#include <LiquidCrystal.h>


const long READ_DELAY = 5000; // update delay interval

const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5; // lcd display pin connections
const LiquidCrystal lcd_driver(rs, en, d4, d5, d6, d7);

const dht dht_sensor;
const int DHT11_PIN = 13; // dht11 data pin connection

const int WARNING_LED_PIN = 10; // led pin connection

void setup() {
  Serial.begin(9600);
  lcd_driver.begin(16, 2);
  lcd_driver.noAutoscroll();
  pinMode(WARNING_LED_PIN, OUTPUT);
}

void loop() {
  int dht_output = dht_sensor.read11(DHT11_PIN);
  handle_dht11_output(dht_output);
  delay(READ_DELAY);
}

void handle_dht11_output(int dht_output) {
  if (dht_output == DHTLIB_OK) {
    String temp_str = "Temp:     " + String(dht_sensor.temperature) + "C";
    String humidity_str = "Humidity: " + String(dht_sensor.humidity) + "%";
    Serial.println(temp_str);
    Serial.println(humidity_str);
    display_on_lcd(temp_str, humidity_str);

    if(dht_sensor.temperature >= 25) {
      digitalWrite(WARNING_LED_PIN, HIGH);
    } else {
      digitalWrite(WARNING_LED_PIN, LOW);
    }
  }
}

void display_on_lcd(String temperature_str, String humidity_str) {
  lcd_driver.clear();
  lcd_driver.print(temperature_str);
  lcd_driver.setCursor(0, 2);
  lcd_driver.print(humidity_str);
}
