#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RFID setup
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {7, 6, 5};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Servo setup
Servo myservo;
int pos = 0;

// Variables
long randNumber;
char arr[10];
char mob_no[] = "8121145834";
byte key_cnt = 0;
bool keypad_flag = false;
bool door_flag = false;
bool end_flag = false;
int key_num;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("OTP BASED");
  lcd.setCursor(0, 1);
  lcd.print("DOOR LOCK SYSTEM");

  SPI.begin();
  mfrc522.PCD_Init();
  myservo.attach(3);
  delay(2000);

  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Swipe your card ");

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  // Change these UIDs according to your card values
  if (content.substring(1) == "FB 73 E5 43" || content.substring(1) == "F7 CD 8C 43") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Authorized Access");

    randNumber = random(1000, 9999); // generate 4-digit OTP
    send_sms(randNumber); // Send OTP via GSM
    key_cnt = 0;
    keypad_flag = true;

    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter OTP:");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    delay(2000);
    lcd.clear();
  }

  // OTP input from keypad
  if (keypad_flag) {
    while (true) {
      char customKey = customKeypad.getKey();
      if (customKey) {
        lcd.setCursor(key_cnt, 1);
        lcd.print(customKey);
        arr[key_cnt++] = customKey;
      }

      if (key_cnt >= 4) {
        delay(100);
        key_num = ((arr[0] - '0') * 1000) + ((arr[1] - '0') * 100) + ((arr[2] - '0') * 10) + (arr[3] - '0');
        door_flag = true;
        keypad_flag = false;
        break;
      }
    }
  }

  // Door logic
  if (door_flag) {
    delay(500);
    lcd.clear();

    if (key_num == randNumber) {
      lcd.setCursor(0, 0);
      lcd.print("Door Open...");
      for (pos = 90; pos <= 180; pos++) {
        myservo.write(pos);
        delay(15);
      }
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door Closing...");
      for (pos = 180; pos >= 90; pos--) {
        myservo.write(pos);
        delay(15);
      }

    } else {
      lcd.setCursor(0, 0);
      lcd.print("Wrong OTP!");
    }

    delay(2000);
    lcd.clear();
    door_flag = false;
  }
}

void send_sms(long otp) {
  Serial.println("AT");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=\"");
  Serial.print(mob_no);
  Serial.println("\"");
  delay(500);
  Serial.print("Your Door OTP is: ");
  Serial.println(otp);
  delay(500);
  Serial.write(26); // Ctrl+Z to send SMS
  delay(2000);
}
