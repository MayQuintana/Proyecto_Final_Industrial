#include <WiFi.h>
#include <ESP32Servo.h>

/****** Retardo***********/
int periodo = 10;
int periodo2=2000;
int periodo3=1000;
int periodo4=500;
unsigned long tiempo = 0;
// Ponemos nuestro wifi para probar 
const char* ssid     = /*"INFINITUM502D04" */"Martin_Garcia_H*";
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
String output21State = "off";
String output15State = "off";
String output14State = "off";
String output12State = "off";

// Assigna  variables de entrada a los GPIO pins
const int output16 = 16;
const int output5 = 5; 
const int output4 = 4;
const int output3 = 3;  
const int output2 = 2;
const int output21 = 21; 
const int output15 = 15;
const int output14 = 14;
const int output12 = 12;
Servo servo_4;
Servo servo_2;

IPAddress ip(192, 168, 1, 64);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  // Inicializar variables de salida 
  pinMode(output16, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output21, OUTPUT);
  pinMode(output15, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  // Apagar salidas
  digitalWrite(output16, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output21, LOW);
  digitalWrite(output15, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output12, LOW);
  
  //motor
  servo_4.attach(4);
  servo_2.attach(2);
  servo_4.write(0);
  servo_2.write(0);
 // delay(2000);
  /***/
  while (millis() < tiempo + periodo2){    
/* ESPERA */
}
// Conetcta a  Wi-Fi con el SSID y contrasena que pusimos de ejemplo 
  while (millis() < tiempo + periodo){
/* ESPERA */
}
  Serial.println();
  WiFi.config(ip, gateway, subnet);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {

  while (millis() < tiempo + periodo4){
/* ESPERA */
}
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

  tiempo=millis(); 
  WiFiClient client = server.available();   // Escucha a clientes entrantes 

  if (client) {                             // Si queremos que un nuevo cliente se conecte,
    Serial.println("New Client.");          // imprimir un mensaje en el puerto serial
    String currentLine = "";                // hacer una cadena para contener los datos entrantes del cliente
    while (client.connected()) {            // Bucle mientras la cliente está conectada
      if (client.available()) {             // Si hay bytes para leer de la cliente,
        char c = client.read();             // leer un byte, despues
        Serial.write(c);                    //imprímalo en el monitor de serie
        header += c;
        if (c == '\n') {                   // si el byte es un carácter de nueva línea
          // si la línea actual está en blanco, tiene dos caracteres de nueva línea seguidos.
          // ese es el final de la solicitud HTTP del cliente, así que envíe una respuesta:
          if (currentLine.length() == 0) {          
// Los encabezados HTTP siempre comienzan con un código de respuesta (por ejemplo, HTTP / 1.1 200 OK)
            // y un tipo de contenido para que el cliente sepa lo que viene, luego una línea en blanco:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // prende el GPIOs on and off luz de los cuartos
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
              while (millis() < tiempo + periodo3){
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              servo_4.write(0);
              while (millis() < tiempo + periodo3){
            }
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            } else if (header.indexOf("GET /21/on") >= 0) {
              Serial.println("GPIO 21 on");
              output21State = "on";
              digitalWrite(output21, HIGH);
            } else if (header.indexOf("GET /21/off") >= 0) {
              Serial.println("GPIO 21 off");
              output21State = "off";
              digitalWrite(output21, LOW);
            } else if (header.indexOf("GET /15/on") >= 0) {
              Serial.println("GPIO 15 on");
              output15State = "on";
              digitalWrite(output15, HIGH);
            } else if (header.indexOf("GET /15/off") >= 0) {
              Serial.println("GPIO 15 off");
              output15State = "off";
              digitalWrite(output15, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
              servo_2.write(90);
              while (millis() < tiempo + periodo3){
           }
           } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              servo_2.write(0);
              while (millis() < tiempo + periodo3){
            }
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
               
           // Muestra el estado actual y los botones ON / OFF para GPIO 4 
            client.println("<p>Cuarto 3 - State " + output3State + "</p>");
            // Si output4State está desactivado, muestra el botón ON      
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Cuarto 4 - State " + output21State + "</p>");
            if (output21State=="off") {
              client.println("<p><a href=\"/21/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/21/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("<p>Cuarto 5 - State " + output15State + "</p>");
            if (output15State=="off") {
              client.println("<p><a href=\"/15/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/15/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            //motor puerta
            client.println("<p>Puerta Abrir/Cerrar - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //garage
            client.println("<p>Puerta Abrir/Cerrar - State " + output2State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            // Ventiladores.
            client.println("<p>Ventilacion Cuarto 1 - State " + output14State + "</p>");
            if (output14State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Ventilacion Cuarto 2 - State " + output12State + "</p>");
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("</body></html>");
            
            // La respuesta HTTP termina con otra línea en blanco
            client.println();
            // Salir del bucle while
            break;
          } else { // si tienes una nueva línea, borra currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si tiene algo más que un carácter de retorno de carro,
          currentLine += c;      // agregarlo al final de currentLine
        }
      }
    }
            
    // Limpia el encabezado 
    header = "";
    // Para la conexion 
    client.stop();
    Serial.println("Cliente disconnected.");
    Serial.println("");
  }
}
