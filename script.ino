#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


int pourcentage = 0; 
//int miseEnMarche = 6;

int sensorPin = A0; 
int led_verte = 13;
int led_rouge = 12;
int relay = 14;
int signal_sensor =3;

int hsol;

const char* ssid = "Redmi10";
const char* password = "mayif56jordan";

WiFiServer server(80);
WiFiClient wifiClient;

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>Arrosage Control</title></head><body><div id='main'><h2>Arrosage Control</h2>";
String html_2 = "";
String html_4 = "</div></body></html>";

void connectToWiFi() {
    //Connect to WiFi Network
      Serial.println();
      Serial.println();
      Serial.print("Connecting to WiFi");
      Serial.println("...");
      WiFi.begin(ssid, password);
      int retries = 0;
    while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
      retries++;
      delay(500);
      Serial.print(".");
    }

    server.begin();
    Serial.println("Server started");

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("WiFi connected!"));
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
        Serial.println(F("Setup ready"));
}

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(signal_sensor, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(relay, OUTPUT);
  //pinMode(miseEnMarche, OUTPUT);

  digitalWrite(led_verte, LOW);
  digitalWrite(led_rouge, LOW);
  digitalWrite(signal_sensor, LOW);
  digitalWrite(relay, LOW);
  //digitalWrite(miseEnMarche, HIGH);

  connectToWiFi();
  
}
void loop(){

    // HTTPClient http;
    //     String url = "http://192.168.84.110/";     
           
    //     http.begin(wifiClient, url);

    //      String httpResp = http.getString();

         WiFiClient client = server.available();
         String request = client.readStringUntil('\r');

            if (request.indexOf("check") > 0) {
                defaut();     // detecter l'état du sol 
                traitement(); 
            }
            if ( request.indexOf("on") > 0) {
                defaut();

                if(pourcentage<20){
                  digitalWrite(signal_sensor, HIGH);
                  digitalWrite(relay, HIGH);

                  Serial.println("Arrosage demarrer");    
                }else{
                  Serial.println("Impossible d'arroser car l'humidité est elever");   
                  digitalWrite(relay, LOW); 
                }   

            }
            if (request.indexOf("off") > 0) {
                digitalWrite(signal_sensor, LOW); 
                digitalWrite(relay, LOW);
                
                Serial.println("Arrosage fermer");

               
            }

          
            // client.flush();
 
            // client.print( header );
            // client.print( html_1 );    
            // client.print( html_2 );
            // client.print( html_4);
        
            // delay(5);


  
}


int Conversion(int value){
  int valeurPourcentage = 0;
  valeurPourcentage = map(value, 1023, 0, 0, 100);

  return valeurPourcentage;
}


void defaut(){
      hsol = analogRead(sensorPin);
      pourcentage = Conversion(hsol);   
           
           Serial.println(pourcentage);
  }  


void traitement(){

    if(pourcentage<20){
      digitalWrite(led_rouge, 1);
      delay(500);
      digitalWrite(led_rouge, 0);
      delay(500);    
      digitalWrite(led_rouge, 1);
      delay(500);    
      digitalWrite(led_rouge, 0);
      delay(500);    
      digitalWrite(led_rouge, 1);
      delay(500);
      digitalWrite(led_rouge, 0);
      delay(500);
      digitalWrite(led_rouge, 1);
      delay(500);    
      digitalWrite(led_rouge, 0);
      delay(500);    
      digitalWrite(led_rouge, 1);
      delay(500);
      digitalWrite(led_rouge, 0);
      delay(500); 
    }

    if(pourcentage>20){
      digitalWrite(led_verte, 1);
      delay(500);
      digitalWrite(led_verte, 0);
      delay(500);    
      digitalWrite(led_verte, 1);
      delay(500);    
      digitalWrite(led_verte, 0);
      delay(500);    
      digitalWrite(led_verte, 1);
      delay(500);
      digitalWrite(led_verte, 0);
      delay(500); 
      digitalWrite(led_verte, 1);
      delay(500);    
      digitalWrite(led_verte, 0);
      delay(500);    
      digitalWrite(led_verte, 1);
      delay(500);
      digitalWrite(led_verte, 0);
      delay(500); 
    }
  
  }