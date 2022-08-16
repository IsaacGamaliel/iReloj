# Desarrollo para  dispositivos inteligentes
## Nombre del proyecto: iReloj
## Integrantes del equipo:
- Rojas Hernández Miguel Arturo
- Muñiz Amaro Isaac Gamaliel
- Miranda Valtierra Carlos Eduardo
- Balderas Zamora José Guillermo
# Objetivo del proyecto
iReloj es un proyecto que consiste en ser un dispositivo portable cómodo, que solvente algunas de las necesidades del usuario. Algunas de las funcionalidades con las que contará el proyecto son, detección de temperatura, humedad, presión y tomar fotos para poder visualizarlas en la computadora. 

# Visión
Tener un prototipo final, que cumpla con las necesidades del usuario para ayudarlo a informar como esta su entorno día a día. 

# Software empleado
- Arduino IDE 1.8.19: Permite escribir, depurar, editar y grabar nuestro programa (llamados “sketches” en el mundo Arduino) de una manera sumamente sencilla, en gran parte a esto se debe el éxito de Arduino, a su accesibilidad.

# Librerías usadas:
- AsyncTCP: Biblioteca asíncrona SSL TCP para ESP32.
- CameraWebServer_Access_Point: para establecer una conexión inalámbrica entre equipos y pueden formar una red inalámbrica externa (local o internet) con la que interconectar dispositivos móviles o tarjetas de red inalámbricas.
- ESPAsyncWebServer : Podemos crear un servidor asíncrono, es decir, que es capaz de atender a varios clientes de forma simultánea.
- NTPClient: Es un protocolo de Internet para sincronizar los relojes de los sistemas informáticos a través del enrutamiento de paquetes.

# Hadware 
![image](https://user-images.githubusercontent.com/68245966/184734671-daef5f7e-6f6d-478b-93ff-5cdaa2458e0b.png)

# Arquitectura(Modelo 3 capas)
![image](https://user-images.githubusercontent.com/68245966/184910048-b9b76973-c826-42f1-963f-64314de4c839.png)

# Historias de usuario
- Detector de temperatura: Mandará la información a una pantalla del reloj para que sea visible por parte del usuario.
- Cámara: El usuario podrá tomar fotografías.
- Detector de presión: Mandará la información a una pantalla.
- Detector de humedad: Mandará la información a una pantalla.
- Detector de gas: para visualizarlo en pantalla y en dispositivo móvil.

# Capturas de pantalla del tablero trello para cada uno de los sprints del proyecto
![image](https://user-images.githubusercontent.com/68245966/184734969-13a443bd-0b4d-41d4-9edc-b8bfdce08c9f.png)

![image](https://user-images.githubusercontent.com/68245966/184734992-74655573-6174-4ca1-b535-acbd3cf82ad4.png)

![image](https://user-images.githubusercontent.com/68245966/184735012-95b90c16-33ba-4ec7-bd34-a5daf0955282.png)

# Circuito
![image](https://user-images.githubusercontent.com/68245966/184735088-374820a3-6ebf-460b-b4c1-deec13ca4b92.png)

# Prototipo
![WhatsApp Image 2022-06-10 at 12 14 56 AM](https://user-images.githubusercontent.com/68245966/173080481-b01f618e-74fb-432e-b7ea-7b69f68015cb.jpeg)

# Resultados
Una primera fase en donde se estaba en prueba, con el sensor Bme680 impriminedo la información en la pantalla.
![image](https://user-images.githubusercontent.com/68245966/184735132-62a1e072-03ce-4825-8a45-0938b9163a96.png)

Reloj de papel con ESP32-CAM en un primera fase de diseño y funcionamiento.

![image](https://user-images.githubusercontent.com/68245966/184735184-36e08d2b-6a2f-4505-82d4-295677dd2319.png)

Proyecto terminado con material de plastico.

![image](https://user-images.githubusercontent.com/68245966/184735227-485a2dc7-31bf-4053-a4be-89ea01e109af.png)

# Trello
https://trello.com/b/ET21GXpT/ireloj

# Youtube
https://youtu.be/qDpQkG1Gta0
