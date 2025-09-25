const int LED_PIN_1 = 11;
const int LED_PIN_2 = 12;
const int LED_PIN_3 = 13;

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN_1, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_1, LOW);
  delay(1000);

  digitalWrite(LED_PIN_2, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_2, LOW);
  delay(1000);

  digitalWrite(LED_PIN_3, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_3, LOW);
  delay(1000);
}