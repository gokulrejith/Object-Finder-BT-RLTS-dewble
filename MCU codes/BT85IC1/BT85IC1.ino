#include <SoftSerial.h> // use the software uart
SoftSerial bluetooth(2, 4); // RX, TX

unsigned long previousMillis = 0;        // will store last time
const long interval = 500;           // interval at which to delay
static uint32_t tmp; // increment this

void setup() {
  pinMode(1, OUTPUT); // for LED status
  bluetooth.begin(9600); // start the bluetooth uart at 9600 which is its default
  delay(200); // wait for voltage stabilize
  bluetooth.print("BLUtag"); // place your name in here to configure the bluetooth name.
                                       // will require reboot for settings to take affect. 
  delay(3000); // wait for settings to take affect. 
}

void loop() {
  if (bluetooth.available()) { // check if anything in UART buffer
    if(bluetooth.read() == '1'){ // did we receive this character?
       digitalWrite(1,!digitalRead(1)); // if so, toggle the onboard LED   
    }
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bluetooth.print(tmp++); // print this to bluetooth module
  }

}
