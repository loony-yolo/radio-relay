#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "GyverButton.h"
GButton but (3);
RF24 radio(9, 10);
byte recieved_data[1];
byte relay = 5;
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

void setup() {
  pinMode(relay, OUTPUT);
  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(0, 15);
  radio.enableAckPayload();
  radio.setPayloadSize(32);
  radio.openReadingPipe(1, address[0]);
  radio.setChannel(0x60);
  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  radio.powerUp();
  radio.startListening();
}

void loop() {
  byte pipeNo;
   while ( radio.available(&pipeNo))
    radio.read( &recieved_data, sizeof(recieved_data) );
    digitalWrite(relay, recieved_data[0]);
but.tick();
if (but.isPress()) {
  relay = !relay;
 }  
}
