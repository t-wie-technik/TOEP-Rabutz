#include <WiFi101.h>;
#include "string.h";


#define IS_ACCESS_POINT 0 // 0 or 1
#if IS_ACCESS_POINT == 1
  char ssid[] = "rabutz-test";  // AP name
  char pass[] = "";             // no AP password (open AP)
  //char pass[] = "1234567890";   // AP password
#else
  char ssid[] = "RabutzRobotics"; // your network SSID (name)
  char pass[] = "31073851";  // your network password
  //char pass[] = "";  // your network is open
#endif
//#define WAIT_FOR_SERIAL_CONNECTION // wait for USB serial connection
#define MAX_PACKET_LEN 1400 // max ethernet frame payload
#define CT_NONE  0
#define CT_PLAIN 1
#define CT_HTML  2

WiFiServer webserver(80); // webserver at port 80
char *httpRequestURL; // HTTP request from client
unsigned long lastReq;
const String index_html_text[] = 
    {"<!DOCTYPE html>",
    "<html>",
    "<head>",
    "<meta charset='utf-8'>",
    "<title>Bahnhof Siedlung</title>",
    "</head>",
    "<body>",
    "<a>Das ist die Steuereinheit des Bahnhof Siedlung<a/><br/>",
    "<a href='/debug'> Start</a><br/>",
    "<a href='/toOtherDebug'>A-A test</a>",
    "</body>",
    "</html>"};

void Commands(String first,String second, String third, String forth, String fith);
/*
//IPAddress server(192,168,1,189);
void Commands(String index, String value){
    if (index == "R"){
      if (value == "1") digitalWrite(15, HIGH);
      else digitalWrite(15, LOW);
    }
    }else if (index == "test"){
      WiFiClient c;
      c.connect(server, 80);
      c.println("GET /J2/1 HTTP/1.0");
      c.println();
    }
}
*/

void SendPlain(String data, IPAddress target){
  WiFiClient c;
    Serial.println(data);
  if(c.connect(target, 80)){
      Serial.println("during send");
    c.println(data);
      Serial.println("success send");
  }else{Serial.println("nosend");}
  Serial.println("after send");
}

void Kill(){
  
}

bool startWifi(char *ssid, char *password, bool isAP)
{
  int status;
  /*this is not used since we run all arduinos as clients
  if(isAP) 
  {
    // create AP
    Serial.print("Create an open Access Point: ");
    Serial.println(ssid);
    if(strlen(password))
    {
      status = WiFi.beginAP(ssid, password); // WPA (FW >=19.5.0)
    }
    else
    {
      status = WiFi.beginAP(ssid);
    }
    if(status != WL_AP_LISTENING) 
    {
      Serial.println("Creating access point failed");
      return false; // return error
    }
  }
  else
  {*/
    // connect to WPA/WPA2 network
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    if(status != WL_CONNECTED)
    {
      Serial.println("Connecting failed");
      return false; // return error
    }
  //}
  return true;
}

void printWifiStatus() 
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void httpSendHeader(WiFiClient &client, int content_type)
{
  const char header_none_data[]  = "HTTP/1.0 200 OK\n\n";
  const char header_plain_data[] = "HTTP/1.0 200 OK\nContent-type: text/plain\n\n";
  const char header_html_data[]  = "HTTP/1.0 200 OK\nContent-type: text/html\n\n";

  if(content_type == CT_PLAIN)
    client.write(header_plain_data, sizeof(header_plain_data)-1);
  else if(content_type == CT_HTML)
    client.write(header_html_data, sizeof(header_html_data)-1);
  else
    client.write(header_none_data, sizeof(header_none_data)-1);
}

void httpSendData(WiFiClient &client, const char *data, int len)
{
  while(len > 0)
  {
    int sendlen = len;
    if(len > MAX_PACKET_LEN)
      sendlen = MAX_PACKET_LEN;
  
    client.write(data, sendlen);
    data += sendlen;
    len -= sendlen;
  }
}

bool httpSplitRequest(char *httpRequest, size_t len)
{
  char *reqpart[2];

  if(len >= 3)
  {
    reqpart[0] = strtok(httpRequest, " \t\n");
    if(strncmp(reqpart[0], "GET\0", 4) == 0)
    {
      httpRequestURL = strtok(NULL, " \t"); // url
      //if(!strncmp(httpRequestURL, "/\0", 2)) // rename empty url to index.html
      //  httpRequestURL = "/index.html";
  
      reqpart[1] = strtok (NULL, " \t\n");
      if(!strncmp(reqpart[1], "HTTP/1.0", 8) || \
         !strncmp(reqpart[1], "HTTP/1.1", 8))
      {
        //Serial.println(reqpart[0]);
        //Serial.println(reqpart[1]);
        //Serial.println(httpRequestURL);
        return true;      
      }
    }
  }

  // wrong request
  return false;
}

String httpGetResource(int nr)
{
  String resource = "";
  char *pnt = httpRequestURL;

  if(*pnt == '/') // URL must start with '/'
  {
    while(*pnt)
    {
      if(*pnt++ == '/')
      {
        if(nr-- <= 0)
        {
          while(*pnt != '\0' && *pnt != '/')
          {
            resource += *pnt++;
          }
          break;
        }
      }
    }
  }

  return resource;
}

void SetupWiFi() {
  // wait for WiFi connection   
  while(!startWifi(ssid, pass, IS_ACCESS_POINT))
  {
    delay(5000); // wait 5 seconds and retry
  } 
  // start webserver
  webserver.begin();
  // you're connected now, so print out the status
  printWifiStatus();
}

void SendRequestToOther(String request, IPAddress target){
  String send_final = "GET ";// /NoReply";
  send_final = send_final + request;
  send_final = send_final + " HTTP/1.1";

  SendPlain(send_final, target);
}

void UpdateWiFiHandler() {

  if (millis() - lastReq > 20000){
    Kill();
  }
  
  // put your main code here, to run repeatedly:
  WiFiClient client = webserver.available();
  if(client) {
    // a http request ends with a blank line
    boolean currentLineIsBlank = true;    
    char httpRequest[1024];
    size_t httpRequestLen = 0;
    while(client.connected()) 
    {
      if(client.available()) 
      {
        char c = client.read();
        if(httpRequestLen < (sizeof(httpRequest)-1))
        {
          httpRequest[httpRequestLen++] = c;
          httpRequest[httpRequestLen] = '\0';
        }
        if(c == '\n' && currentLineIsBlank) 
        {
          //Serial.println(httpRequest);
          if (httpSplitRequest(httpRequest, httpRequestLen)) {
            lastReq = millis();

            int id = 0;

            if(httpGetResource(id) == "NoReply"){
              id = 1;
            }

            Commands(httpGetResource(id),httpGetResource(id + 1),httpGetResource(id + 2),httpGetResource(id + 3),httpGetResource(id + 4));

            int i = 0;
            if(id == 1){
              
            }else{
             httpSendHeader(client, CT_HTML);
             while(index_html_text[i] != "</html>")
             {
              client.println(index_html_text[i]);
              i++;
              //httpSendData(client, index_html_text, sizeof(index_html_text)-1); 
             }
            }
            break;
          }
        }
      }
    }
    // close the connection
    client.stop();
  }
}
