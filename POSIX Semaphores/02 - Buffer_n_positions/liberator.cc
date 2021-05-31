#include "Area.h"
#include "../primitives/primitives.h"

int main()
{
  p_shm a51("Area51");
  p_sem prod("A51p", 5);
  p_sem cons("A51c", 0);
  a51.del();
  prod.del();
  cons.del();
}
