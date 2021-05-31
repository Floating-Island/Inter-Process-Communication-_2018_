#include "../primitives/sv_mq.h"

using namespace std;
/*deletes messages in queue*/
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage:" << argv[0] << " <mesage-queue>";
    exit(1);
  }
  sv_mq cola(argv[1]);
  cola.del();
}
