#include <Arduino.h>
#include "ESP32_MailClient.h"
#include "SD.h"

#include "image.h"

#define PIN_ALERT 16

const char* WIFI_SSID = "salut";
const char* WIFI_PASSWORD = "salutsalut";

const char* DESTINATAIRE = "kage7340@gmail.com";
const char* EXPEDITEUR = "FOS.projet@gmail.com";
const char* EXPEDITEUR_MDP = "FOSIOT2020";

const char* PSEUDO = "ESP32_IOT";
const char* PSEUDO_MAIL = "noreply@FOS.com";


//The Email Sending data object contains config and data to send
SMTPData smtpData;

//Callback function to get the Email sending status
void sendCallback(SendStatus info);
void sendEmail();

void setup()
{

  Serial.begin(9600);
  
  pinMode(PIN_ALERT, INPUT);

  Serial.println();
  Serial.print("Connecting to AP");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop()
{
  /*if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(200);
    }
  }*/

  if(digitalRead(PIN_ALERT) == HIGH){ //Reception du signal d'alerte
    Serial.println("Signal recu");
    sendEmail();
  }
    
}

void sendCallback(SendStatus msg)
{
  Serial.println(msg.info());

  if (msg.success())
  {
    Serial.println("Message envoye");
  }
}

void sendEmail(){
  Serial.println("Mounting SD Card...");

  if (SD.begin()) // MailClient.sdBegin(14,2,15,13) for TTGO T8 v1.7 or 1.8
  {

    Serial.println("Preparing attach file...");

    File file = SD.open("/text_file.txt", FILE_WRITE);
    file.print("Hello World!\r\nHello World!");
    file.close();

    file = SD.open("/binary_file.dat", FILE_WRITE);

    static uint8_t buf[512];

    buf[0] = 'H';
    buf[1] = 'E';
    buf[2] = 'A';
    buf[3] = 'D';
    file.write(buf, 4);

    size_t i;
    memset(buf, 0xff, 512);
    for (i = 0; i < 2048; i++)
    {
      file.write(buf, 512);
    }

    buf[0] = 'T';
    buf[1] = 'A';
    buf[2] = 'I';
    buf[3] = 'L';
    file.write(buf, 4);

    file.close();
  }
  else
  {
    Serial.println("SD Card Monting Failed");
  }

  Serial.println();


  Serial.println("Sending email...");

  smtpData.setLogin("smtp.gmail.com", 587, EXPEDITEUR, EXPEDITEUR_MDP);
  
  smtpData.setSender(PSEUDO, PSEUDO_MAIL);

  smtpData.setPriority("High");

  smtpData.setSubject("ESP32 SMTP Mail Sending Test");

  smtpData.setMessage("<div style=\"color:#ff0000;font-size:20px;\">Hello World! - From ESP32</div>", true);

  smtpData.addRecipient(DESTINATAIRE);



  //Add attachments, can add the file or binary data from flash memory, file in SD card
  //Data from internal memory
  smtpData.addAttachData("firebase_logo.png", "image/png", (uint8_t *)dummyImageData, sizeof dummyImageData);

  //Add attach files from SD card
  //Comment these two lines, if no SD card connected
  //Two files that previousely created.
  //smtpData.addAttachFile("/binary_file.dat");
  //smtpData.addAttachFile("/text_file.txt");


  //Add some custom header to message
  //See https://tools.ietf.org/html/rfc822
  //These header fields can be read from raw or source of message when it received)
  smtpData.addCustomMessageHeader("Date: Sat, 10 Aug 2019 21:39:56 -0700 (PDT)");
  //Be careful when set Message-ID, it should be unique, otherwise message will not store
  //smtpData.addCustomMessageHeader("Message-ID: <abcde.fghij@gmail.com>");

  //Set the storage types to read the attach files (SD is default)
  //smtpData.setFileStorageType(MailClientStorageType::SPIFFS);
  smtpData.setFileStorageType(MailClientStorageType::SD);



  smtpData.setSendCallback(sendCallback);

  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  smtpData.empty();
}
