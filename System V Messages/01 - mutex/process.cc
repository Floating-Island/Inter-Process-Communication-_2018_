#include "../primitives/sv_mq.h"

using namespace std;

int main()
{
  mpdu *message;
  sv_mq mutex("/mutex");
  cout << "Trying to enter .." << endl;
  message = mutex.receive();
  cout << "... into the critical zone ..." << endl;
  string liberatingString;
  cin >> liberatingString;
  mutex.send(*message);
  cout << "Finished" << endl;
}