/* reader */

#include "../primitives/primitives.h"

using namespace std;

typedef struct
{
  int read = 0;
} shar;

int main()
{
  p_sem mutex("Mutex", 1);
  p_sem access("Access", 1);
  shar *sh;
  p_shm area("Area");
  sh = reinterpret_cast<shar *>(area.map(sizeof(shar)));
  cout << "Reader " << getpid() << " tries to access \n";
  mutex.wait();
  if (++sh->read == 1) //the first one to enter blocks entrance to database.
    access.wait();
  // the rest of the readers stays in mutex.wait()
  mutex.post();

  /* Reading opeartion*/
  cout << "Reader " << getpid() << " reading,  insert character to exit\n";
  cin.get();
  mutex.wait();
  if (--sh->read == 0) //the last one unblocks entrance to database.
    access.post();
  mutex.post();
}
