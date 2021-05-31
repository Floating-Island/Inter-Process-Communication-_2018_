#include <iostream>
#include <cstdlib>
#include <sys/shm.h>
#include "../primitives/primitives.h"
#include "Area.h"

using namespace std;

int main(int argc, char *argv[])
{
	p_shm a51("Area51");
	Area *area;
	area = static_cast<Area *>(a51.map(sizeof(Area)));
	cout << "Read " << (*area) << endl;
}