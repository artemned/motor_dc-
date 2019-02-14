#include "COMPORT.h"

using namespace std;





Comport::Comport(string& number_port ){

const char* buffer=number_port.c_str();//имя порта
	Comport::hComm = CreateFile( buffer,                       // Name of the Port to be Opened
							GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
							0,                                 // No Sharing, ports cant be shared
							NULL,                              // No Security
							OPEN_EXISTING,                     // Open existing port only
							0,                                 // Non Overlapped I/O
							NULL);
		if (Comport::hComm == INVALID_HANDLE_VALUE)
			printf("\n   Error! - Port %s can't be opened", buffer);
		else
			printf("\n   Port %s Opened\n ", buffer);

      Comport::dcbSerialParams={0};
       dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

		Status = GetCommState(hComm, &dcbSerialParams);     //retreives  the current settings

		if (Status == FALSE)
			printf("\n   Error! in GetCommState()");

		dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
		dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
		dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
		dcbSerialParams.Parity   = NOPARITY;      // Setting Parity = None

		Comport::Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

		if (Status == FALSE)
			{
				printf("\n   Error! in Setting DCB Structure");
			}
		else
			{
				printf("\n   Setting DCB Structure Successfull\n");
				printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
				printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
				printf("\n       StopBits = %d", dcbSerialParams.StopBits);
				printf("\n       Parity   = %d", dcbSerialParams.Parity);
			}


      Comport::timeouts = { 0 };
        timeouts.ReadIntervalTimeout         = 50;
 		timeouts.ReadTotalTimeoutConstant    = 50;
		timeouts.ReadTotalTimeoutMultiplier  = 10;
		timeouts.WriteTotalTimeoutConstant   = 50;
		timeouts.WriteTotalTimeoutMultiplier = 10;

		if (SetCommTimeouts(Comport::hComm, &timeouts) == FALSE)
			printf("\n   Error! in Setting Time Outs");
		else
			printf("\n\n   Setting Serial Port Timeouts Successfull");
			cout<<"\n";

       }
Comport:: ~Comport()
{
    CloseHandle(Comport::hComm);
    cout<<"goodbye";
}


void  Comport::write_msg(char* msg){



       // lpBuffer should be  char or byte array, otherwise write wil fail

        if(msg=="1000")
           {

		CloseHandle(Comport::hComm);//Closing the Serial Port
		printf("\n ==========================================\n");


		}
        const char* buf=msg;

		DWORD   dNoOFBytestoWrite;              // No of bytes to write into the port
		DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port

		dNoOFBytestoWrite = sizeof(buf); // Calculating the no of bytes to write into the port

	 Status = WriteFile(hComm,               // Handle to the Serialport
						   buf,            // Data to be written to the port
						   dNoOFBytestoWrite,   // No of bytes to write into the port
						   &dNoOfBytesWritten,  // No of bytes written to the port
						   NULL);

		if (Status == TRUE)
		{
		    printf("\n\n    %s - Written to %s", buf, buf);
			cout<<"\n";
		}

		else
			printf("\n\n   Error %d in Writing to Serial Port",GetLastError());




     };
void Comport::read_msg()
{



      DWORD iSize;
      char sReceivedChar[256];
      bool flag=true;
      while(true)
      {
            ReadFile(Comport::hComm, &sReceivedChar, sizeof(sReceivedChar), &iSize, 0);  // получаем 1 байт
            if (iSize > 0)   // если что-то принято, выводим
                cout << sReceivedChar;
                flag=false;

      }


}






