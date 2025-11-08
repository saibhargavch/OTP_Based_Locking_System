# OTP_Based_Locking_System
An advanced OTP-based door lock system using Arduino, RFID, GSM, and Keypad. When an authorized RFID card is scanned, a unique OTP is sent to the user’s mobile via GSM. The door unlocks only after entering the correct OTP, ensuring secure two-factor authentication for access control.

🔐 OTP-Based Door Lock System using RFID, Keypad, and GSM

📘 Project Overview
This project implements a secure door lock system that combines RFID technology, OTP verification, and servo-based physical control to enhance access security. 
When an authorized RFID card is scanned, a one-time password (OTP) is generated and sent to the registered mobile number via a GSM module. 
Only after entering the correct OTP on the keypad, the door unlocks automatically using a servo motor.

This ensures two-factor authentication (2FA) for access — something you have (RFID card) and something you know (OTP).

------------------------------------------------------------

⚙️ Key Features
✅ RFID-based identification of authorized users  
🔒 OTP sent to mobile via GSM for second-level verification  
🎛️ LCD display for user feedback and system status  
⌨️ Keypad input for OTP entry  
⚙️ Servo-controlled door lock mechanism  
🔄 Auto-lock feature after door access  
🧠 Arduino-powered embedded system  

------------------------------------------------------------

🧩 Hardware Components
Component | Description
---------------------------------------------
Arduino UNO | Main microcontroller board  
RFID Module (RC522) | Reads RFID card UIDs  
Servo Motor (SG90/MG90S) | Controls door lock  
GSM Module (SIM800L / SIM900A) | Sends OTP via SMS  
16x2 I2C LCD Display | Displays messages and OTP prompts  
4x3 Keypad | Allows OTP entry  
Jumper Wires | For circuit connections  
Power Supply (9V or Adapter) | Powers the Arduino and peripherals  

------------------------------------------------------------

🧠 Working Principle
1. The user swipes an RFID card.  
2. The system checks if the card’s UID is authorized.  
3. If valid, it generates a 4-digit random OTP.  
4. The OTP is sent to the user’s registered mobile number using the GSM module.  
5. The user enters the OTP using the keypad.  
6. If OTP matches → door unlocks (servo rotates).  
7. After a few seconds → door locks back automatically.  
8. If OTP is incorrect → access denied.

------------------------------------------------------------

🧾 Software Requirements
- Arduino IDE  
- MFRC522 Library  
- Keypad Library  
- Servo Library  
- LiquidCrystal_I2C Library  
- SIM800L (GSM AT Command Support)

------------------------------------------------------------

📬 Output Example
LCD displays:  
- “Swipe your card”  
- “Authorized Access”  
- “Enter OTP”  

GSM sends message:  
> “Your Door OTP is: 4732”

Upon correct OTP entry:  
- “Door Open...” → servo unlocks  
- “Door Closing...” → servo returns
