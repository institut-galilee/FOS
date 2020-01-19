// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <ArduinoJson.h>
// #include "ESP32_MailClient.h"

// SMTPData smtpData;

// const char *ssid = "salut";
// const char *password = "salutsalut";

// const char *API_KEY = "710705bcd74a697f99ec2d5e020b1229";

// void scanNetworks()
// {

//     int numberOfNetworks = WiFi.scanNetworks();

//     Serial.print("Number of networks found: ");
//     Serial.println(numberOfNetworks);

//     for (int i = 0; i < numberOfNetworks; i++)
//     {

//         Serial.print("Network name: ");
//         Serial.println(WiFi.SSID(i));

//         Serial.print("Signal strength: ");
//         Serial.println(WiFi.RSSI(i));

//         Serial.print("MAC address: ");
//         Serial.println(WiFi.BSSIDstr(i));

//         //Serial.print("Encryption type: ");
//         //Serial.print(WiFi.encryptionType(i)); the type is  wifi_auth_mode_t

//         Serial.println("-----------------------");
//     }
// }

// void connectToNetwork()
// {
//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(1000);
//         Serial.println("Establishing connection to WiFi..");
//     }

//     Serial.println("Connected to network");
// }

// void printWiFiInfo()
// {
//     Serial.println(WiFi.macAddress());
//     Serial.println(WiFi.localIP());

//     WiFi.disconnect(true);
//     Serial.println(WiFi.localIP());
// }

// void SendGetRequest(){
//  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
//     HTTPClient http;
 
//     http.begin("http://api.openweathermap.org/data/2.5/weather?q=Paris,fr&units=metric&APPID=710705bcd74a697f99ec2d5e020b1229"); //Specify the URL 
//     //(A test json server: https://jsonplaceholder.typicode.com/guide.html)
    
//     int httpCode = http.GET();     //Make the request
 
//     if (httpCode > 0) { //Check for the returning code
 
//         String payload = http.getString();
//         //Serial.println(httpCode);
//         //Serial.println(payload);
        
//         DynamicJsonDocument doc(1024);
//         deserializeJson(doc, payload);
//         JsonObject obj = doc.as<JsonObject>();
//         float temp = obj["main"]["temp"];
//         Serial.println( temp );
//       }
 
//     else {
//       Serial.println("Error on HTTP request Code:"+httpCode);
//     }
 
//     http.end(); //Free the resources
//   }
// }

// void SendPostRequest()
// {
//     if ((WiFi.status() == WL_CONNECTED))
//     { //Check the current connection status

//         HTTPClient http;

//         http.begin("http://api.openweathermap.org/data/2.5/weather?q=Paris,fr&units=metric&APPID=710705bcd74a697f99ec2d5e020b1229"); //Specify destination for HTTP request
//         http.addHeader("Content-Type", "application/json");

//         DynamicJsonDocument doc(200);
//         doc["title"] = "title";
//         doc["body"] = "body";
//         doc["userId"] = "1";

//         String output;
//         serializeJsonPretty(doc, output); // You can also use serializeJson(doc, Serial);
//         Serial.println(output);

//         int httpCode = http.POST(output); //Send the actual POST request
//         if (httpCode > 0)
//         {
//             String response = http.getString(); //Get the response to the request
//             Serial.println(httpCode);           //Print return code
//             Serial.println(response);           //Print request answer
//         }
//         else
//         {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpCode);
//         }
//     }
// }

// void initMail(){
//   smtpData.setLogin("smtp.gmail.com", 587, "FOS.projet@gmail.com", "fos.projet");

//   smtpData.addCustomMessageHeader("Date: Sat, 10 Aug 2019 21:39:56 -0700 (PDT)");
//   smtpData.addCustomMessageHeader("Message-ID: <10000.30000@gmail.com>");

//   smtpData.setDebug(true);

//   smtpData.setSender("ESP32", "FOS.projet@gmail.com");
//   smtpData.addRecipient("kage7340@gmail.com");
//   smtpData.setPriority("High");
//   smtpData.setSubject("ESP32 Send Mail Test");
//   smtpData.setMessage("This is plain text message", false);
// }

// // --------------------------------------------------------------------------------------------------
// void setup()
// {
//     Serial.begin(9600);

//     //scanNetworks();
//     //delay(5000);
//     connectToNetwork();
//     //delay(5000);
//     //printWiFiInfo();
//     initMail();
//     MailClient.sendMail(smtpData);
// }

