#include <iostream>
#include <string>
#include <cstdlib>

#include "../primitives/sv_mq.h"
#include "Messages.h"

using namespace std;

int main(int argc, char *argv[])
{
  string request, requestingProcess;
  int readers_waiting = 0, readers_active = 0;
  int writers_waiting = 0, writers_active = 0;
  sv_mq doorman("door");
  sv_mq readers_queue("readers");
  sv_mq writers_queue("writers");
  mpdu *requestMessage;
  cout << "readers waiting = " << readers_waiting << "; active readers = " << readers_active << endl;
  cout << "writers waiting = " << writers_waiting << " ;  active writers = " << writers_active << endl;
  cout << "Waiting ..." << endl;
  
  requestMessage = doorman.receive();
  cout << " Received: " << (*requestMessage) << endl;
  request = requestMessage->getHdr();
  while (request != Finishes)
  {
    requestingProcess = requestMessage->getSdu();
    delete requestMessage;
    if (request == Reader_Wants_To_Enter)
    {
      readers_waiting++;
      cout << "Reader wants to enter database " << requestingProcess << endl;
    }
    if (request == Reader_Leaves)
    {
      readers_active--;
      cout << "Reader leaves database " << requestingProcess << endl;
    }
    if (request == Writer_Wants_To_Enter)
    {
      writers_waiting++;
      cout << "Writer wants to enter database" << requestingProcess << endl;
    }
    if (request == Writer_Leaves)
    {
      writers_active--;
      cout << "Writer leaves database " << requestingProcess << endl;
    }
    cout << "readers waiting = " << readers_waiting << "; active readers = " << readers_active << endl;
    cout << "writers waiting = " << writers_waiting << " ;  active writers = " << writers_active << endl;
    //now it operates according to the state
    if ((readers_waiting != 0) and (writers_active == 0))
    {
      while (readers_waiting != 0)
      {
        readers_waiting--;
        readers_active++;
        cout << "Reader enters database ";
        readers_queue.send(mpdu(Reader_Enters, ""));
        cout << "readers waiting = " << readers_waiting << "; active readers = " << readers_active << endl;
      }
    }
    if ((readers_active == 0) and (writers_waiting != 0) and (writers_active == 0))
    {
      writers_waiting--;
      writers_active++;
      cout << "Writer enters database" << endl;
      writers_queue.send(mpdu(Writer_Enters, ""));
    }
    cout << "Waiting ..." << endl;
    cout << "readers waiting = " << readers_waiting << "; active readers = " << readers_active << endl;
    cout << "writers_waiting = " << writers_waiting << " ;  writers_active=" << writers_active << endl;
    requestMessage = doorman.receive();
    cout << " Received: " << (*requestMessage) << endl;
    request = requestMessage->getHdr();
  }
  doorman.del();
  readers_queue.del();
  writers_queue.del();
  cout << "Finished" << endl;
}