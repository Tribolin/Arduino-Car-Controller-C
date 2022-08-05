
#include "Header.h"
using namespace std;

struct Point
{
	int x;
	int y;
};

float diff(int x,int y)
{
	if (x > y)
	{
		return (x - y);
	}
	if (x < y)
	{
		return y - x;
	}
	return 0;
}
vector<Point> getPoints()
{
	
	
	bool UI = newUi();
	vector<Point> points;
	Point end;
	end.x = 0;
	end.y = 0;
	int i = 0;
	points.push_back(end);
    Point p;
	if (!UI)
	{
		
		do
		{
			
			i++;
			cout << "X:";
			cin >> p.x;
			cout << "Y:";
			cin >> p.y;
			points.push_back(p);
			cout << "Point added\n";
		} while (points[i].x != end.x || points[i].y != end.y);
		
	}
	else
	{
		system("Controller.exe");
		ifstream x("CarData.txt",ios::binary);
		if ( x.fail())
		{
			cerr << "File Error!!\n trying again!\n";
			return getPoints();
		}
		string buffer;
		while (x.good() && getline(x,buffer))
		{
			cout << buffer << '\n';
			p.x = newUI::getX(buffer);

			p.y = newUI::getY(buffer);
			cout << "X"<<p.x<<'\n' << "Y"<<p.y<<'\n';
			points.push_back(p);
			
			
		}
		points.push_back(end);
	}
	cout << "\nok\n";
	
	return points;
}

void getVecs(vector<Point> raw,vector<Vec>& vecs)
{
	Point last = raw[0];
	Vec newvec;
	float geg = 0;
	float an = 0;
	float dergreebuf;
	float lastdegree = 0;
	float lastdegreebuf = 0;
	for (size_t i = 0; i < raw.size(); i++)
	{
		geg = diff(last.y,raw[i].y);
		an = diff(last.x, raw[i].x);
		newvec.distance = sqrt(pow(geg,2) + pow(an,2));
		float buf = geg / newvec.distance;
		newvec.distance != 0?dergreebuf = (asin(buf) * 180 / 3.1415):dergreebuf = 0;
		if (last.x > raw[i].x) 
		{
			dergreebuf = 180 - dergreebuf;

		}
		if (last.y > raw[i].y)
		{
			dergreebuf *= -1;
		}
		
		dergreebuf -= 90;
		dergreebuf = round(dergreebuf);
		newvec.degree = dergreebuf - lastdegree;
		lastdegree = dergreebuf;
		cout << newvec.degree << "  = degree \n";
		cout << newvec.distance << " = distance\n";
		vecs.push_back(newvec);
		last = raw[i];
	}
}

int main()
{
	
	vector<Vec> vecs;
	cout << "To add a new Point tipe in first x then press enter , then y and press enter.\nTo end use Point(0|0):\n";
	//Vectrenberechnung für Auto (relative Gradzahlen; Achtung (* -1))
	getVecs(getPoints(),vecs);
	cout << "\nVectorenberechnung abgeschlossen\nStarte Kommunication\n";
	Serial :: init(9600);
	Serial :: Communicate(vecs);
	
	
}
