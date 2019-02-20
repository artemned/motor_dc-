#pragma once
#include "COMPORT.h"
class abstract_motors
{
   public:
    abstract_motors()
    {
        Speed=0;
    }
    int get_speed()const
    {
        return Speed;
    }
    void set_speed(int speed)
    {
        Speed=speed;
        if(speed<=0)Speed=0;
        if(speed>=255)Speed=255;
    }
    virtual void Off() = 0;//отключает мотор
    virtual void Forward() = 0;//движение вперед
    virtual void Reverse() = 0;//движение назад
    virtual void Brake() = 0;//остановка мотора
    virtual ~abstract_motors(){}

private:
    int Speed;//скорость
};
class motor:public abstract_motors,public Comport
{
    public:
    motor(std::string number_port):Comport(number_port)
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
