#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>

#define SS_PIN 10
#define RST_PIN 9
#define IR_PIN 7
#define TRIG_PIN 4
#define ECHO_PIN 2
#define BUZZER_PIN 6
#define SERVO_PIN 8

struct ObjectData {
    byte uid[4];
    char name[16];
    int distance_cm;
    bool is_registered;
};

const int MAX_SLOTS = 5;
const int DATA_SIZE = sizeof(ObjectData);
const int EEPROM_BASE = 0;

enum SystemState {
    IDLE = 0,
    DETECTED = 1,
    VERIFYING = 2
};

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
Servo controlServo;

SystemState currentState = IDLE;
unsigned long lastActivityTime = 0;
ObjectData currentItem;
const int DISTANCE_TOLERANCE = 1;

void resetSystem();
void servoOpen();
void servoClose();
void buzz(int freq, int duration);
long measureDistance();
void eepromWriteData(int slot, const ObjectData *data);
void eepromReadData(int slot, ObjectData *data);
ObjectData getObjectDataByUID(byte *uid);
void handleSerialCommands();
void handleIdleState();
void handleDetectedState();
void handleVerifyingState();
void printUID(byte *uid);


void setup() {
    Serial.begin(9600);
    pinMode(IR_PIN, INPUT_PULLUP);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    
    lcd.init();
    lcd.backlight();
    SPI.begin();
    rfid.PCD_Init();

    controlServo.attach(SERVO_PIN);
    
    resetSystem();
    Serial.println("System Initialized. Use commands: REG, DELALL, LIST");
}

void loop() {
    if (currentState != IDLE && (millis() - lastActivityTime > 2000)) {
        buzz(1000, 300); 
        Serial.println("Timeout: Resetting to IDLE.");
        resetSystem();
        return; 
    }
    
    switch (currentState) {
        case IDLE:
            handleIdleState();
            break;
        case DETECTED:
            handleDetectedState();
            break;
        case VERIFYING:
            handleVerifyingState();
            break;
    }

    handleSerialCommands();
}

void servoOpen() {
    controlServo.write(0);
}

void servoClose() {
    controlServo.write(90);
}

void buzz(int freq, int duration) {
    tone(BUZZER_PIN, freq, duration);
}

long measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // Thêm timeout để tránh bị treo nếu không nhận được xung
    long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
    
    if (duration == 0) return 999; 

    return duration * 0.034 / 2;
}

void resetSystem() {
    currentState = IDLE;
    lastActivityTime = millis();
    servoOpen();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM READY");
    lcd.setCursor(0, 1);
    lcd.print("Access OPEN");
}

void eepromWriteData(int slot, const ObjectData *data) {
    int addr = EEPROM_BASE + slot * DATA_SIZE;
    EEPROM.put(addr, *data);
}

void eepromReadData(int slot, ObjectData *data) {
    int addr = EEPROM_BASE + slot * DATA_SIZE;
    EEPROM.get(addr, *data);
}

ObjectData getObjectDataByUID(byte *uid) {
    ObjectData temp;
    for (int i = 0; i < MAX_SLOTS; i++) {
        eepromReadData(i, &temp);
        if (temp.is_registered) {
            bool match = true;
            for (int j = 0; j < 4; j++) {
                if (temp.uid[j] != uid[j]) {
                    match = false;
                    break;
                }
            }
            if (match) return temp;
        }
    }
    ObjectData notFound = { {0, 0, 0, 0}, "Not Found", 0, false };
    return notFound;
}

void handleIdleState() {
    if (digitalRead(IR_PIN) == LOW) { 
        currentState = DETECTED;
        lastActivityTime = millis();
        Serial.println("!!! Object Detected by IR. Locking access.");
        servoClose();
        buzz(500, 100); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Object Removed!");
        lcd.setCursor(0, 1);
        lcd.print("Scan Tag To ID");
    }
}

void handleDetectedState() {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        byte *uid = rfid.uid.uidByte;
        currentItem = getObjectDataByUID(uid); 
        
        if (currentItem.is_registered) {
            currentState = VERIFYING;
            lastActivityTime = millis();
            buzz(1200, 100);
            lcd.clear();
            lcd.print("Tag OK: ");
            lcd.print(currentItem.name);
            lcd.setCursor(0, 1);
            lcd.print("Checking Shape...");
        } else {
            buzz(300, 300);
            lcd.setCursor(0, 1);
            lcd.print("! Access Denied !");
            delay(1000); 
            lcd.setCursor(0, 1);
            lcd.print("Scan Tag To ID");
            lastActivityTime = millis(); 
        }
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }
}

