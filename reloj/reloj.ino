// Librerias para tiempo y WiFi
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>

// Librerias para pantalla OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Librerias para sensor BME680
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SCREEN_WIDTH 128 // largo de la pantalla OLED, en pixeles
#define SCREEN_HEIGHT 64 // alto de la pantalla OLED, en pixeles

// pins usados para BME680
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5

// pin usado para el buzzer piezo
const int TONE_OUTPUT_PIN = 2;

// El ESP32 tiene 16 canales que pueden generar 16 ondas diferentes
// Canal para el tono
const int TONE_PWM_CHANNEL = 0; 

#define SEALEVELPRESSURE_HPA (1013.25)

// Declaracion para una pantalla SSD1306 conectada a traves de I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_BME680 bme(BME_CS); // hardware para conexion SPI

#define BUTTON_PIN 4 // Boton conectado al GPIO4
// Variables a cambiar para boton
int lastState = HIGH; // Estado previo del boton
int currentState;     // Estado actual del boton

// Remplazar con las credenciales de tu WiFi
const char* ssid     = "iPhone de Miguel";
const char* password = "narizon237";

// Definir el cliente NTP para obtener el tiempo
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables para guardar la fecha y el tiempo
String formattedDate;
String dayStamp;
String timeStamp;

// Variables predefinidas para los valores de los sensores
String temperature = "30.02";
String pressure = "797.06";
String humidity = "40";
String gas = "105.94";
String height = "1980.11";
String button = "LOW";
String alert = "";

// Codigo de la pagina web
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Datos de ESP32</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="3" >
  </head><body>
  <h2>Datos de la ESP32</h2> 
  <h3>Temperatura: %TEMPERATURE% &deg;C</h3>
  <h3>Presion: %PRESSURE% hPa</h3>
  <h3>Humedad: %HUMIDITY% &percnt;</h3>
  <h3>Gas: %GAS% KOhms</h3>
  <h3>Altitud: %ALTITUDE% m</h3>
  <h3>Estado de boton: %BUTTON%</h3>
  <h3>%ALERT%</h3>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

AsyncWebServer server(80);

// Remplaza los valores predeterminados
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return temperature;
  }
  else if(var == "PRESSURE"){
    return pressure;
  }
  else if(var == "HUMIDITY"){
    return humidity;
  }
  else if(var == "GAS"){
    return gas;
  }
  else if(var == "ALTITUDE"){
    return height;
  }
  else if(var == "BUTTON"){
    return button;
  }
  else if(var == "ALERT"){
    return alert;
  }
  return String();
}

void setup() {
  // Iniciar el monitor serial
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("Conectandose a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Imprimir la IP para iniciar servidor
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Iniciando un cliente NTP para obtener el tiempo
  timeClient.begin();
  // Definir diferencia de tiempo en segundos para adaptar a zona horaria
  timeClient.setTimeOffset(-18000);

  // Iniciar el boton como una entrada pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!bme.begin()) {
    Serial.println(F("No se encontro un sensor BME680 valido, ¡Checa el cableado!"));
    while (1);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Direccion 0x3D para 128x64
    Serial.println(F("SSD1306 ubicacion alocada fallo"));
    for(;;);
  }
  delay(1000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 3);
  // Mostrar texto estatico
  display.println(F("Iniciando..."));
  display.display();

  // Definir un oversampling e iniciacion de filtros
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C para 150 ms

  // Enviar pagina web al cliente
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.onNotFound(notFound);
  server.begin();
}
void loop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Datos formateados
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);

  // Extraer la fecha
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("FECHA: ");
  Serial.println(dayStamp);
  // Extraer el tiempo
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-4);
  Serial.print("HORA: ");
  Serial.println(timeStamp);

  // Leer el estado del switch/boton:
  currentState = digitalRead(BUTTON_PIN);
  if (lastState == LOW && currentState == HIGH) {
    if (button == "HIGH") {
      button = "LOW";
      Serial.println("El estado del boton ha cambiado de HIGH a LOW");
    } else {
      button = "HIGH";
      Serial.println("El estado del boton ha cambiado de LOW a HIGH");
    }
  }
  // Guardar el ultimo estado del boton
  lastState = currentState;

  // Indicar al sensor BME680 que inicie mediciones
    unsigned long endTime = bme.beginReading();
    if (endTime == 0) {
      Serial.println(F("Fallo al comenzar a leer :("));
      return;
  }

  delay(50); // Esto representa trabajo paralelo

  if (!bme.endReading()) {
    Serial.println(F("Fallo al completar lectura :("));
    return;
  }

  // Mostrar datos en la pantalla
  display.clearDisplay();
  display.setCursor(0, 3);

  display.print(dayStamp);
  display.print("   ");
  display.println(timeStamp);
  
  display.setCursor(0,16);
  display.print(F("Temperatura: "));
  display.print(bme.temperature);
  display.println(F("*C"));
  display.print(F("Presion: "));
  display.print(bme.pressure / 100.0);
  display.println(F("hPa"));
  display.print(F("Humedad: "));
  display.print(bme.humidity);
  display.println(F("%"));
  display.print(F("Gas: "));
  display.print(bme.gas_resistance / 1000.0);
  display.println(F(" KOhms"));
  display.print(F("Altitud: "));
  display.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  display.println(F("m"));
  display.display();

  Serial.print(F("Temperatura: "));
  Serial.print(bme.temperature);
  Serial.println(F("*C"));
  Serial.print(F("Presion: "));
  Serial.print(bme.pressure / 100.0);
  Serial.println(F("hPa"));
  Serial.print(F("Humedad: "));
  Serial.print(bme.humidity);
  Serial.println(F("%"));
  Serial.print(F("Gas: "));
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(F(" KOhms"));
  Serial.print(F("Altitud: "));
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(F("m"));

  temperature = String(bme.temperature);
  pressure = String(bme.pressure / 100.0);
  humidity = String(bme.humidity);
  gas = String(bme.gas_resistance / 1000.0);
  height = String(bme.readAltitude(SEALEVELPRESSURE_HPA));

  // Sonar el piezo si la temperatura excede 38*C
  if (bme.temperature >= 38) {
    ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 4);

    Serial.println("Alerta la temperatura ha alcanzado los 38*C");
    alert = "Alerta la temperatura ha alcanzado los 38*C";
  } else {
    alert = "";
  }

  delay(100);
  ledcDetachPin(TONE_OUTPUT_PIN);
}
