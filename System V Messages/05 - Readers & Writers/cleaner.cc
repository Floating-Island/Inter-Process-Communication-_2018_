#include <iostream>
#include <string>
#include <cstdlib>

#include "../primitives/sv_mq.h"
#include "Messages.h"

using namespace std;

int main()
{
  cout << "General cleaning " << endl;
  sv_mq doorman("door");
  doorman.del();
  cout << "door ..." << endl;
  sv_mq readers_queue("readers");
  readers_queue.del();
  cout << "readers..." << endl;
  sv_mq writers_queue("writers");
  writers_queue.del();
  cout << "writers..." << endl;
}