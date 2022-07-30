#include "Header.h"
using namespace std;
namespace newUI
{
	int getX(string buffer)
	{
		int posx = buffer.find_first_of('X');
		int posy = buffer.find_first_of('Y');
		buffer = buffer.substr(0,posy-1);
		buffer = buffer.substr(posx +2,buffer.size());
		cout << buffer;
		return stoi(buffer);
	}
	int getY(string buffer)
	{
		int posy = buffer.find_first_of('Y');
		buffer = buffer.substr(posy +2 , buffer.size());
		return stoi(buffer);
	}
}
bool newUi()
{
	ifstream in("Eigenschaften.txt",ios ::binary);
	string buf;
	getline(in,buf);
	int x = stoi(buf);
	if (x == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool equel(char n1[7])
{
	const char comper[] = { 'R','e','q','u','e','s','t' };
	for (int i = 0; i < 7;i++)
	{
		if (n1[i] != comper[i])
		{
			return false;
		}
	}
	return true;
}