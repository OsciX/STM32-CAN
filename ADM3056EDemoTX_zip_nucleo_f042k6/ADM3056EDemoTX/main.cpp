#include "CAN.h"
#include "mbed.h"


#define TXD_PIN PA_12
#define RXD_PIN PA_11
#define SILENT_PIN A2
#define STBY_PIN A1
#define RS_PIN A0

DigitalOut SILENT(SILENT_PIN);
DigitalOut STBY(STBY_PIN);
DigitalOut RS(RS_PIN);

#if defined (DEVICE_CAN) || defined(DOXYGEN_ONLY)

Ticker ticker;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
/** The constructor takes in RX, and TX pin respectively.
  * These pins, for this example, are defined in mbed_app.json
  */
CAN can1(RXD_PIN, TXD_PIN);


    
uint64_t data = 18446744073709551100;


void send() {
    printf("send()\n");
    if(can1.write(CANMessage(1337, (char*) &data, 8))) {
        printf("wloop()\n");
        printf("Message sent: %d\n", data);
        data++;
    } 
    led1 = !led1;
}

int main() {
    
    SILENT = 0;
    STBY = 0;
    RS = 0;
    
    can1.frequency(125000);
    can1.mode(CAN::Normal);
    printf("main()\n");
    ticker.attach(&send, 1);
    CANMessage msg;
    while(1) {
        printf("loop()\n");
        /*
        if(can1.read(msg)) {
            printf("Message received: %d\n", msg.data[0]);
            led2 = !led2;
        } */
        wait(0.2);
    }
}

#else
  #error CAN NOT SUPPORTED
  
#endif