#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "../primitives/sv_mq.h"
#include "Messages.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <processs-name>" << endl;
    exit(1);
  }
  char auxiliaryName[20];
  sprintf(auxiliaryName, "%d", static_cast<int>(getpid()));
  string processName(auxiliaryName), auxiliaryAnswer;
  processName = argv[1] + ("-" + processName);
  cout << "Writer " << processName << endl;
  mpdu message, *answerMessage;
  sv_mq doorman("door");
  sv_mq writers_queue("writers");
  message.setHdr(Writer_Wants_To_Enter);
  message.setSdu(processName);
  cout << "Asking permission to enter the database" << endl;
  doorman.send(message);
  
  // Entry to database
  answerMessage = writers_queue.receive();
  auxiliaryAnswer = answerMessage->getSdu();
  delete answerMessage;

  cout << "Inside database, insert string to leave " << endl;
  cin >> auxiliaryAnswer;
  message.setHdr(Writer_Leaves);
  doorman.send(message);
  // leaves the database

  if (argc == 3)
    doorman.send(mpdu(Finishes, ""));
  cout << "Finished" << endl;
}