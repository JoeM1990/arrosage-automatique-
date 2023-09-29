
#include <ESP8266WiFi.h>

int pourcentage = 0; 
//int miseEnMarche = 6;

int sensorPin = A0; 
int led_verte = 13;
int led_rouge = 13;
int relay = 14;
int signal_sensor =3;

int hsol;

const char* ssid = " ";
const char* password = " ";

WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(signal_sensor, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(miseEnMarche, OUTPUT);

  digitalWrite(led_verte, LOW);
  digitalWrite(led_rouge, LOW);
  digitalWrite(signal_sensor, LOW);
  //digitalWrite(miseEnMarche, HIGH);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi OK");
  
  // demarrage du serveur
  server.begin();
  Serial.println("Server OK");

  // Adresse IP locale attribuee
  Serial.println(WiFi.localIP());


}
void loop(){

  WiFiClient client = server.available();

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if(!client.available()){
    // Ici on check le système pour verifier l'hulidité du sol
      

        if(req.indexOf("/check/1") != -1){   // Si l'utilisateur appui sur le button check system
            defaut();     // detecter l'état du sol 
            traitement();

            Serial.println("Detection etat du sol");
          }

        else if (req.indexOf("/start/1") != -1){   // Boutton  manuel_ON
            digitalWrite(signal_sensor, HIGH);

            Serial.println("Arrosage demarrer");          
          }

        else if(req.indexOf("/start/0") != -1){ // Bouton manuel_OFF
            digitalWrite(signal_sensor, LOW); 
            
            Serial.println("Arrosage fermer");
        }

        else{

          Serial.println("Requete invalide");

          client.stop();
          return;
        }
 } 

}


int Conversion(int value){
  int valeurPourcentage = 0;
  valeurPourcentage = map(value, 1023, 0, 0, 100);

  return valeurPourcentage;
}


void defaut(){
      hsol = analogRead(sensorPin);
      pourcentage = Conversion(hsol);        
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
  
  }
  
