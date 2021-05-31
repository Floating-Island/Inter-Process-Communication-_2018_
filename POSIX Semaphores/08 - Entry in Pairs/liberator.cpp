#include <unistd.h>
#include "../primitives/primitives.h"

/* liberator */

using namespace std;

int main(int argc, char *argv[])
{
	p_shm spaceA("processesA");
	p_shm spaceB("procesosB");
	p_sem semaphoreA("semaphoreA", 1);
	p_sem semaphoreB("semaphoreB", 1);
	p_sem semaphorePairA("pairA", 0);
	p_sem semaphorePairB("pairaB", 0);
	p_sem semaphoreControl("control", 0);

	spaceA.del();
	spaceB.del();
	semaphoreA.del();
	semaphoreB.del();
	semaphorePairA.del();
	semaphorePairB.del();
	semaphoreControl.del();
}
