#include<ESP8266WiFi.h>
#include<Servo.h>   //servo
Servo kalu;         //servo



int port = 4200; //port Number
WiFiServer server(port);

//Server connect to WiFi Network
//Enter your wifi SSID

const char *ssid = "Dialog 4G 406";
//Enter your wifi Password
const char *password = "53F900c5";

String string = "";
char tst;

//==============================
//                    Power on setup
//==============================

void setup() {
  kalu.attach(4);

  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi


  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }


  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}

void loop()
{

  WiFiClient client = server.available();

  if (client) {
    if (client.connected())
    {
    }

    while (client.connected()) {
      while (client.available() > 0) {
        // read data from the connected client
        char a = client.read();
        tst = a;
        String b = String(a);
        string = string + b;
        //Serial.write(a);
        delay(10); //wait to read data
      }
      //Send Data to connected client(No need this for now)
      while (Serial.available() > 0)
      {
        client.write(Serial.read());
      }

    }
    client.stop();
    controlDevice(tst);
    string = "";
  }

}

void controlDevice(char s) {

  

  Serial.print("Respons --> ");
  Serial.println(s);

  switch (s)
  {
    case 'K':
      kalu.write(0);
      break;
    case 'L':
      kalu.write(180);

      break;


    default:
      break;
  }   

}
