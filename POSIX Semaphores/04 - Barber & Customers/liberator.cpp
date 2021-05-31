#include <unistd.h>
#include "../primitives/primitives.h"

/* liberator */

using namespace std;
int main(int argc, char *argv[])
{
	p_shm occupiedSpots("Chairs");
	occupiedSpots.del();
	p_sem mutex("Mutex", 1);
	mutex.del();
	p_sem figaro("Barber", 0);
	figaro.del();
	p_sem client("Client", 0);
	client.del();
	p_sem exit("Exit", 0);
	exit.del();
}
