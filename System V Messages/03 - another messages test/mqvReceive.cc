#include "../primitives/sv_mq.h"

using namespace std;
/*receives message from queue*/
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "usage:" << argv[0] << " <message-queue> " << endl;
    exit(1);
  }
  mpdu *message;
  string messageString;
  sv_mq queue(argv[1]);
  message = queue.receive();
  cout << "Received " << (*message) << endl;
}