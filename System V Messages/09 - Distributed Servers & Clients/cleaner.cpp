#include "../primitives/sv_mq.h"

int main(int argc, char *argv[])
{
	sv_mq servers("/servers");
	servers.del();
}