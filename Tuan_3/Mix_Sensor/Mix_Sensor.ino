#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

// Định nghĩa các chân cảm biến và thiết bị
#define DHTPIN 3
#define LDR_PIN A1
#define WATER_PIN A2
#define SOUND_PIN A0
#define LedLight_PIN 7
#define MOTOR_PIN 9
#define SERVO_PIN 4
#define BUZZER_PIN 13 // Chân điều khiển còi

// Định nghĩa loại cảm biến DHT
#define DHTTYPE DHT11

// Khai báo đối tượng
LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

void setup() {
    Serial.begin(9600);
    pinMode(LedLight_PIN, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT); // Khai báo chân còi là đầu ra
    myServo.attach(SERVO_PIN);

    lcd.init();
    lcd.backlight();
    
    lcd.setCursor(0, 0);
    lcd.print("He thong Giam Sat");
    lcd.setCursor(0, 1);
    lcd.print("Dang khoi dong...");
    delay(2000);
    lcd.clear();

    dht.begin();
}

void loop() {
    float temp = dht.readTemperature();
    float humi = dht.readHumidity();
    int ldr_value = analogRead(LDR_PIN);
    int water_value = analogRead(WATER_PIN);
    int sound_value = analogRead(SOUND_PIN);
    
    if (isnan(temp) || isnan(humi)) {
      Serial.println("Loi! Khong doc duoc du lieu tu cam bien DHT!");
      lcd.setCursor(0, 0);
      lcd.print("Loi DHT");
      delay(1000);
      return; 
    }

    Serial.print("Nhiet do: "); Serial.print(temp); Serial.print(" C\t");
    Serial.print("Do am: "); Serial.print(humi); Serial.print(" %\t");
    Serial.print("Anh sang: "); Serial.print(ldr_value); Serial.print("\t");
    Serial.print("Muc nuoc: "); Serial.print(water_value); Serial.print("\t");
    Serial.print("Am thanh: "); Serial.println(sound_value);

    // Hiển thị dữ liệu lên LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temp);
    lcd.print("C H:");
    lcd.print(humi);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("L:");
    lcd.print(ldr_value);
    lcd.print(" W:");
    lcd.print(water_value);
    lcd.print(" S:");
    lcd.print(sound_value);

    // --- Logic điều khiển các thiết bị ---

    // Điều khiển quạt và cửa servo dựa trên nhiệt độ
    if (temp > 35) {
      digitalWrite(MOTOR_PIN, HIGH);
      myServo.write(90);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp > 35C");
      lcd.setCursor(0, 1);
      lcd.print("Bat quat! Mo cua!");
      tone(BUZZER_PIN, 1000); // Bật còi khi nhiệt độ cao
      delay(2000);
      noTone(BUZZER_PIN); // Tắt còi sau khi cảnh báo
    } else {
      digitalWrite(MOTOR_PIN, LOW);
      myServo.write(0);
    }

    // Điều khiển đèn dựa trên ánh sáng
    if (ldr_value < 300) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Troi toi bat den");
      digitalWrite(LedLight_PIN, HIGH);
      tone(BUZZER_PIN, 1000); // Bật còi khi trời tối
      delay(2000);
      noTone(BUZZER_PIN); // Tắt còi sau khi cảnh báo
    } else {
      digitalWrite(LedLight_PIN, LOW);
    }

    // Cảnh báo mực nước cao
    if (water_value > 300) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CANH BAO!");
      lcd.setCursor(0, 1);
      lcd.print("Muc nuoc cao!");
      tone(BUZZER_PIN, 1000); // Bật còi khi mực nước cao
      delay(2000);
      noTone(BUZZER_PIN); // Tắt còi sau khi cảnh báo
    }

    // Cảnh báo âm thanh lớn
    if (sound_value > 190) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CANH BAO!");
      lcd.setCursor(0, 1);
      lcd.print("Am thanh qua lon!");
      tone(BUZZER_PIN, 1000); // Bật còi khi âm thanh lớn
      delay(2000);
      noTone(BUZZER_PIN); // Tắt còi sau khi cảnh báo
    }

    delay(1000);
}
