//// Programa Esteira
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
const char* MQTT_SERVER = "broker.app.wnology.io";
const char* MQTT_ACCESS_KEY = "";
const char* MQTT_ACCESS_SECRET = "";
const char* DEVICE_ID = "";
const char* MQTT_TOPIC = "wnology//state";
const int MQTT_PORT = 1883;
const int PUBLISH_INTERVAL = 300000;

WiFiClient espClient;
PubSubClient client(espClient);

char attributes[200];

//////////////////////////////////////////////////////////////////
int SensorCapacitivo = 35;  // define a porta digital a ser lida
int SensorIndutivo = 32;  // define a porta digital a ser lida
int OpticoBaixo = 33;  // define a porta digital a ser lida
int OpticoMedio = 25;  // define a porta digital a ser lida
int OpticoAlto = 26;  // define a porta digital a ser lida
int Esteira01 = 27;  // define a porta digital a ser lida
int Esteira02 = 14;  // define a porta digital a ser lida
int Esteira03 = 13;  // define a porta digital a ser lida
/////////////////////////////////////////////////////////////////
int Atuador01 = 19;  // define a porta digital como saida
int Atuador02 = 21;  // define a porta digital como saida
int Atuador03A = 04;  // define a porta digital como saida
int Atuador03R = 18;  // define a porta digital como saida
int saidaDigital05 = 17;  // define a porta digital como saida
int saidaDigital06 = 23;  // define a porta digital como saida
int saidaDigital07 = 16;  // define a porta digital como saida
int saidaDigital08 = 22;  // define a porta digital como saida
/////////////////////////////////////////////////////////////////
int ValorSensorCapacitivo ;  // valor da porta digital
int ValorSensorIndutivo;  // valor da porta digital
int ValorOpticoBaixo;  // valor da porta digital
int ValorOpticoMedio;  // valor da porta digital
int ValorOpticoAlto;  // valor da porta digital
int ValorEsteira01;  // valor da porta digital
int ValorEsteira02;  // valor da porta digital
int ValorEsteira03;  // valor da porta digital
/////////////////////////////////////////////////////////////////
int Palta = 0;
int Pmedia = 0;
int Pbaixa = 0;

void setup() {
  Serial.begin(115200);
  call_pub();
  pinMode(SensorCapacitivo, INPUT);  // configura a porta digital como entrada
  pinMode(SensorIndutivo, INPUT);  // configura a porta digital como entrada
  pinMode(OpticoBaixo, INPUT);  // configura a porta digital como entrada
  pinMode(OpticoMedio, INPUT);  // configura a porta digital como entrada
  pinMode(OpticoAlto, INPUT);  // configura a porta digital como entrada
  pinMode(Esteira01, INPUT);  // configura a porta digital como entrada
  pinMode(Esteira02, INPUT);  // configura a porta digital como entrada
  pinMode(Esteira03, INPUT);  // configura a porta digital como entrada
///////////////////////////////////////////////////////////////
  pinMode(Atuador01, OUTPUT);  // configura a porta digital como saida
  pinMode(Atuador02, OUTPUT);  // configura a porta digital como saida
  pinMode(Atuador03A, OUTPUT);  // configura a porta digital como saida
  pinMode(Atuador03R, OUTPUT);  // configura a porta digital como saida
  pinMode(saidaDigital05, OUTPUT);  // configura a porta digital como saida
  pinMode(saidaDigital06, OUTPUT);  // configura a porta digital como saida
  pinMode(saidaDigital07, OUTPUT);  // configura a porta digital como saida
  pinMode(saidaDigital08, OUTPUT);  // configura a porta digital como saida

  digitalWrite(Atuador01, HIGH);  // configura a porta digital como saida
  digitalWrite(Atuador02, HIGH);  // configura a porta digital como saida
  digitalWrite(Atuador03A, HIGH);  // configura a porta digital como saida
  digitalWrite(Atuador03R, HIGH);  // configura a porta digital como saida
  digitalWrite(saidaDigital05, HIGH);  // configura a porta digital como saida
  digitalWrite(saidaDigital06, HIGH);  // configura a porta digital como saida
  digitalWrite(saidaDigital07, HIGH);  // configura a porta digital como saida
  digitalWrite(saidaDigital08, HIGH);  // configura a porta digital como saida

}

void loop() {
  Scan();
  
  if(ValorOpticoBaixo == 1){
    int baixo = 1;
    int medio = 0;
    int alto = 0;
    int sair = 1;
    int timer = 0;
    int pulso = 0;
    while(sair == 1){
      timer++;
      Scan();
      if(ValorOpticoMedio == 1){
        medio = 1;
      }
      if(ValorOpticoAlto == 1){
        alto = 1;
      }

      if(timer >= 40 && baixo == 1 && medio == 0 && alto == 0 && pulso == 0){
        digitalWrite(Atuador01, LOW);
        Pbaixa++;
        pulso = 1;
      }
      if(timer >= 40 && baixo == 1 && medio == 1 && alto == 0 && pulso == 0){
        digitalWrite(Atuador02, LOW);
        Pmedia++;
        pulso = 1;
      }
      if(timer >= 40 && baixo == 1 && medio == 1 && alto == 1 && pulso == 0){
        digitalWrite(Atuador03A, LOW);
        delay(100);
        pulso = 1;
        digitalWrite(Atuador03A, HIGH);
        Palta++;
      }
           
      if (ValorEsteira01 == 1 || ValorEsteira02 == 1 || ValorEsteira03 == 1){
        digitalWrite(Atuador01, HIGH); 
        digitalWrite(Atuador02, HIGH); 
        digitalWrite(Atuador03R, LOW); 
        delay(100);
        digitalWrite(Atuador03R, HIGH); 
        sair = 0;
      }
      delay(25);
    }
    call_pub();    
  }
}
