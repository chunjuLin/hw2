#include "mbed.h"
#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn down(D3);
DigitalIn up(D4);
DigitalIn selected(D5);

AnalogOut aout(PA_4);
AnalogIn ain(D6);

Thread thread;

float frequency = 10; 
float blank = 100;
int pre_down;
int pre_up;
int done = 0;
float sample;
float ADCdata[1000];

void get_point(){

    for (int i = 0; i < 1000; i++){
        sample = ain;
        ADCdata[i] = sample;
        wait_us(1000);
    }
    for (int i = 0; i < 1000; i++){
        printf("%f\r\n", ADCdata[i]);
    }
}

int main()
{

    uLCD.line(29, 55, 99, 55, WHITE);
    uLCD.line(29, 73, 99, 73, WHITE);
    uLCD.line(29, 55, 29, 73, WHITE);
    uLCD.line(99, 55, 99, 73, WHITE);

   while (done == 0)
   {
        if(selected.read() == 1) done = 1;
        if(done == 0){
            if(pre_down != down.read() && down.read() == 1){
                if(frequency >= 10){
                    frequency -= 20;
                    blank -= 100;
                }
            } 
            else if(pre_up != up.read() && up.read() == 1){
                if(frequency < 1000){
                    frequency += 20;
                    blank += 100;
                }
            }
            pre_down = down.read();
            pre_up = up.read();
        }
        uLCD.locate(4,5); uLCD.printf("%d  Hz",(int)frequency);
        uLCD.filled_rectangle(30, 56, 30 + (blank)/10 - 1, 72, 0x00FF00);
        if(frequency != 130)uLCD.filled_rectangle(30 + (blank)/10, 56, 98, 72, BLACK);
        uLCD.line(99, 55, 99, 73, WHITE);

   }
    thread.start(get_point);
   while (done == 1){
        float T = 1 / frequency;
        float dt = T / 10 * 1000000;
        for (float i = 0.1125f; i <= 0.9f; i += 0.1125f) {
            aout = i;
            wait_us((int)dt);
        }
        for (float i = 0.9f; i >= 0.0f; i -= 0.45f) {
            aout = i;
            wait_us((int)dt);
        }
   }
}