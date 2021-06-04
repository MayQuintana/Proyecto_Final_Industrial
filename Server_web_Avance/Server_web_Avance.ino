#include <ESP8266WiFi.h>
#include <Servo.h>

// Ponemos nuestro wifi para probar 
const char* ssid     = /*"INFINITUM502D04" */"Martin_Garcia_H";
const char* password = /*"23D581E62F" */"M4451072841g4582873H";

// Cambiamos el servidor web al puerto 80
WiFiServer server(80);

//Variable que guaradara la dirreccion  HTTP 
String header;

// Auxiliares para guardar las entradas que tiene 
String output16State = "off";
String output5State = "off";
String output4State = "off";
String output3State = "off";
String output2State = "off";
String output1State = "off";
String output0State = "off";
String output14State = "off";
String output12State = "off";

// Assigna  variables de entrada a los GPIO pins
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

IPAddress ip(192, 168, 1, 64);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  // Initialize las variables 
  pinMode(output16, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  // Ponemos los outputs a modo bajo
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

  // Conetcta a  Wi-Fi con el SSID and contrasena que pusimos de ejemplo 
  delay(10);
  Serial.println();
  WiFi.config(ip, gateway, subnet);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Imprime el IP local y empieza el servidor web
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // busca a clientes que se vayan uniendo 

            }
            
            // Despliega pagina web 
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS  apagar/prende  botones 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            //se modifico y se agrego dos botones mas.
           // client.println(".button2 {background-color: #77878A;}");
           // client.println(".button2 {background-color: #77878A;}</style></head>");
            
            
            // El encabezado de la pagina 
            client.println("<body><h1>Smart Home System</h1>");

            client.println("<p>Cuarto 1 - State " + output16State + "</p>");
            if (output16State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            // Mustrra el estado en el que se encuentra y Prende y Apaga botons para GPIO 5  
            client.println("<p>Cuarto 2 - State " + output5State + "</p>");
            // Si la estado t5State esta apagado, muestre opcion de Prender       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               //aqui nos quedanos 
            
    // Limpia el encabezado 
    header = "";
    // Para la conexion 
    client.stop();
    Serial.println("Cliente disconnected.");
    Serial.println("");
  }
}
