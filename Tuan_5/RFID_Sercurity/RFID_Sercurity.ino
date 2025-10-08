#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Khởi tạo LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Định nghĩa chân cắm
const int POT_PIN = A0;   // Chân biến trở
const int BUZ_PIN = 10;   // Chân còi báo (PWM)
const int LED_RED = 9;    // Chân màu Đỏ (PWM)
const int LED_GREEN = 6;  // Chân màu Xanh lá cây (PWM)
const int LED_BLUE = 5;   // Chân màu Xanh dương (PWM)
const int BTN_PIN = 2;    // Chân nút nhấn

// Biến toàn cục
int secret_number;
int guess_count = 0;
int player_guess_value;

// Đặt giá trị cho vùng đệm (deadband)
const int DEAD_BAND = 3;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZ_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  randomSeed(analogRead(A1));
  newGame();
}

void loop() {
  // 1. Đọc và chuyển đổi giá trị biến trở
  int raw_value = analogRead(POT_PIN);
  player_guess_value = map(raw_value, 0, 1023, 0, 255);

  // 2. Hiển thị thông tin lên LCD
  lcd.setCursor(0, 0);
  lcd.print("Ban doan: ");
  lcd.print(player_guess_value);
  lcd.print("    ");

  // 3. Cung cấp gợi ý (lớn hơn/nhỏ hơn)
  if (player_guess_value < secret_number - 50) {
    lcd.setCursor(0, 1);
    lcd.print("Gia tri nho hon");
  } else if (player_guess_value > secret_number + 50) {
    lcd.setCursor(0, 1);
    lcd.print("Lon hon!       ");
  } else {
    // Nếu giá trị chính xác, hiển thị "OK"
    lcd.setCursor(0, 1);
    lcd.print("Gan dung roi!   ");
  }

  // 4. Phản hồi màu sắc và âm thanh
  int diff = abs(player_guess_value - secret_number);

  if ((player_guess_value >= 0 && player_guess_value <= 5) || (player_guess_value >= 249 && player_guess_value <= 254)) {
    // Giá trị ở hai đầu dải đo: Đỏ
    setColor(255, 0, 0); 
  } else if ((player_guess_value >= 6 && player_guess_value < secret_number - 50) || (player_guess_value <= 248 && player_guess_value > secret_number + 50)) {
    // Khoảng từ 6 đến cách điểm đích trên dưới 50: Vàng
    setColor(255, 255, 0);
  } else if ((player_guess_value >= secret_number - 50 && player_guess_value < secret_number - 30) || (player_guess_value <= secret_number + 50 && player_guess_value > secret_number + 30)) {
    // Khoảng từ cách điểm đích trên dưới 50 đến 30: Xanh da trời
    setColor(0, 255, 255);
  } else {
    // Còn lại (trong khoảng trên dưới 30): Xanh lá cây
    setColor(0, 255, 0); 
  }

  analogWrite(BUZ_PIN, player_guess_value);

  // 5. Kiểm tra nút nhấn để xác nhận đoán và quyết định thắng/thua
  if (digitalRead(BTN_PIN) == LOW) {
    delay(50); // Chống dội nút
    if (digitalRead(BTN_PIN) == LOW) {
      guess_count++;
      
      if (abs(player_guess_value - secret_number) <= DEAD_BAND) {
        winGame();
      } else {
        // Nếu đoán sai, thông báo và cho người chơi tiếp tục
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ban doan sai!");
        setColor(255, 0, 0);

        // Còi cảnh báo cao 2 lần
        analogWrite(BUZ_PIN, 254);
        delay(500);
        analogWrite(BUZ_PIN, 0);
        delay(600);
        analogWrite(BUZ_PIN, 254);
        delay(500);
        analogWrite(BUZ_PIN, 0);

        setColor(0, 0, 0);
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ban doan: ");
        lcd.print(player_guess_value);
      }
      
      while (digitalRead(BTN_PIN) == LOW);
    }
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(LED_RED, 255 - redValue);
  analogWrite(LED_GREEN, 255 - greenValue);
  analogWrite(LED_BLUE, 255 - blueValue);
}

void newGame() {
  secret_number = random(0, 256);
  guess_count = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hay doan so!");
  lcd.setCursor(0, 1);
  lcd.print("Luot: 0        ");
}

void winGame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chien thang!");
  lcd.setCursor(0, 1);
  lcd.print("Luot: ");
  lcd.print(guess_count);
  
  // Hiệu ứng nhấp nháy nhiều màu và tiếng bíp
  for (int i = 0; i < 5; i++) {
    setColor(255, 0, 0); // Đỏ
    tone(BUZ_PIN, 500);
    delay(200);
    setColor(0, 255, 0); // Xanh lá
    tone(BUZ_PIN, 1000);
    delay(200);
    setColor(0, 0, 255); // Xanh dương
    tone(BUZ_PIN, 1500);
    delay(200);
    noTone(BUZ_PIN);
  }
  
  setColor(0, 0, 0); // Tắt đèn
  delay(1000);
  newGame();
}