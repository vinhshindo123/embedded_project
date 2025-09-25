#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

const int btnPin = 2; // Chân ngắt
const int ledPin = 7; // Chân đèn LED (đỏ)
const int greenLedPin = 6; // Chân đèn LED xanh
const int buzzerPin = 8; // Chân còi (nếu có)
const int servoPin = 11; // Chân servo

volatile bool buttonPressed = false;

// Hàm xử lý ngắt khi nút được nhấn
void onButton() {
  buttonPressed = true;
}

void setup() {
  lcd.init();
  lcd.backlight();
  
  myServo.attach(servoPin); // Khởi tạo servo ở chân 11
  myServo.write(0); // Quay về vị trí ban đầu (0 độ)
  
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(btnPin), onButton, FALLING);
  
  randomSeed(analogRead(A0));
  
  lcd.setCursor(0, 0);
  lcd.print("Tro choi");
  lcd.setCursor(0, 1);
  lcd.print("Danh len");
  delay(3000);
}

void loop() {
  // Trạng thái chờ lượt chơi mới
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhan nut de choi");
  myServo.write(0);
  digitalWrite(greenLedPin, LOW); // Tắt đèn xanh
  
  buttonPressed = false;
  
  // Chờ người chơi nhấn nút để bắt đầu
  while(!buttonPressed) {
    delay(50);
  }
  
  // Giai đoạn chờ
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ke dich dang o gan...");
  
  buttonPressed = false;

  unsigned long waitTime = random(5000, 10000);
  unsigned long startTime = millis();
  
  while (millis() - startTime < waitTime) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    
    // Kiểm tra nếu người chơi tấn công quá sớm
    if (buttonPressed) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HANH DONG QUA SOM!");
      noTone(buzzerPin);
      tone(buzzerPin, 200, 1000); // Âm thanh thất bại
      delay(3000);
      return; // Bắt đầu lại vòng lặp
    }
  }

  // Giai đoạn tấn công
  digitalWrite(ledPin, LOW); // Tắt đèn đỏ
  myServo.write(90); // Quay servo 90 độ
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ke dich ngu gat!");
  digitalWrite(greenLedPin, LOW);
  lcd.setCursor(0, 1);
  lcd.print("TAN CONG!");
  
  buttonPressed = false;
  startTime = millis();
  
  // Chờ người chơi trong 1 giây
  while (millis() - startTime < 1000) {
    if (buttonPressed) {
      digitalWrite(greenLedPin, HIGH); // Bật đèn xanh
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TIEN CONG THANH CONG!");
      tone(buzzerPin, 1500, 1000); // Âm thanh chiến thắng to hơn và kéo dài
      delay(3000);
      return; // Bắt đầu lại vòng lặp
    }
  }
  
  // Xử lý khi người chơi chậm trễ
  if (!buttonPressed) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("KE DICH PHAT HIEN!");
    lcd.setCursor(0, 1);
    lcd.print("Ban da that bai!");
    noTone(buzzerPin);
    tone(buzzerPin, 200, 1000); // Âm thanh thất bại
    delay(3000);
  }
}