#pragma once
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <string.h>
#include <string>



class Comport{
 public:
        Comport( std::string& number_por);

        ~Comport();
 void  write_msg(char* ms);
 void read_msg();

const char* buffer;
private:
DCB dcbSerialParams;
COMMTIMEOUTS timeouts;
HANDLE hComm;
bool   Status;
char  TempChar;//����� ������                        // Temperory Character
char  SerialBuffer[256]; //������ ������
DWORD NoBytesRead;
DWORD dwEventMask;
int i = 0;

   };


