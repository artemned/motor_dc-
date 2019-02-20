#include <iostream>
#include <conio.h>
#include "motors_.h"
using namespace std;


class Dc_motors:public motor
{
   public:
   Dc_motors(string number_port):motor(number_port){}
        void Forward()
       {
            int j;
            for(j = 0; j < get_speed(); j++)
            { uint8_t ms={0x09};
               write_msg( ms);

            }
            for( ; j < 256; j++)
            { uint8_t sm={0x00};
               write_msg(sm);
            }
       }
        void Reverse()
        {
            int j;
            for(j = 0; j < get_speed(); j++)
             {
               uint8_t ms={0x06};
               write_msg (ms);
             }
            for( ; j < 256; j++)
            {
             uint8_t sm={0x00};
             write_msg(sm);
            }

        }
        void Brake()
        {   uint8_t ms={0x0C};
              write_msg(ms);

        }
};

enum struct MOTORTYPE{
UPFS,//униполярный режим полных фаз
UPHS,//униполярный режим полу фаз
BPFS,//биполярный режим поных фаз
BPHS// биполярный режим полу фаз
};

class Step_motors:public motor
{
public:

 Step_motors(  MOTORTYPE motortype_ , string number_port):motor(number_port)
 {
  motor_type = motortype_;
    CycleIndex = 0;

    switch( motor_type)
   {
     case MOTORTYPE::UPFS :
     MaxIndex = 4;
     Switching[0] = 0x11;
     Switching[1] = 0x12;
     Switching[2] = 0x22;
     Switching[3] = 0x21;
     break;
     case MOTORTYPE::UPHS :
     MaxIndex = 8;
     Switching[0] = 0x01;
     Switching[1] = 0x11;
     Switching[2] = 0x10;
     Switching[3] = 0x12;
     Switching[4] = 0x02;
     Switching[5] = 0x22;
     Switching[6] = 0x20;
     Switching[7] = 0x21;
     break;
     case MOTORTYPE::BPFS :
     MaxIndex = 4;
     Switching[0] = 0x99;
     Switching[1] = 0x69;
     Switching[2] = 0x66;
     Switching[3] = 0x96;
     break;
     case   MOTORTYPE::BPHS :
     MaxIndex = 8;
     Switching[0] = 0x99;
     Switching[1] = 0x09;
     Switching[2] = 0x69;
     Switching[3] = 0x60;
     Switching[4] = 0x66;
     Switching[5] = 0x06;
     Switching[6] = 0x96;
     Switching[7] = 0x90;
   }
}


void Forward()
{

         write_msg(Switching[CycleIndex]);
          if(++CycleIndex == MaxIndex) CycleIndex = 0;
         Sleep(259-get_speed());//пауза

}
 void Reverse()
{
    if(--CycleIndex == -1)
    {
        CycleIndex = MaxIndex-1;
    }
     write_msg(Switching[CycleIndex]);
    Sleep(259-get_speed());

}
void Brake() {
  switch(motor_type)
  {
   case MOTORTYPE::UPFS : case  MOTORTYPE::UPHS :  write_msg(0x11); break;
   case  MOTORTYPE::BPFS : case  MOTORTYPE::BPHS :  write_msg(0x99);
  }
}
 private:
   MOTORTYPE motor_type;//тип двигателя которым управляем
 unsigned char Switching[8];//массив для заполнения байт коммутации двигателя
 int CycleIndex;//для последовательного обращения байтам массива
 int MaxIndex;//определяет момент для перехода на начало массива

};



int main()
{


    Step_motors dc(MOTORTYPE::BPHS,"COM3");
    dc.set_speed(22);
     while(!kbhit()){
      dc.Forward();
     }

    return 0;
}
