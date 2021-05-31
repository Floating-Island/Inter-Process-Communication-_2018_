#include <iostream>
#include <unistd.h>
#include "../primitives/primitives.h"

#define CAPACITY 3
/* Client */

using namespace std;

int main(int argc, char *argv[])
{
	int *onHold, me;
	me = getpid();
	p_shm occupiedSpots("Chairs");
	onHold = static_cast<int *>(occupiedSpots.map(sizeof(int)));
	p_sem mutex("Mutex", 1);
	p_sem figaro("Barber", 0);
	p_sem cliente("Client", 0);
	p_sem salida("Exit", 0);
	string answer;

	cout << "Client " << me << " wants to shave" << endl;
	mutex.wait(); //tries to enter the barber shop
	if ((*onHold) < CAPACITY)
	{
		*onHold = (*onHold) + 1; //enters the barber shop
		cliente.post();				   //waits for barber to attend him.
		mutex.post();				   //barber is going to serve him, barber allows another customer to enter the shop
		cout << "Client " << me << " waiting barber. Position " << (*onHold) << endl;
		figaro.wait(); //waits for the barber to shave him
		cout << " Shaving ... " << endl;
		salida.wait();
		cout << "Bye" << endl;
	}
	else
	{
		cout << "No room to enter." << endl;
		mutex.post();
	}
}
