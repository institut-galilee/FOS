#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

#define PIN_BUTTON 7

#define PIN_IR 8

#define PIN_ALERT 4

#define PIN_LED_VERTE 6
#define PIN_LED_ROUGE 5

MFRC522 rfid(SS_PIN, RST_PIN); // appel de la classe

LiquidCrystal_I2C lcd(0x27, 20, 4);
// LiquidCrystal_I2C lcd(0x3F, 20, 4);

bool sys_armed = false ;

String keyOk[5] = {"86 5e a1 1f", "", "", "", ""};

void setup()
{
    Serial.begin(9600);
    SPI.begin();     // Init SPI bus
    rfid.PCD_Init(); // Init MFRC522

    lcd.init();

    pinMode(PIN_LED_VERTE,OUTPUT);
    pinMode(PIN_LED_ROUGE,OUTPUT);

    // led eteintes a l'init
    digitalWrite(PIN_LED_VERTE,LOW);
    digitalWrite(PIN_LED_ROUGE,LOW);

    pinMode(PIN_BUTTON, INPUT);

    pinMode(PIN_IR, INPUT);
}


void sendText(String txt, int x = 0, int y = 0, bool clear = true)
{
    if(clear)
    {
        lcd.clear();
        lcd.backlight();
    }

    lcd.setCursor(x, y);
    lcd.print(txt);
}

void closeLCD()
{
    lcd.clear();
    lcd.noBacklight();
}

void sendMail(){
    // Envoyer un mail au proprietaire via l'esp32
    digitalWrite(PIN_ALERT,HIGH);
    delay(10000);
    digitalWrite(PIN_ALERT,LOW);
    Serial.println("Alert send");
}

void intrusion()
{
    // processus lancer lors d'une intrusion
    sendText("Intrusion !");
    sendMail();
}

void verify_access()
{

    // Si on ne detecte pas une carte on reboucle au debut
    if (!rfid.PICC_IsNewCardPresent())
        return;

    // as t'on lu la carte
    if (!rfid.PICC_ReadCardSerial())
        return;

    // recuperation de l'UID et concaténation de sa valeur en hex dans un string
    String myKey = String(rfid.uid.uidByte[0], HEX) + " " + String(rfid.uid.uidByte[1], HEX) + " " + String(rfid.uid.uidByte[2], HEX) + " " + String(rfid.uid.uidByte[3], HEX);

    // j'affiche la valeur de la carte sur le serial
    Serial.println(myKey);

    bool accessOk = 0;
    // je boucle sur toutes les valeurs des clés autorisés et si je la trouve accesOK => 1
    for (int y = 0; y < (sizeof(keyOk) / sizeof(String)); y++)
    {

        if (keyOk[y] == myKey)
        {
            accessOk = 1;
        }
    }

    // Halt PICC, fin de lecture de carte
    rfid.PICC_HaltA();

    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();

    // La carte as t'elle acces , si oui led verte , si non led rouge
    if (accessOk == 1)
    {
        accessGranted();
    }
    else
    {
        accessDenied();
    }

    // on eteind les led apres un delais
    delay(2000);
    // digitalWrite(PIN_LED_VERTE, LOW);
    // digitalWrite(PIN_LED_ROUGE, LOW);
}

void write_access()
{
    // Si on ne detecte pas une carte on reboucle au debut
    if (!rfid.PICC_IsNewCardPresent())
        return;

    // as t'on lu la carte
    if (!rfid.PICC_ReadCardSerial())
        return;

    String myKey = String(rfid.uid.uidByte[0], HEX) + " " + String(rfid.uid.uidByte[1], HEX) + " " + String(rfid.uid.uidByte[2], HEX) + " " + String(rfid.uid.uidByte[3], HEX);

    for (int i = 0; i < 5; i++)
    {

        if (keyOk[i] == myKey)
        {
            sendText("Already saved");
            break;
        }

        if (keyOk[i] == "")
        {
            keyOk[i] = myKey;
            sendText("Write successful");
            break;
        }
    }

    delay(2000);
}

void accessGranted()
{
    digitalWrite(PIN_LED_VERTE, HIGH);
    sendText("ACCESS GRANTED");
    if(sys_armed){
        sendText("SYSTEM DESARMED", 0, 1, false);
    }else{
      sendText("ALREADY DESARMED", 0, 1, false);
    }

    sys_armed = false;

    delay(2000);
    digitalWrite(PIN_LED_VERTE, LOW);
}

void accessDenied()
{
    digitalWrite(PIN_LED_ROUGE, HIGH);
    sendText("ACCESS DENIED");
    if(!sys_armed){
        sendText("SYSTEM ARMED", 0, 1, false);
    }

    sys_armed = true;

    delay(2000);
    digitalWrite(PIN_LED_ROUGE, LOW);
}

void loop()
{

    if (digitalRead(PIN_BUTTON) == HIGH)
    {
        Serial.println("Bouton enfonce");
        write_access();
    }
    else
    {
        verify_access();
    }

    if (digitalRead(PIN_IR) == HIGH)
    {
        //sendText("Mouvement detecte");
        if (sys_armed)
        {
            intrusion();
        }
    }
    else
    {}

    delay(200);

    //sendMail();

    closeLCD();
}
