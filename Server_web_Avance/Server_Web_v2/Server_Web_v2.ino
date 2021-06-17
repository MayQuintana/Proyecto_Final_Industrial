#include <WiFi.h>
#include <ESP32Servo.h>

//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------Credenciales de WiFi-----------------------

const char* ssid     = "Martin_Garcia_H*";
const char* password = "M4451072841g4582873H";

//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request

//  variables Auxiliares para store estado output 
String output16State = "off";
String output5State = "off";
String output4State = "off";
String output3State = "off";
String output2State = "off";
String output1State = "off";
String output0State = "off";
String output14State = "off";
String output12State = "off";

// Asignacion de variables de salida GPIO pins
const int output16 = 16; //cuarto 1
const int output5 = 5;   //cuarto 2
const int output4 = 4;
const int output3 = 3;  
const int output2 = 2;//cuarto 3
const int output1 = 1;   //cuarto 4
const int output0 = 0;
const int output14 = 14;
const int output12 = 12;
Servo servo_4;
Servo servo_2;

String estadoSalida = "off";

const int salida = 2;

//------------------------CODIGO HTML------------------------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<meta charset='utf-8' />"
"<link rel=\"icon\" href=\"data:,\">"
"<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;"
"text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
".button2 {background-color: #77878A;}</style>"
"<title>Servidor Web ESP32</title>"
"</head>"
"<body>"
"<center>"
"<h1>Smart System Hose</h1>"
/* Cuartos */
"<p>Cuarto 1 - State " + output16State + "</p>"
if (output16State=="off") {
  "<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>"
} else {
  "<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>"
} 
"<p>Cuarto 2 - State " + output5State + "</p>"
if (output5State=="off") {
"<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>"
} 
"<p>Cuarto 3 - State " + output3State + "</p>"
if (output3State=="off") {
"<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>"
}
"<p>Cuarto 4 - State " + output1State + "</p>"
if (output1State=="off") {
"<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>"
} 
"<p>Cuarto 5 - State " + output0State + "</p>"
if (output0State=="off") {
"<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>"
} 
//motor puerta
"<p>Puerta Abrir/Cerrar - State " + output4State + "</p>"
if (output4State=="off") {
"<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>"
}
//garage
"<p>Puerta Abrir/Cerrar - State " + output2State + "</p>"
if (output2State=="off") {
"<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>"
}
// Ventiladores.
"<p>Ventilacion Cuarto 1 - State " + output14State + "</p>"
if (output14State=="off") {
"<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>"
}
"<p>Ventilacion Cuarto 2 - State " + output12State + "</p>"
if (output12State=="off") {
 "<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>"
} else {
"<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>"
},
"</center>"
"</body>"
"</html>";


//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("");

    pinMode(output16, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  // Apagar salidas
  digitalWrite(output16, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output1, LOW);
  digitalWrite(output0, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output12, LOW);
  
  //motor
  servo_4.attach(4);
  servo_2.attach(2);
  servo_4.write(0);
  servo_2.write(0);
  delay(2000);
  
  pinMode(salida, OUTPUT); 
  digitalWrite(salida, LOW);

  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      //para usar con ip fija
      //IPAddress ip(192,168,1,180); 
      //IPAddress gateway(192,168,1,1); 
      //IPAddress subnet(255,255,255,0); 
      //WiFi.config(ip, gateway, subnet); 
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); // iniciamos el servidor
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
}

//----------------------------LOOP----------------------------------

void loop(){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

  if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del 
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // enciende y apaga el GPIO
            if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16State = "on";
              digitalWrite(output16, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16State = "off";
              digitalWrite(output16, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
              servo_4.write(90);
              delay(1000);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              servo_4.write(0);
              delay(1000);
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output0, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
              servo_2.write(90);
              delay(1000);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              servo_2.write(0);
              delay(1000);
              digitalWrite(output2, LOW);
            } else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            } else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            }
            /* if (header.indexOf("GET /on") >= 0) {
              Serial.println("GPIO on");
              estadoSalida = "on";
              digitalWrite(salida, HIGH);
            } else if (header.indexOf("GET /off") >= 0) {
              Serial.println("GPIO off");
              estadoSalida = "off";
              digitalWrite(salida, LOW);
            }*/
            
            // Muestra la página web
            client.println(pagina);
            
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else { // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
