#include "webserver.h"
#include "FS.h"
#include "SPIFFS.h"
#include <WebServer.h>
#include <ESPmDNS.h>
#include <cstring>

#define FORMAT_SPIFFS_IF_FAILED false

WebServer server;

void
handle_root();

void
handle_not_found();

int
initialize_server(const char *address, const uint16_t port)
{
  if(!SPIFFS.begin(false))
    if(!SPIFFS.begin(true))
      return SRV_STOR_FAIL;
  server.serveStatic("/index.html", SPIFFS, "/index.html");
  server.serveStatic("/favicon.png", SPIFFS, "/favicon.png");
  server.onNotFound(handle_not_found);
  server.begin(port);
  if(!MDNS.begin(address))
    return SRV_MDNS_FAIL;
  return SRV_OK;
}

void
wait_clients()
{
  server.handleClient();
}

void
handle_not_found2() //currently bugged, crashes the board into reset
{
  char message[16384];
  char temp[512];
  sprintf(message,
    "File not found\n\nURI: %s\nMethod: %s\nArguments: %d\n",
    server.uri().c_str(), (server.method()==HTTP_GET)? "GET":"POST", server.args());
  for(uint8_t i=0; i<server.args(); i++)
  {
    memset(temp, 0, sizeof(temp));
    sprintf(temp, "\t%s: %s\n", server.argName(i).c_str(), server.arg(i).c_str());
    strcat(message, temp);
  }
  server.send(404, "text/plain", message);
}

void
handle_not_found()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
