#include "../primitives/primitives.h"

using namespace std;

int main()
{
  p_sem produce("producer", 1);  //semaphore for producing. unblocked
  p_sem consume("consumer", 0); //semaphore for consuming. blocked
  Message *message;
  p_shm area("area"); //creates a shared memory space, identified as 'area'
  message = reinterpret_cast<Message *>(area.map(BUFSIZ));
  if (message == MAP_FAILED)
  {
    perror("Cannot map area ");
    cerr << "Key<" << area.getKey() << "> " << endl;
    exit(1);
  }
  cout << "Waiting on producer strings..." << endl;

  do
  {
    consume.wait(); //the first time it gets blocked, the semaphore was already 0. Waits on producer
    string res = message->getData();
    cout << "String received from producer:" << endl;
    if (!message->isLast())
    {
      cout << "Received: " << res << endl;
      produce.post(); //allows producer to create a product
    }
  } while (!message->isLast());
  cout << "last string from producer received." << endl;
  produce.del();
  consume.del();
  area.del();
}
