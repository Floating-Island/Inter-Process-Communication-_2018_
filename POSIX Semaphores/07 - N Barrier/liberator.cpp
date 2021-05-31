#include <unistd.h>
#include "../primitives/primitives.h"
#include "maximumProcessesCapacity.hpp"
/* liberator */

using namespace std;

int main(int argc, char *argv[])
{
	p_shm spotsInBarrier("OccupiedSpots");
	p_sem inBarrier("inBarrier", 1); //to change the quantity of processes inside the barrier
	p_sem barrierEntrance("barrierEntrance", MAXIMUM_BARRIER_QUANTITY);//to allow a number of processes enter the barrier
	p_sem barrierExit("barrierExit", 0); //to leave the barrier
	p_sem barrierGuardian("barrierGuardian", 0);   //the guardian allows processes to leave the barrier when reaching the MAXIMUM_BARRIER_QUANTITY

	spotsInBarrier.del();
	inBarrier.del();
	barrierEntrance.del();
	barrierExit.del();
	barrierGuardian.del();
}
