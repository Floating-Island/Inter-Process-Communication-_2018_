#include <iostream>
#include "../primitives/primitives.h"

/* Process A */

using namespace std;

int main(int argc, char *argv[])
{

	p_shm espacioA("processesA");
	int *quantityOfA = static_cast<int *>(espacioA.map(sizeof(int)));
	p_sem semaphoreA("semaphoreA", 1);
	p_sem semaphoreControl("control", 0);
	p_sem semaphorePairA("pairA", 0);
	int processNumber = getpid();
	cout << "I, " << processNumber << " being A want to enter..." << endl;
	semaphoreA.wait();
	++(*quantityOfA);
	semaphoreA.post();
	semaphoreControl.post();
	semaphorePairA.wait();
	cout << "I, " << processNumber << " do something with my partner B..." << endl;
	cout << "I, " << processNumber << " leave the place with B..." << endl;
	cout << "I, " << processNumber << " shutdown..." << endl;
}