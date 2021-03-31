#include "mbed.h"
#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn down(D3);
DigitalIn up(D4);
DigitalIn selected(D5);

AnalogOut aout(PA_4);
AnalogIn ain(D6);

Thread thread;
int frequency = 10; 
float blank = 100;
int pre_down;
int pre_up;
int done = 0;
float sample;
float ADCdata[5000];
int k = 0;

void get_point(){
   // while(1){
       /* for (int i = 0; i < 1000; i++){
            sample = ain;
            ADCdata[i] = sample;
            //ThisThread::sleep_for(1);
            wait_us(1000);
        }*/
        for (int i = 0; i < 1000; i++){
            printf("%f\r\n", ADCdata[i]);
        }
   // }
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
   // thread.start(get_point);
   
        float T = 1.0 / frequency;
        float dt = T / 100 * 1000000;
        printf("%d\n",frequency*100);
        while (k < 1000){
            for (float i = 0.1125f; i <= 0.9f; i += 0.009844f) {
                aout = i;          
                wait_us((int)dt); k++;
            }
            for (float i = 0.9f; i >= 0.0f; i -= 0.045f) {
                aout = i;
                wait_us((int)dt); k++;
                //printf("Hi4\n");
            }
        }
        k = 0;
       // printf("Hi\n");
        while (k < 1000){
            for (float i = 0.1125f; i <= 0.9f; i += 0.009844f) {
                aout = i;
                ADCdata[k] = ain; k++;           
                wait_us((int)dt);
                //printf("Hi1\n");
            }
            for (float i = 0.9f; i >= 0.0f; i -= 0.045f) {
                aout = i;
                ADCdata[k] = ain; k++;
                wait_us((int)dt);
                //printf("H2\n");
            }
        }
        for (int i = 0; i < 1000; i++){
            printf("%f\r\n", ADCdata[i]);
        }
        while (done == 1){
            for (float i = 0.1125f; i <= 0.9f; i += 0.009844f) {
                aout = i;           
                wait_us((int)dt);
            }
            for (float i = 0.9f; i >= 0.0f; i -= 0.045f) {
                aout = i;
                wait_us((int)dt);
            }
        }
}