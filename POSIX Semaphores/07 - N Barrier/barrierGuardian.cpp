#include <iostream>
#include <unistd.h>
#include "../primitives/primitives.h"

#include "maximumProcessesCapacity.hpp"
/* Barrier guardian */

using namespace std;

int main(int argc, char *argv[])
{
	int me;
	me = getpid();
	p_sem barrierEntrance("barrierEntrance", MAXIMUM_BARRIER_QUANTITY); //to allow to enter a certain quantity of processes inside barrier
	p_sem barrierExit("barrierExit", 0);						 //to leave the barrier
	p_sem barrierGuardian("barrierGuardian", 0);					 //the guardian allows processes to leave the barrier when reaching the MAXIMUM_BARRIER_QUANTITY

	cout << "guardian " << me << " protect the barrier" << endl;
	while (true)
	{
		barrierGuardian.wait();
		cout << "the maximum number of allowed processes inside the barrier has been reached..." << endl;
		for (int barrierCounter = 0; barrierCounter < MAXIMUM_BARRIER_QUANTITY; barrierCounter++)
		{
			barrierExit.post();
			cout << "I allow " << (barrierCounter + 1) << " processes to leave the barrier" << endl;
		}
		barrierGuardian.wait();
		cout << "A whole batch of processes has left the barrier. I let another batch in..." << endl;
		cout << "Do I let another batch in? yes/no:" << endl;
		string answer;
		cin >> answer;
		if (answer == "no")
			break;
		for (int entranceToBarrier = 0; entranceToBarrier < MAXIMUM_BARRIER_QUANTITY; entranceToBarrier++)
		{
			barrierEntrance.post();
			cout << "I allow " << (entranceToBarrier + 1) << " processes to enter the barrier" << endl;
		}
	}
	p_shm barrierSpots("OccupiedSpots");
	barrierSpots.del();
	p_sem inBarrier("inBarrier", 1);
	inBarrier.del();
	barrierEntrance.del();
	barrierExit.del();
	barrierGuardian.del();
}