void handleVerifyingState() {
    long currentDist = measureDistance();
    
    if (abs(currentDist - currentItem.distance_cm) <= DISTANCE_TOLERANCE) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Verification OK!");
        lcd.setCursor(0, 1);
        lcd.print(currentItem.name);
        
        buzz(1800, 200);
        servoOpen(); 
        delay(3000); 
        resetSystem();
    } else {
        lcd.clear();
        lcd.print("Shape Mismatch!");
        lcd.setCursor(0, 1);
        lcd.print("Act:");
        lcd.print(currentDist);
        lcd.print(" Exp:");
        lcd.print(currentItem.distance_cm);
        
        buzz(400, 500);
        delay(3000);
        
        currentState = DETECTED; 
        lastActivityTime = millis();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("! Mismatch Error !");
        lcd.setCursor(0, 1);
        lcd.print("Scan Tag To ID");
    }
}

void printUID(byte *uid) {
    for (int i = 0; i < 4; i++) {
        if (uid[i] < 0x10) Serial.print("0");
        Serial.print(uid[i], HEX);
        if (i < 3) Serial.print(":");
    }
}

void handleSerialCommands() {
    if (!Serial.available()) return;

    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toUpperCase(); 
    
    if (cmd == "DELALL") {
        ObjectData empty = { {0, 0, 0, 0}, "", 0, false };
        for (int i = 0; i < MAX_SLOTS; i++) {
            eepromWriteData(i, &empty);
        }
        Serial.println(">>> SUCCESS: All EEPROM slots cleared (DELALL).");
        return;
    }
    
    if (cmd == "LIST") {
        Serial.println("--- EEPROM Registered Items ---");
        for (int i = 0; i < MAX_SLOTS; i++) {
            ObjectData item;
            eepromReadData(i, &item);
            Serial.print("Slot ");
            Serial.print(i);
            Serial.print(": ");
            if (item.is_registered) {
                Serial.print("UID=");
                printUID(item.uid);
                Serial.print(", Name=");
                Serial.print(item.name);
                Serial.print(", Dist=");
                Serial.print(item.distance_cm);
                Serial.println("cm");
            } else {
                Serial.println("EMPTY");
            }
        }
        Serial.println("---------------------------------");
        return;
    }


    if (cmd.startsWith("REG ")) {
        String fullCmd = cmd.substring(4); 
        
        int comma1 = fullCmd.indexOf(',');
        int comma2 = fullCmd.indexOf(',', comma1 + 1);

        if (comma1 == -1 || comma2 == -1) {
            Serial.println("Error: Invalid format. Use REG <UID>,<Name>,<Dist>");
            return;
        }

        String uidStr = fullCmd.substring(0, comma1);
        String nameStr = fullCmd.substring(comma1 + 1, comma2);
        String distStr = fullCmd.substring(comma2 + 1);

        uidStr.trim();
        nameStr.trim();
        distStr.trim();

        if (uidStr.length() != 11) {
            Serial.println("Error: UID format must be XX:XX:XX:XX (11 chars).");
            return;
        }

        byte uid[4];
        for (int i = 0; i < 4; i++) {
            String hx = uidStr.substring(i * 3, i * 3 + 2); 
            if (hx.length() < 2) {
                Serial.println("Error: UID conversion failed.");
                return;
            }
            uid[i] = (byte)strtol(hx.c_str(), NULL, 16);
        }

        int distance = distStr.toInt();
        if (distance == 0) {
            Serial.println("Error: Distance must be a number > 0.");
            return;
        }
        
        ObjectData newData;
        memcpy(newData.uid, uid, 4);
        nameStr.toCharArray(newData.name, 16);
        newData.distance_cm = distance;
        newData.is_registered = true;

        int emptySlot = -1;
        for (int i = 0; i < MAX_SLOTS; i++) {
            ObjectData temp;
            eepromReadData(i, &temp);
            if (!temp.is_registered) { 
                emptySlot = i;
                break;
            }
        }

        if (emptySlot != -1) {
            eepromWriteData(emptySlot, &newData);
            Serial.print("SUCCESS: Registered ");
            Serial.print(newData.name);
            Serial.print(" to slot ");
            Serial.print(emptySlot);
            Serial.print(" with Dist ");
            Serial.print(distance);
            Serial.println("cm.");
        } else {
            Serial.println("ERROR: No empty registration slots available. Use DELALL to reset.");
        }
    } else {
        Serial.println("Cmd? Use: REG <UID>,<Name>,<Dist> | DELALL | LIST");
    }
}
