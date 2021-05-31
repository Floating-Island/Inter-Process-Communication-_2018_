#include <iostream>
#include <unistd.h>
#include "../primitives/primitives.h"

/* control */

using namespace std;

int main(int argc, char *argv[])
{
	p_shm spaceA("processesA");
	int *quantityOfA = static_cast<int *>(spaceA.map(sizeof(int)));
	p_shm spaceB("processesB");
	int *quantityOfB = static_cast<int *>(spaceB.map(sizeof(int)));
	p_sem semaphoreA("semaphoreA", 1);
	p_sem semaphoreB("semaphoreB", 1);
	p_sem semaphorePairA("pairA", 0);
	p_sem semaphorePairB("pairB", 0);
	p_sem semaphoreControl("control", 0);
	int processNumber = getpid();
	cout << "control " << processNumber << " allow to enter processes in pairs" << endl;
	while (true)
	{
		cout << "wait for processes to try to enter..." << endl;
		semaphoreControl.wait();
		semaphoreA.wait();
		if ((*quantityOfA) > 0)
		{
			cout << "there're A processes waiting..." << endl;
			semaphoreB.wait();
			if ((*quantityOfB) > 0)
			{
				cout << "there're B processes waiting..." << endl;
				cout << "a pair of processes A and B is allowed to enter..." << endl;
				semaphorePairA.post();
				semaphorePairB.post();
				cout << "I remove a process from space A..." << endl;
				--(*quantityOfA);
				cout << "I remove a process from space B..." << endl;
				--(*quantityOfB);
				cout << "There's a pair of processes less..." << endl;
				cout << "do I let more pairs to enter? yes/no" << endl;
				string answer;
				cin >> answer;
				if (answer == "no")
					break;
			}
			semaphoreB.post();
		}
		semaphoreA.post();
	}
	spaceA.del();
	spaceB.del();
	semaphoreA.del();
	semaphoreB.del();
	semaphorePairA.del();
	semaphorePairB.del();
	semaphoreControl.del();
	cout << "I" << endl;
}
