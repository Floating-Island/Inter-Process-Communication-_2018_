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
    cerr << "Usage: " << argv[0] << " <process-name>" << endl;
    exit(1);
  }
  char auxiliaryName[20];
  sprintf(auxiliaryName, "%d", static_cast<int>(getpid()));
  string name(auxiliaryName), auxiliaryAnswer;
  name = argv[1] + ("-" + name);
  cout << "Reader " << name << endl;
  mpdu message, *answerMessage;
  sv_mq doorman("door");
  sv_mq readers_queue("readers");
  message.setHdr(Reader_Wants_To_Enter);
  message.setSdu(name);
  cout << "Asking permission to enter the database" << endl;
  doorman.send(message);
  
  // Entry to database
  answerMessage = readers_queue.receive();
  auxiliaryAnswer = answerMessage->getSdu();
  delete answerMessage;

  cout << "In database, insert string to leave" << endl;
  cin >> auxiliaryAnswer;
  message.setHdr(Reader_Leaves);
  doorman.send(message);
  // leaves the database

  if (argc == 3)
    doorman.send(mpdu(Finishes, ""));
  cout << "Finished" << endl;
}