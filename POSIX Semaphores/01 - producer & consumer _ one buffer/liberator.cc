#include "../primitives/primitives.h"

using namespace std;
//frees memory
int main()
{
  p_sem produce("producer", 1);
  p_sem consume("consumer", 0);
  p_shm area("area");
  produce.del();
  consume.del();
  area.del();
}