#include "esp_camera.h"
#include "Arduino.h"
#include "FS.h"                // Tarjeta SD ESP32
#include "SD_MMC.h"
#include "soc/soc.h"           // Corregir problemas de brownout
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"
#include <EEPROM.h>            // Leer y escribir a memoria flash

// Definir el numero de bytes a acceder
#define EEPROM_SIZE 1

// Definicion de pines para CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

int pictureNumber = 0;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Corregir problemas de brownout
 
  Serial.begin(115200);
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("La camara inicio con el error 0x%x", err);
    return;
  }
  
  Serial.println("Iniciando tarjeta SD");
  if(!SD_MMC.begin()){
    Serial.println("Fallo montaje de tarjeta SD");
    return;
  }
  
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("La tarjeta SD no esta conectada");
    return;
  }
    
  camera_fb_t * fb = NULL;
  
  // Tomar foto con la camara
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("La captura de camara fallo");
    return;
  }
  // Iniciar EEPROM con tamano predefinido
  EEPROM.begin(EEPROM_SIZE);
  pictureNumber = EEPROM.read(0) + 1;

  // Directorio en el que la nueva foto sera guardada
  String path = "/Foto " + String(pictureNumber) +".jpg";

  fs::FS &fs = SD_MMC; 
  Serial.printf("El nombre de la foto es: %s\n", path.c_str());
  
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(!file){
    Serial.println("Fallo al abrir el archivo en modo escritura");
  } 
  else {
    file.write(fb->buf, fb->len); // payload (imagen), payload largo
    Serial.printf("Archivo guardado en el directorio: %s\n", path.c_str());
    EEPROM.write(0, pictureNumber);
    EEPROM.commit();
  }
  file.close();
  esp_camera_fb_return(fb); 
  
  // Apaga el LED on-board (flash) conectado al GPIO 4
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  rtc_gpio_hold_en(GPIO_NUM_4);
  
  delay(2000);
  Serial.println("Pasando a hibernacion ahora");
  delay(2000);
  esp_deep_sleep_start();
  Serial.println("Esto nunca se imprimira");
}

void loop() {
  
}
