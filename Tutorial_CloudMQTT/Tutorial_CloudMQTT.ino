
#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
//Define a pinagem do ESP8266

#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1

 

//-----------------------------------------wifi-----------------------------------------
const char* ssid = "Valhalla"; //Aqui o nome da sua rede local wi fi
const char* password =  "Lokiandthor"; // Aqui a senha da sua rede local wi fi

//-----------------------------------------api.cloudmqtt-----------------------------------------
const char* mqttServer = "m13.cloudmqtt.com"; // Aqui o endereço do seu servidor fornecido pelo site 
const int mqttPort = 14919; // Aqui mude para sua porta fornecida pelo site
const char* mqttUser = "ystaukxs"; //  Aqui o nome de usuario fornecido pelo site
const char* mqttPassword = "JFAKokLHQ0IV"; //  Aqui sua senha fornecida pelo site
char EstadoSaida = '0';  
WiFiClient espClient;
PubSubClient client(espClient);


void mqtt_callback(char* topic, byte* payload, unsigned int length);


void setup() {

    pinMode(D1, OUTPUT);
    digitalWrite(D1, LOW); 
    pinMode(D2, OUTPUT);
    digitalWrite(D2, LOW);  
    pinMode(D3, OUTPUT);
    digitalWrite(D3, LOW); 
    pinMode(D4, OUTPUT);
    digitalWrite(D4, LOW);
    pinMode(D5, OUTPUT);
    digitalWrite(D5, LOW); 
    pinMode(D6, OUTPUT);
    digitalWrite(D6, LOW); 
    pinMode(D7, OUTPUT);
    digitalWrite(D7, LOW); 
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
    pinMode(D8, OUTPUT);
    digitalWrite(D8, LOW); 
 
  Serial.begin(115200);
  wifi();
  cloudmqtt();
  //Manda mensagem
  client.publish("liga","desliga");
  //topico que sera usado pelo nodeMCU
  client.subscribe("LED");
 
}

 void loop() {
  client.loop();
  reconectarWifi();
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);

       String msg;
    
 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
  

        
    //toma ação dependendo da string recebida:
    //verifica se deve colocar nivel alto de tensão na saída.
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
 
 
    //verifica se deve colocar nivel alto de tensão na saída se enviar L e digito, ou nivel baixo se enviar D e digito no topíco LED

    
    

       if (msg.equals("L1"))
    {
        digitalWrite(D1, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D1"))
    {
        digitalWrite(D1, LOW);
        EstadoSaida = '1';
    }
         if (msg.equals("L2"))
    {
        digitalWrite(D2, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D2"))
    {
        digitalWrite(D2, LOW);
        EstadoSaida = '1';
    }

        if (msg.equals("L3"))
    {
        digitalWrite(D3, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D3"))
    {
        digitalWrite(D3, LOW);
        EstadoSaida = '1';
    }

        if (msg.equals("L4"))
    {
        digitalWrite(D4, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D4"))
    {
        digitalWrite(D4, LOW);
        EstadoSaida = '1';
    }

        if (msg.equals("L5"))
    {
        digitalWrite(D5, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D5"))
    {
        digitalWrite(D5, LOW);
        EstadoSaida = '1';
    }
        if (msg.equals("L6"))
    {
        digitalWrite(D6, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D6"))
    {
        digitalWrite(D6, LOW);
        EstadoSaida = '1';
    }
          if (msg.equals("L7"))
    {
        digitalWrite(D7, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D7"))
    {
        digitalWrite(D7, LOW);
        EstadoSaida = '1';
    }

     if (msg.equals("L8"))
    {
        digitalWrite(D0, HIGH);
        EstadoSaida = '0';
    }
    if (msg.equals("D8"))
    {
        digitalWrite(D0, LOW);
        EstadoSaida = '1';
  
   }

        // Liga todos os leds se enviar LT no topico LED
        
        if (msg.equals("LT"))
    {
        digitalWrite(D0,HIGH);
        digitalWrite(D1,HIGH);
        digitalWrite(D2,HIGH);
        digitalWrite(D3,HIGH);
        digitalWrite(D4,HIGH);
        digitalWrite(D5,HIGH);
        digitalWrite(D6,HIGH);
        digitalWrite(D7,HIGH);
        digitalWrite(D8,HIGH);

    }
        // Desliga todos os leds se enviar DT no topico LED

        if (msg.equals("DT"))
    {
        digitalWrite(D0,LOW);
        digitalWrite(D1,LOW);
        digitalWrite(D2,LOW);
        digitalWrite(D3,LOW);
        digitalWrite(D4,LOW);
        digitalWrite(D5,LOW);
        digitalWrite(D6,LOW);
        digitalWrite(D7,LOW);
        digitalWrite(D8,LOW);
        delay(1000);

       }
     }
   
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 


void wifi(){
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando com o WiFi...");
  }
  Serial.print("Conectado com o ");
  Serial.println(ssid);
}

void reconectarWifi(){
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão com wifi perdida");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Reconectando a o WiFi...");
    }
    Serial.print("Reconectando a o ");
    Serial.println(ssid);
    cloudmqtt();
  }

}
void cloudmqtt(){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Conectando com o cloudmqtt...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("Conectado a o cloudmqtt");  
    } 
    else {
      Serial.println("Erro");
      delay(2000);
 
    }
  }
}
  
