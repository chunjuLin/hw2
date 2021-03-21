#include "mbed.h"
#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn down(D3);
DigitalIn up(D4);
DigitalIn selected(D5);

AnalogOut aout(PA_4);
//AnalogIn filted_signal(A1);

float frequency = 400; // in Hz
int pre_down;
int pre_up;
int done = 0;

int main()
{
    printf("start! \n\r");
    uLCD.line(29, 55, 99, 55, WHITE);
    uLCD.line(29, 73, 99, 73, WHITE);
    uLCD.line(29, 55, 29, 73, WHITE);
    uLCD.line(99, 55, 99, 73, WHITE);
   // press the button and see the console / led change
   while (done == 0)
   {
        if(selected.read() == 1) done = 1;
        if(done == 0){
            if(pre_down != down.read() && down.read() == 1){
                if(frequency >= 400){
                    frequency -= 100;
                }
            } 
            else if(pre_up != up.read() && up.read() == 1){
                if(frequency < 1000){
                    frequency += 100;
                }
            }
            pre_down = down.read();
            pre_up = up.read();
        }
        uLCD.locate(4,5); uLCD.printf("%d  Hz",(int)frequency);
        uLCD.filled_rectangle(30, 56, 30 + (frequency - 300)/10 - 1, 72, 0x00FF00);
        if(frequency != 1000)uLCD.filled_rectangle(30 + (frequency - 300)/10 , 56, 98, 72, BLACK);
        uLCD.line(99, 55, 99, 73, WHITE);
       // uLCD.cls();
       //uLCD.reset();
       // uLCD.line(29, 55, 29 + frequency/10, 73, WHITE);
     // printf("value down : %d \n\r", down.read());
     // printf("select : %d \n\r", selected.read());
      printf("frequency: %f \n\r", frequency);
      //ThisThread::sleep_for(250ms);
   }
   while (done == 1){
        float T = 1 / frequency;
        float dt = T / 10 * 1000000;
        //printf("T: %f\n\r",T);
        //printf("dt: %f\n\r",dt);
        //printf("dt_int: %d\n\r",(int)dt);
        for (float i = 0.0f; i <= 0.9f; i += 0.1125f) {
            aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
            wait_us((int)dt);
        }
        for (float i = 0.9f; i >= 0.0f; i -= 0.45f) {
            aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
            wait_us((int)dt);
        }
   }
}