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

BufferedSerial serial_port(USBTX, USBRX);


void timer_1ms()
{
    //led = !led;
    ovf_cnt_1ms++;
}

int main()
{

    timer_ms.attach(timer_1ms, 1ms);
    

    while (true) {
        ThisThread::sleep_for(1ms);
        if(ovf_cnt_1ms > 999)
        {
            ovf_cnt_1ms = 0;
            led = !led; 

            printf("Ain: %d \r\n", (uint8_t) ain.read_u16());
        }
    }
}
