#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "GyverButton.h"
GButton remote1 (2);
GButton mic (3);
GButton but (5);
boolean relay;
byte transmit_data[1];
RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
byte counter;

void setup() {
 Serial.begin(9600);
 radio.begin();
 radio.setAutoAck(1);  
 radio.setRetries(0, 15);
 radio.enableAckPayload();
 radio.setPayloadSize(32);
 radio.openWritingPipe(address[0]);
  radio.setChannel(0x60);
  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  radio.powerUp();
  radio.stopListening();
 }

void loop() {
mic.tick();
but.tick();
remote1.tick();
if (mic.isPress() || but.isPress() || remote1.isPress() ) {
  relay = !relay;
  Serial.println(relay);
  transmit_data[0] = relay;
 }
}
