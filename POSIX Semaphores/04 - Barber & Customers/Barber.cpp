#include <iostream>
#include "../primitives/primitives.h"

#define CAPACITY 3
/* Barber */

using namespace std;

int main(int argc, char *argv[])
{
	int *onHold;
	p_shm ocupiedSpots("Chairs");
	onHold = static_cast<int *>(ocupiedSpots.map(sizeof(int)));
	p_sem mutex("Mutex", 1); //so more clients are able (or not) to enter the barber shop
	p_sem figaro("Barber", 0);
	p_sem client("Client", 0); //wait for more clients to show up
	p_sem exit("Exit", 0);   //when the barber finishes shaving a client, the barber frees the client to leave the shop
	string answer = "yes";

	while (answer != "finish")
	{
		cout << "Figaro ready to shave..." << endl;
		client.wait(); //waits for clients.
		cout << "There're " << (*onHold) << " clients waiting." << endl;
		mutex.wait();				   //attends a client or let others enter the shop
		*onHold = (*onHold) - 1; //attends client. Frees a chair
		figaro.post();				   //starts shaving client
		mutex.post();				   //allows another client enter while shaving the client on the chair.
		cout << " Shaving ... (any string to keep shaving, finish to end shaving)" << endl;
		cin >> answer;
		exit.post(); //allows the shaved client to leave the shop
	}
	ocupiedSpots.del();
	figaro.del();
	client.del();
	exit.del();
}