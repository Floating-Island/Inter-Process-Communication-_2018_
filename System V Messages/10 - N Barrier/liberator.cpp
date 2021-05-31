#include <unistd.h>
#include "../primitives/sv_mq.h"

/* liberator */

using namespace std;

int main(int argc, char *argv[])
{
	sv_mq enterBarrier("barrierEntrance");
	sv_mq insideBarrier("barrier");

	enterBarrier.del();
	insideBarrier.del();
}
