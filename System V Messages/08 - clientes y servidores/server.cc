#include <unistd.h>
#include "../primitives/sv_mq.h"
/*   Server   */

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <process-name>" << endl;
    exit(1);
  }
  string processName, auxiliaryAnswer;
  processName = string(argv[1]) + "-" + to_string(getpid());
  cout << "Server " << processName << endl;
  mpdu message, *p_messageAnswer;
  string client, command, payload;
  sv_mq privateQueue(processName.c_str());//server's private queue
  sv_mq control("/control");//controller's queue
  message.setHdr("SRV");//means server
  message.setSdu(processName);
  cout << "Message to controller <" << message << ">" << endl;
  control.send(message);//sends message to the controller with its name
  cout << "...Controller notified ... waiting activation" << endl;
  p_messageAnswer = privateQueue.receive();//waits for a message in its queue with a client's name
  cout << "Received: " << (*p_messageAnswer) << endl;
  client = p_messageAnswer->getSdu();
  free(p_messageAnswer);//eliminates the message received
  cout << "Waiting client on " << privateQueue << endl;
  p_messageAnswer = privateQueue.receive();//waits for client to send something
  cout << "Received: " << (*p_messageAnswer) << endl;
  command = p_messageAnswer->getSdu();
  payload = p_messageAnswer->getSdu();
  free(p_messageAnswer);
  cout << "Execute <" << command << "> over <" << payload << ">" << endl;
  privateQueue.del();
  cout << "Server finished " << endl;
}