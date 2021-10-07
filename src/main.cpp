#include <Arduino.h>
#include <StateMachine.h>
#include <string>

/**
 * ----------------------------------------------------------------------------
 * This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
 * for further details and other examples.
 *
 * NOTE: The library file MFRC522.h has a lot of useful info. Please read it.
 *
 * Released into the public domain.
 * ----------------------------------------------------------------------------
 * This sample shows how to read and write data blocks on a MIFARE Classic PICC
 * (= card/tag).
 *
 * BEWARE: Data will be written to the PICC, in sector #1 (blocks #4 to #7).
 *
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>

#ifndef LED_BUILTIN 
#define LED_BUILTIN 13
#endif

constexpr uint8_t PIN_MISO = 19;
constexpr uint8_t PIN_MOSI = 23;
constexpr uint8_t PIN_SCK = 18;

constexpr uint8_t RST_PIN = 3;          // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN =  21;         // Configurable, see typical pin layout above

MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN);
MFRC522 mfrc522 = MFRC522(&spiDevice);  // Create MFRC522 instance

StateMachine stateMachine;


void setup() {
  Serial.begin(9600);		
  while (!Serial);		

  SPI.begin( PIN_SCK, PIN_MISO, PIN_MOSI);
  mfrc522.PCD_Init();		
  mfrc522.PCD_DumpVersionToSerial();	
  Serial.println(F("Scan RFID tag."));
}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent())   // Look for new cards
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())   // Select one of the cards
  {
    Serial.println("Bad read (was card removed too quickly?)");
    return;
  }

  if (mfrc522.uid.size == 0) 
  {
    Serial.println("Bad card (size = 0)");
  } 
  else 
  {
    Serial.println("Good scan: ");
    Serial.print("   Size of ID: ");
    Serial.println(mfrc522.uid.size);
    stateMachine.ProcessNewScannedTag(mfrc522.uid.uidByte);
  };

  mfrc522.PICC_HaltA(); // disengage with the card.
}