// void loop()
// {
//     // Serial.println(WiFi.status());
//     // Serial.print("wl_connected = ");
//     // Serial.println(WL_IDLE_STATUS);


//     //SendGetRequest();

//     //SendPostRequest();

//     delay(5000);
// }

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#include "I2C.h"
#include "FifoCamera.h"

const int VSYNC = 32; //vertical sync
const int SIOD = 21; //SDA
const int SIOC = 22; //SCL

const int RRST = 17;  //read reset
const int WRST = 16;  //write reset
const int RCK = 4;    //read clock
const int WR = 0;     //write flag
//OE -> GND     (output enable always on since we control the read clock)
//PWDN not nonnected  
//HREF not connected
//STR not connected
//RST -> 3.3V 

const int D0 = 13;
const int D1 = 12;
const int D2 = 14;
const int D3 = 27;
const int D4 = 26;
const int D5 = 25;
const int D6 = 35;
const int D7 = 34;

const int TFT_CS = 2; //chip select
const int TFT_RST = 0; //connected to EN on LOLIN32
const int TFT_DC = 15; //data/command pin
//DIN <- MOSI 23
//CLK <- SCK 18

I2C<SIOD, SIOC> i2c;
FifoCamera<I2C<SIOD, SIOC>, RRST, WRST, RCK, WR, D0, D1, D2, D3, D4, D5, D6, D7> camera(i2c);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#define QQVGA
//#define QQQVGA

#ifdef QQVGA
const int XRES = 160;
const int YRES = 120;
#endif
#ifdef QQQVGA
const int XRES = 80;
const int YRES = 60;
#endif

const int BYTES_PER_PIXEL = 2;
const int frameSize = XRES * YRES * BYTES_PER_PIXEL;
unsigned char frame[frameSize];

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initialization...");
  i2c.init();
  camera.init();
  
  #ifdef QQVGA
    camera.QQVGARGB565();
  #endif
  #ifdef QQQVGA
    camera.QQQVGARGB565();
  #endif
  
  //camera.QQVGAYUV();
  //camera.RGBRaw();
  //camera.testImage();
  
  pinMode(VSYNC, INPUT);
  Serial.println("start");
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(0);
}

void displayRGB565()
{
  tft.setAddrWindow(0, 0, YRES - 1, XRES - 1);
  int i = 0;
  for(int x = 0; x < XRES; x++)
    for(int y = 0; y < YRES; y++)
    {
      i = (y * XRES + x) << 1;
      tft.pushColor(frame[i] | (frame[i + 1] << 8));
      //tft.pushColor(((frame[i] | (frame[i + 1] << 8)) >> 1) & 0b111101111101111); //dimming to test for tft error
    }  
}

void testTFT() //a small tft test output showing errors on my tft with bright colors
{
  tft.setAddrWindow(0, 0, 31, 63);
  int i = 0;
  for(int y = 0; y < 64; y++)
    for(int x = 0; x < 32; x++)
      tft.pushColor(x | y << 5);
}

void displayY8()
{
  tft.setAddrWindow(0, 0, YRES - 1, XRES - 1);
  int i = 0;
  for(int x = 0; x < XRES; x++)
    for(int y = 0; y < YRES; y++)
    {
      i = y * XRES + x;
      unsigned char c = frame[i];
      unsigned short r = c >> 3;
      unsigned short g = c >> 2;
      unsigned short b = c >> 3;
      tft.pushColor(r << 11 | g << 5 | b);
    }  
}

void frameToSerial()
{
  int i = 0;
  Serial.println("var frame=[");
  for(int y = 0; y < YRES; y+=1)
  {
    i = y * XRES;
    for(int x = 0; x < XRES; x+=1)
    {
      //Serial.print(frame[i + x], HEX);
      Serial.print(frame[i + x]);
      Serial.print(',');
    }
    Serial.println();
  }
  Serial.println("];");  
}

void loop() 
{
  while(!digitalRead(VSYNC));
  while(digitalRead(VSYNC));
  camera.prepareCapture();
  camera.startCapture();
  while(!digitalRead(VSYNC));
  camera.stopCapture();

  //color
  camera.readFrame(frame, XRES, YRES, BYTES_PER_PIXEL);
  displayRGB565();
  
  //testTFT();
  
  //b/w 
  camera.readFrameOnlySecondByte(frame, XRES, YRES);
  displayY8();
}
