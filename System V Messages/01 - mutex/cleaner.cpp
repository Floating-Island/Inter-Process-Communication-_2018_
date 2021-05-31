#include "../primitives/sv_mq.h"

using namespace std;

int main()//eliminates message queues
{
	mpdu message;
	sv_mq mutex("/mutex");
	mutex.del();
}