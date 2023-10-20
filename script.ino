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

    IPAddress ip(192, 168, 56, 110);
    IPAddress dns(192,168,1,254);
    IPAddress gateway(192,168,1,254);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.config(ip);

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

         WiFiClient client = server.available();
         String request = client.readStringUntil('\r');

        HTTPClient https;
        String url = "https://www.project.monkila-tech.com/script.php";     
           
        https.begin(client, url);
        https.addHeader("Content-Type", "application/x-www-form-urlencoded");

        //String request = http.readStringUntil('\r');

            if (request.indexOf("check") > 0) {
                defaut();     // detecter l'état du sol 
                traitement(); 

                  HTTPClient https;
                  String url = "https://www.project.monkila-tech.com/";     
                    
                  https.begin(client, url);
                  https.addHeader("Content-Type", "application/x-www-form-urlencoded");

                  String httpRequestData = "value="+pourcentage;
                  int httpResponseCode = https.POST(httpRequestData);

                  if(httpResponseCode>0){
                    Serial.println("Success"); 
                  }

                  https.end();

            }
            if ( request.indexOf("on") > 0) {
                defaut();

                if(pourcentage<20){
                  digitalWrite(signal_sensor, HIGH);
                  digitalWrite(relay, HIGH);

                  HTTPClient https;
                  String url = "https://www.project.monkila-tech.com/script.php";     
                    
                  https.begin(client, url);
                  https.addHeader("Content-Type", "application/x-www-form-urlencoded");

                  //double qt = 0,06*5;

                  String httpRequestData = "motif=arrosage&quantite=20";
                  int httpResponseCode = https.POST(httpRequestData);

                  if(httpResponseCode>0){
                    Serial.println("Success"); 
                  }

                  String url2 = "http://192.168.56.110/parms1=Arrosage demarrer";     
                  https.begin(client, url2);
                  https.addHeader("Content-Type", "application/x-www-form-urlencoded");


                  https.end();

                  Serial.println("Arrosage demarrer");    
                }else{
                  Serial.println("Impossible d'arroser car l'humidité est elever");  

                  HTTPClient https;

                  String url3 = "http://192.168.56.110/parms1=Impossible d'arroser car l'humidité est elever";     
                  https.begin(client, url3);
                  https.addHeader("Content-Type", "application/x-www-form-urlencoded");


                  digitalWrite(relay, LOW); 
                }   

            }
            if (request.indexOf("off") > 0) {
                digitalWrite(signal_sensor, LOW); 
                digitalWrite(relay, LOW);

                HTTPClient https;

                 String url4 = "http://192.168.56.110/parms1=Arrosage fermer";     
                  https.begin(client, url4);
                  https.addHeader("Content-Type", "application/x-www-form-urlencoded");
                
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