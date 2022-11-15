#include "Header.h"
#include <time.h>
using namespace std;
namespace Serial
{
	string COM = "\\\\.\\COM";
	string num = "";
	HANDLE serialHandle;
	COMSTAT status_;
	DWORD errors_;
	void init(int baut)
	{
		cout << "COM?:\n";
		cin >> COM;
		
		COM += num;
		cout <<COM<< endl;
		if(num == "-")
		{
			COM = "\\\\.\\COM15";
			cout << "COM 15 OK?";
		}
		else if (COM[0] != '\\' )
		{
			COM = "\\\\.\\" + COM;
		}
		
			std::wstring stemp = std::wstring(COM.begin(), COM.end());
			LPCWSTR sw = stemp.c_str();
			serialHandle = CreateFile(sw, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DCB serialParams = { 0 };
		serialParams.DCBlength = sizeof(serialParams);


		DCB dcbSerialParams = { 0 };

		if (!GetCommState(serialHandle, &dcbSerialParams)) {

			printf("Warning: Failed to get current serial params");
		}

		else {
			dcbSerialParams.BaudRate = 115200;
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;
			dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(serialHandle, &dcbSerialParams))
				printf("Warning: could not set serial port params\n");
			else {

				PurgeComm(serialHandle, PURGE_RXCLEAR | PURGE_TXCLEAR);
			}
			COMMTIMEOUTS timeout = { 0 };
			timeout.ReadIntervalTimeout = 50;
			timeout.ReadTotalTimeoutConstant = 50;
			timeout.ReadTotalTimeoutMultiplier = 50;
			timeout.WriteTotalTimeoutConstant = 50;
			timeout.WriteTotalTimeoutMultiplier = 10;

			SetCommTimeouts(serialHandle, &timeout);


			cout << "Port "<<num<<" offen\n";
		}
	}
	string readSer()
	{
		int reply_wait_time = 1;
		char buf[1];
		char front_delimiter_ = '?';
		char end_delimiter_ = '!';
		DWORD bytes_read;
		string result;
		bool began = false;
		ClearCommError(serialHandle, &errors_, &status_);
		unsigned long start_time = time(nullptr);
		while ((time(nullptr) - start_time) < reply_wait_time)
		{

			if (status_.cbInQue > 0)
			{
				if (ReadFile(serialHandle, buf, 1, &bytes_read, NULL))
				{
					if (buf[0] == front_delimiter_ || began) {
						began = true;

						if (buf[0] == end_delimiter_)
							return result;

						if (buf[0] != front_delimiter_)
							result.append(buf, 1);
					}
				}
			}

		}
		return "?";
	}
	
	void Communicate(vector<Vec> vecs)
	{
		int count = 0;
		while (count < vecs.size())
		{
			
			string request = readSer();
			cout << "\nanswer == " << request;
			if (request == "Request")
			{
				cout << "\nsending\n";
				int roundedG = round(vecs[count].degree);
				int roundedD = round(vecs[count].distance);
				string answer;
				answer += "G";
				answer += to_string(roundedG);
				answer += "D";
				answer += to_string(roundedD);
				cout << answer << '\n';
				count++;

				const char* cstr = answer.c_str();
				WriteFile(serialHandle, cstr, answer.size(), NULL, NULL);
			}
		}
		while (1)
		{
			string request = readSer();
			cout << "\nanswer == " << request;
			string provile = "X";
			const char* end = provile.c_str();
			if (request == "Request")
			{
				WriteFile(serialHandle, end, provile.size(), NULL, NULL);
				break;
			}
		}
		

		CloseHandle(serialHandle);
		cout << "\nComplete\n";
		int main();
		main();
	}

}