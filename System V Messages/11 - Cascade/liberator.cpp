#include <unistd.h>
#include "../primitives/sv_mq.h"

/* liberator */

using namespace std;

int main(int argc, char *argv[])
{
	sv_mq adder("adder");
	sv_mq printer("printer");

	adder.del();
	printer.del();
}
