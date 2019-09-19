# Sender_LoRA
Envió y recepción de información mediante Arduino uno y LoRA

El proyecto se basa en un sensor de humedad, temperatura y un receptor GPS conectados a un controlador Arduino Uno, los datos obtenidos de
estos sensores son enviados de forma inalambrica con el dispositivo LoRa.

En el otro costado se encuentra un arduino Uno con otro dispositivo LoRa que esta recibiendo la la señal del anterior que contiene los datos de los sensores.

El archivo save_csv permite leer mediante python el puerto serial y almacenas los datos que han sido captados por el receptor.
