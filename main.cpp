/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>
#include <cstdio>

Ticker timer_ms;

uint16_t ovf_cnt_1ms = 0;
uint8_t tx_buff_len = 0, tx_buff[32];
// Blinking rate in milliseconds
#define BLINKING_RATE_MS        10ms //00
#define MAXIMUM_BUFFER_SIZE     32

DigitalOut led(LED1);
AnalogIn   ain(A0);

 static BufferedSerial serial_port(USBTX, USBRX);

void timer_1ms()
{
    //led = !led;
    ovf_cnt_1ms++;
}

int main()
{
    printf("%f\r\n", MBED_BUILD_TIMESTAMP);
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    timer_ms.attach(timer_1ms, 1ms);
    

    while (true) {
        ThisThread::sleep_for(1ms);
        if(ovf_cnt_1ms > 999)
        {
            ovf_cnt_1ms = 0;
            led = !led; 

            //serial_port.write("Hello\r\n", 7);
            printf("Ain: %d \r\n", (uint8_t) ain.read_u16());
        }
    }
}
