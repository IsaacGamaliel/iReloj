# iReloj
iReloj es un proyecto que consiste en ser un dispositivo portable cómodo, que solvente algunas de las necesidades del usuario. El reloj será capaz de recoger información importante para después mandarla a una base de datos y después analizarla para darle sugerencias o advertencias al usuario mediante notificaciones a su celular. Esto para que sea más ágil para el usuario.  Las situaciones que gestionara el dispositivo serán detector de temperaturas, esto con el fin de hacer recomendaciones al usuario en caso de haga frio o calor. Las sugerencias se le harán llegar a su celular mediante una sencilla e intuitiva aplicación móvil en donde algunas de las sugerencias serian: Portar un abrigo en caso de hacer frio o hidratarse en caso de hacer calor.  Otra de las situaciones será el movimiento, aquí se pretende que se analice los pasos dados diariamente, distancia recorrida y al final de la semana darle una estadística de su información.  El proyecto pretende crear un dispositivo inteligente capaz de ayudar a las personas en sus actividades diarias así como cuidarlas de diferentes riesgos que se viven día a día. 

# Componentes
| Nombre de componente | Imagen | ¿Qué hace? |
| ------------- | ------------- | ------------- |
| Sensores DHT11 y DHT22  | ![Image text](https://user-images.githubusercontent.com/44191076/53887826-0ebece80-405e-11e9-997b-a9f1b5e67a41.jpg)  | Pueden medir tanto la humedad como la temperatura. Solo se utiliza un GPIO. La diferencia entre los dos es principalmente el rango de medición y la precisión. El DHT22 (el blanco) puede medir todos los rangos de humedad con una precisión del 2%. Mientras que el DHT11 (azul) solo puede medir áreas con un 20-90% de humedad y, sobre todo, la precisión es significativamente peor con un 5%. |
| Sensores de gas MQ  | ![Sensor de Alcohol MQ3](https://naylampmechatronics.com/249-large_default/sensor-de-alcohol-mq3.jpg) | pueden detectar diferentes gases a temperatura ambiente.El MQ-2 puede reconocer metano, butano, GLP y humo, el MQ-3 detecta, por ejemplo, alcohol, etanol y humo, etc. |
| Sensor de movimiento PIR  | ![Sensor de movimiento PIR](https://www.albri.com.mx/fotos_producto/5030.jpg)   | Tiene algunas ventajas sobre otros productos similares: además del bajo precio, solo envía una señal si algo se mueve. Esto te permite esperar los flancos de señal usando los GPIO. Además, se puede variar una resistencia para que solo se envíe una señal cuando el movimiento esté cerca, o se perciban cambios que ya están lejos  |
| Módulo GPS NEO-6M  | ![Módulo GPS NEO-6M](https://media.naylampmechatronics.com/294-superlarge_default/modulo-gps-neo-6m.jpg)  | El receptor GPS más común y más conocido es el módulo NEO-6M. Todos los datos de posición GPS se pueden determinar con la ayuda de los satélites en órbita.  |
| esp32-cam  | ![image](https://user-images.githubusercontent.com/68245966/173081085-2d94b969-3721-421c-9f12-b26354f1e223.png) | Esto le permite nuevas funciones, como las de vigilancia o espionaje remoto capturando todo lo que ocurre cuando tú no estás y enviarlo a cualquier dispositivo para su grabación  |

# Arquitectura(Modelo 3 capas)
![image](https://user-images.githubusercontent.com/68245966/173080326-2484b7ea-0a6a-48b9-b518-0b322f8e20b5.png)

# Prototipo
![WhatsApp Image 2022-06-10 at 12 14 56 AM](https://user-images.githubusercontent.com/68245966/173080481-b01f618e-74fb-432e-b7ea-7b69f68015cb.jpeg)

# Trello
https://trello.com/b/ET21GXpT/ireloj
