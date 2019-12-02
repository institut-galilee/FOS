#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "salut";
const char *password = "salutsalut";

const char *API_KEY = "710705bcd74a697f99ec2d5e020b1229";

void scanNetworks()
{

    int numberOfNetworks = WiFi.scanNetworks();

    Serial.print("Number of networks found: ");
    Serial.println(numberOfNetworks);

    for (int i = 0; i < numberOfNetworks; i++)
    {

        Serial.print("Network name: ");
        Serial.println(WiFi.SSID(i));

        Serial.print("Signal strength: ");
        Serial.println(WiFi.RSSI(i));

        Serial.print("MAC address: ");
        Serial.println(WiFi.BSSIDstr(i));

        //Serial.print("Encryption type: ");
        //Serial.print(WiFi.encryptionType(i)); the type is  wifi_auth_mode_t

        Serial.println("-----------------------");
    }
}

void connectToNetwork()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Establishing connection to WiFi..");
    }

    Serial.println("Connected to network");
}

void printWiFiInfo()
{
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());

    WiFi.disconnect(true);
    Serial.println(WiFi.localIP());
}

void SendGetRequest(){
 if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=Paris,fr&units=metric&APPID=710705bcd74a697f99ec2d5e020b1229"); //Specify the URL 
    //(A test json server: https://jsonplaceholder.typicode.com/guide.html)
    
    int httpCode = http.GET();     //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        //Serial.println(httpCode);
        //Serial.println(payload);
        
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        float temp = obj["main"]["temp"];
        Serial.println( temp );
      }
 
    else {
      Serial.println("Error on HTTP request Code:"+httpCode);
    }
 
    http.end(); //Free the resources
  }
}

void SendPostRequest()
{
    if ((WiFi.status() == WL_CONNECTED))
    { //Check the current connection status

        HTTPClient http;

        http.begin("http://api.openweathermap.org/data/2.5/weather?q=Paris,fr&units=metric&APPID=710705bcd74a697f99ec2d5e020b1229"); //Specify destination for HTTP request
        http.addHeader("Content-Type", "application/json");

        DynamicJsonDocument doc(200);
        doc["title"] = "title";
        doc["body"] = "body";
        doc["userId"] = "1";

        String output;
        serializeJsonPretty(doc, output); // You can also use serializeJson(doc, Serial);
        Serial.println(output);

        int httpCode = http.POST(output); //Send the actual POST request
        if (httpCode > 0)
        {
            String response = http.getString(); //Get the response to the request
            Serial.println(httpCode);           //Print return code
            Serial.println(response);           //Print request answer
        }
        else
        {
            Serial.print("Error on sending POST: ");
            Serial.println(httpCode);
        }
    }
}

// --------------------------------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);

    //scanNetworks();
    //delay(5000);
    connectToNetwork();
    //delay(5000);
    //printWiFiInfo();
}

void loop()
{
    // Serial.println(WiFi.status());
    // Serial.print("wl_connected = ");
    // Serial.println(WL_IDLE_STATUS);


    SendGetRequest();

    //SendPostRequest();

    delay(5000);
}
