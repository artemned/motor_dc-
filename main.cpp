#include <iostream>
#include "motors_.h"
using namespace std;

class motor:public abstract_motors,public Comport
{
    public:
    motor(string number_port):Comport(number_port)
    {
        Off();
    }
    void Off()
    {     uint8_t m={0x00};
         write_msg(m);

    }
    void Read()
    {
        read_msg();
    }

    virtual void Forward() =  0;
    virtual void Reverse() =  0;
    virtual void Brake() = 0;


};

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
           // for( ; j < 256; j++)
           // { uint8_t sm={0x00};
             //  write_msg(sm);
           // }
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





int main()
{


    Dc_motors dc{"COM4"};
    dc.set_speed(2);
while(true){
   dc.Forward();
}
    //dc.Read();


  // dc.Brake();

//dc.Reverse();


 // cout<< dc.get_speed()<<endl;
    return 0;
}
