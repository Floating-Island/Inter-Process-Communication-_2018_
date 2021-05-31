#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "../primitives/sv_mq.h"
#include "Messages.h"

using namespace std;

int main(int argc, char *argv[])
{
	sv_mq doorman("door");
	cout << doorman << endl;
	sv_mq readers_queue("readers");
	cout << readers_queue << endl;
	sv_mq writers_queue("writers");
	cout << writers_queue << endl;
}