#include <unistd.h>
#include "../primitives/sv_mq.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <process-name>" << endl;
    exit(1);
  }
  char auxiliaryName[20];
  sprintf(auxiliaryName, "%d", static_cast<int>(getpid())); // el to_string de antes del c++11
  string processName(auxiliaryName), auxiliaryAnswer;
  processName = argv[1] + ("-" + processName); //nombreProceso=argv[1]+"-"+to_string(getpid())
  cout << "Process " << processName << endl;
  mpdu message, *p_answerMessage;
  
  sv_mq private_queue(processName.c_str());//queue is private, only this process is able to access it.
  sv_mq control("/control");
  message.setSdu(processName);
  cout << "Message <" << message << ">" << endl;
  control.send(message);//sending the name of the process to the controller. That way, it will have the name of the private queue
  cout << "...Control notified" << endl;
  p_answerMessage = private_queue.receive();//waiting for a private message
  cout << "...Freed" << endl;
  private_queue.del();
}