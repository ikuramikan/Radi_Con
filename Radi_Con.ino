#include<WiFi.h>
#include"Radi_Con.h"

const char ssid[]="your ssid";
const char passwd[]="your password";

WiFiServer server(80);

Radi_con radi_con(19, 17, 4, 14, 27, 12);

void setup()
{
    delay(1000);
    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.print("connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, passwd);

    while(WiFi.status()!=WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}


void loop()
{
    WiFiClient client = server.available();

    if(client)
    {
        Serial.println("new client");
        String currentLine = "";
        while(client.connected())
        {
            if(client.available())
            {
                char c = client.read();
                Serial.write(c);

                if(c=='\n')
                {
                    if(currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        // HTML
                        client.println("<!DOCTYPE html>");
                        client.println("<html>");
                        client.println("<head><meta charset=\"utf-8\" http-equiv=\"refresh\" constnt=0.1></head>");
                        client.println("<body>");
                        client.println("<h1>ESP-WROOM-32</h1><h2>WiFi接続テスト</h2>");
                        client.println("<br>");
                        client.println("<table>");
                        client.println("<tr><form name='acc' method='GET'><input type='submit' name='dc' style='width:150px; height:90px' value='acc'></form></tr><tr><form name='dec' method='GET'><input type='submit' name='dc' style='width:150px; height:90px' value='dec'></form></tr>");
                        client.println("</table>");
                        client.println("<br><br>");
                        client.println("<table>");
                        client.println("<tr><th> </th><th><form name='forward' method='GET'><input type='submit' style='width:150px; height:90px' name='con' value='forward'></form></th><th> </th><th> </th></tr><tr><th><form name='turnleft' method='GET'><input type='submit' style='width:150px; height:90px' name='con' value='turnleft'></form></th><th><form name='brake' method='GET'><input type='submit' name='con' style='width:150px; height:90px' value='brake'></form></th><th><form name='turnright' method='GET'><input type='submit' name='con' style='width:150px; height:90px' value='turnright'></form></th></tr><th> </th><tr><th> </th><th><form name='back' method='GET'><input type='submit' name='con' style='width:150px; height:90px' value='back'></form></th><th> </th><th> </th><th><form name='idle' method='GET'><input type='submit' name='con' style='width:150px; height:90px' value='idle'></form></th></tr>");
                        client.println("</table>");
                        client.println("</body>");
                        client.println("</html>");
                        client.println("");
                        client.println("");

                        break;
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if(c != '\r')
                {
                    currentLine += c;
                }

                if(currentLine.endsWith("GET /?con=forward"))
                {
                    radi_con.forward();
                }
                if(currentLine.endsWith("GET /?con=back"))
                {
                    radi_con.back();
                }
                if(currentLine.endsWith("GET /?con=brake"))
                {
                    radi_con.brake();
                }
                if(currentLine.endsWith("GET /?con=idle"))
                {
                    radi_con.idle();
                }
                if(currentLine.endsWith("GET /?con=turnleft"))
                {
                    radi_con.turn_left();
                }
                if(currentLine.endsWith("GET /?con=turnright"))
                {
                    radi_con.turn_right();
                }

                if(currentLine.endsWith("GET /?dc=acc"))
                {
                    radi_con.accelerate();
                }
                if(currentLine.endsWith("GET /?con=dec"))
                {
                    radi_con.decelerate();
                }
            }
        }
    }
}