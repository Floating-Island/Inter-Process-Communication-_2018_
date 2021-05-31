#include <iostream>
#include "../primitives/primitives.h"
#include "maximumProcessesCapacity.hpp"
/* Process */

using namespace std;

int main(int argc, char *argv[])
{
	int *QuantityAtBarrier;
	p_shm barrierSpaces("OccupiedSpots");
	QuantityAtBarrier = static_cast<int *>(barrierSpaces.map(sizeof(int)));
	p_sem inBarrier("inBarrier", 1);								 //to change the quantity of processes inside barrier
	p_sem barrierEntrance("barrierEntrance", MAXIMUM_BARRIER_QUANTITY); //to allow to enter a certain quantity of processes inside barrier
	p_sem barrierExit("barrierExit", 0);						 //to exit the barrier
	p_sem barrierGuardian("barrierGuardian", 0);						 //the guardian allows processes to leave the barrier when reaching the MAXIMUM_BARRIER_QUANTITY

	int processNumber = getpid();
	cout << "I, " << processNumber << " want to enter the barrier..." << endl;
	barrierEntrance.wait(); //wants to enter the barrier
	cout << "I, " << processNumber << " enter the barrier..." << endl;
	inBarrier.wait();	//inside the barrier, wants to increase the number of processes in the barrier
	++(*QuantityAtBarrier); //increments the processes quantity in the barrier
	cout << "There're " << (*QuantityAtBarrier) << " processes in the barrier." << endl;
	if ( (*QuantityAtBarrier) == MAXIMUM_BARRIER_QUANTITY)
	{
		barrierGuardian.post(); //if the maximum quantity of processes in the barrier is reached, awake the guardian
		cout << "I, " << processNumber << " notify the guardian that the maximum quantity of processes inside has been reached..." << endl;
	}
	inBarrier.post(); //allows others to modify the quantity of processes inside the barrier
	cout << "I, " << processNumber << " want to leave the barrier..." << endl;
	barrierExit.wait(); //waits to exit the barrier
	cout << "I, " << processNumber << " leave the barrier..." << endl;
	inBarrier.wait();	//leaves barrier, wants to decrease the number of processes in the barrier
	--(*QuantityAtBarrier); //decreases the number of processes inside the barrier
	cout << "There're " << (*QuantityAtBarrier) << " processes in the barrier." << endl;
	if ( (*QuantityAtBarrier) == 0)
	{
		barrierGuardian.post(); //the last one to leave the barrier, awakes the guardian to allow another batch of processes to enter
		cout << "I, " << processNumber << " notify the guardian that all the processes batch has left..." << endl;
	}
	inBarrier.post(); //allows others to modify the number of processes inside the barrier
	cout << "I, " << processNumber << " am free and I shutdown..." << endl;
}