#include "webserver.h"
#include "FS.h"
#include "SPIFFS.h"
#include <WebServer.h>
#include <ESPmDNS.h>
#include <cstring>
#include "screen.h"
#include "clock.h"

#define FORMAT_SPIFFS_IF_FAILED false

WebServer server;

int
request_is_valid();

int
init_storage();

void
init_routes();

String
get_value(const String);

int
initialize_server(const char *address, const uint16_t port)
{
  if(init_storage()==-1)
      return SRV_STOR_FAIL;
  init_routes();
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

int
request_is_valid()
{
  if(server.uri().length()>256)
  {
    server.send(414, "text/plain", "Request too long");
    return 0;
  }
  if(server.args() > 16)
  {
    server.send(403, "text/plain", "Too many arguments");
    return 0;
  }
  if(server.clientContentLength() > 16384)
  {
    server.send(413, "text/plain", "Request too large");
    return 0;
  }
  return 1;
}

int
init_storage()
{
  if(!SPIFFS.begin(false))
    if(!SPIFFS.begin(true))
      return -1;
  return 0;
}

String
get_value(const String param, const String default_val)
{
  for(uint8_t i=0; i<server.args(); i++)
  {
    if(server.argName(i) == param)
      return server.arg(i);
  }
  return default_val;
}

#define TEXT_MAX 512
#define URL_MAX 16
#define PARAM_MAX 32

void
handle_not_found2() // would have worked better if the underlaying server returned c-strings instead of std::string
{
  if(!request_is_valid())
    return;
  char message[TEXT_MAX];
  memset(message, 0, sizeof(message));
  sprintf(message, "File not found\n\nURI: %.16s\nMethod: %s\nArguments: %d\n",
    server.uri().c_str(), (server.method()==HTTP_GET)? "GET":"POST", server.args());

  char temp[PARAM_MAX];
  for(uint8_t i=0; i<server.args(); i++)
  {
    memset(temp, 0, sizeof(temp));
    sprintf(temp, "\t%.8s: %.16s\n",
      server.argName(i).c_str(), server.arg(i).c_str());
    if(strlen(temp) + strlen(message) >= TEXT_MAX) //prevent overflow
      break;
    strcat(message, temp);
  }
  server.send(404, "text/plain", message);
}

void
handle_not_found()
{
  if(!request_is_valid())
    return;
  String message = "File Not Found\n";
  message += "\nURI: " + server.uri();
  message += "\nMethod: " + (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: " + server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++) {
    message += "\t" + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void
handle_get_w()
{
  if(!request_is_valid())
    return;
  if(server.method() == HTTP_POST)
    return handle_not_found();
  char res[8];
  sprintf(res, "%d", get_width());
  server.send(200, "text/plain", res);
}

void
handle_get_h()
{
  if(!request_is_valid())
    return;
  if(server.method() == HTTP_POST)
    return handle_not_found();
  char res[8];
  sprintf(res, "%d", get_height());
  server.send(200, "text/plain", res);
}

void
handle_show_clock()
{
  if(!request_is_valid())
    return;
  if(server.method() == HTTP_GET)
    return handle_not_found();
 
  uint8_t alignment;
  const String halign = get_value("halign", "center");
  if(halign == "left")
    alignment = ORIENT_LEFT;
  else if(halign == "right")
    alignment = ORIENT_RIGHT;
  else if(halign == "center")
    alignment = ORIENT_CENTER_H;

  const String valign = get_value("valign", "center");
  if(valign == "top")
    alignment = alignment | ORIENT_TOP;
  else if(valign == "bottom")
    alignment = alignment | ORIENT_BOTTOM;
  else if(valign == "center")
    alignment = alignment | ORIENT_CENTER_V;

  const String fmt = get_value("format", "");
  char timenow[64] = {0};
  get_time(timenow, sizeof(timenow), fmt.c_str());
  screen_clear();
  screen_print_aligned(timenow, alignment);
  server.sendHeader("Location", "/", true); // redirect
  server.send(302, "text/plain", "");
}

void
handle_show_text()
{
  if(!request_is_valid())
    return;
  if(server.method() == HTTP_GET)
    return handle_not_found();
 
  uint8_t alignment;
  const String halign = get_value("halign", "center");
  if(halign == "left")
    alignment = ORIENT_LEFT;
  else if(halign == "right")
    alignment = ORIENT_RIGHT;
  else if(halign == "center")
    alignment = ORIENT_CENTER_H;

  const String valign = get_value("valign", "center");
  if(valign == "top")
    alignment = alignment | ORIENT_TOP;
  else if(valign == "bottom")
    alignment = alignment | ORIENT_BOTTOM;
  else if(valign == "center")
    alignment = alignment | ORIENT_CENTER_V;
  
  const String val = get_value("text", "");
  screen_clear();
  screen_print_aligned(val, alignment);
  server.sendHeader("Location", "/", true); // redirect
  server.send(302, "text/plain", "");
}

void
init_routes()
{
  server.serveStatic("/index.html", SPIFFS, "/index.html");
  server.serveStatic("/", SPIFFS, "/index.html");
  server.serveStatic("/favicon.png", SPIFFS, "/favicon.png");
  server.on("/show", handle_show_text);
  server.on("/clock", handle_show_clock);
  server.on("/getwidth", handle_get_w);
  server.on("/getheight", handle_get_h);
  server.onNotFound(handle_not_found2);
}
