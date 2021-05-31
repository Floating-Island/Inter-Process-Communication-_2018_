#include "../primitives/primitives.h"
#include "Area.h"

using namespace std;

int main(int argc, char *argv[])
{
  p_sem *philosopherSemaphore[5];
  for (int i = 0; i < 5; i++)
  {
    philosopherSemaphore[i] = new p_sem(string("Philosopher") + to_string(i), 0);
    philosopherSemaphore[i]->del();
  }
}