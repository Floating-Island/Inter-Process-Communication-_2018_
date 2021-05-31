#include "../primitives/sv_mq.h"

using namespace std;
/*sends message to queue*/
int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    cerr << "usage:" << argv[0] << " <message-queue> <message> [f]" << endl;//f sends End as header
    exit(1);
  }
  mpdu message;
  string messageString(argv[2]);
  sv_mq messageQueue(argv[1]);
  if (argc == 4)
    message.setHdr("End");
  else
    message.setHdr("Data");
  message.setSdu(messageString);
  messageQueue.send(message);
  cout << messageQueue << endl;
  cout << "Sent " << message << endl;
}
