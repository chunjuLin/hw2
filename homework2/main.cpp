#include "mbed.h"
#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn down(D3);
DigitalIn up(D4);
DigitalIn selected(D5);

int frequency = 100; // in Hz
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
   while (1)
   {
        if(selected.read() == 1) done = 1;
        if(done == 0){
            if(pre_down != down.read() && down.read() == 1){
                if(frequency > 100){
                    frequency -= 100;
                }
            } 
            else if(pre_up != up.read() && up.read() == 1){
                if(frequency < 700){
                    frequency += 100;
                }
            }
            pre_down = down.read();
            pre_up = up.read();
        }
        uLCD.locate(4,5); uLCD.printf("%d Hz",frequency);
        uLCD.filled_rectangle(30, 56, 30 + frequency/10 - 1, 72, 0x00FF00);
        if(frequency != 700)uLCD.filled_rectangle(30 + frequency/10 , 56, 98, 72, BLACK);
        uLCD.line(99, 55, 99, 73, WHITE);
       // uLCD.cls();
       //uLCD.reset();
       // uLCD.line(29, 55, 29 + frequency/10, 73, WHITE);
     // printf("value down : %d \n\r", down.read());
      printf("select : %d \n\r", selected.read());
      printf("frequency: %d \n\r", frequency);
      //ThisThread::sleep_for(250ms);
   }
}