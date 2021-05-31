#include <iostream>
#include "../primitives/primitives.h"

/* Process B */

using namespace std;

int main(int argc, char *argv[])
{

	p_shm espacioB("processesB");
	int *quantityOfB = static_cast<int *>(espacioB.map(sizeof(int)));
	p_sem semaphoreB("semaphoreB", 1);
	p_sem semaphoreControl("control", 0);
	p_sem semaphorePairB("pairB", 0);
	int processNumber = getpid();
	cout << "I, " << processNumber << " being B want to enter..." << endl;
	semaphoreB.wait();
	++(*quantityOfB);
	semaphoreB.post();
	semaphoreControl.post();
	semaphorePairB.wait();
	cout << "I, " << processNumber << " do something with my partner A..." << endl;
	cout << "I, " << processNumber << " leave the place with my partner A..." << endl;
	cout << "I, " << processNumber << " shutdown..." << endl;
}