#ifndef Area_h
#define Area_h
#include "../primitives/Message.h"

class Area
{
public:
	static const int size = 5;

private:
	Message ms[size];
	int ip;
	int is;
	int integerPut();
	int integerRetrieve();
	friend std::ostream &operator<<(std::ostream &os, Area a);

public:
	Area() : ip(0), is(0) { std::cout << "Area made" << std::endl; };
	Message &operator[](int i);
	void put(Message m);
	Message retrieve();
	void setLast();
	bool isLast();
};
Message &Area::operator[](int i)
{
	return ms[i];
}

int Area::integerPut()
{
	int aux = ip;
	ip = (ip + 1) % size;
	return aux;
}

int Area::integerRetrieve()
{
	int aux = is;
	is = (is + 1) % size;
	return aux;
}
void Area::put(Message m)
{
	ms[integerPut()] = m;
}
Message Area::retrieve()
{
	Message m = ms[integerRetrieve()];
	return m;
}
void Area::setLast()
{
	//puts 'last' flag in the one next to the last inserted
	// uses ip instead of integerPut
	ms[ip].setLast();
}

bool Area::isLast()
{
	return ms[is].isLast();
}

std::ostream &operator<<(std::ostream &os, Area a)
{
	os << "area ip=" << a.ip << " is=" << a.is << std::endl;
	for (int i = 0; i < a.size; i++)
	{
		os << "ms[" << i << "]=" << a.ms[i];
		if (a.ms[1].isLast())
			os << "last";
		os << std::endl;
	}
	return os;
}

#endif
