#include "../primitives/sv_mq.h"

using namespace std;

int main()
{
  mpdu message, *p_requestMessage;
  string request;
  message.setSdu("bye");
  sv_mq control("control");
  cout << "waiting on " << control << endl;
  p_requestMessage = control.receive();//receives the name of the process so it's able to communicate with it
  request = p_requestMessage->getSdu();
  cout << (*p_requestMessage) << endl;
  sv_mq private_queue(request);
  cout << "Process stopped at " << private_queue << " insert string to free the process... " << endl;
  string liberatingString;
  cin >> liberatingString;
  private_queue.send(message);//sending message to that private queue
  cout << " Freed" << endl;
}