#include "../primitives/sv_mq.h"

using namespace std;

int main(){
  mpdu *message;
  string messageString;
  sv_mq messageQueue("/myqueue");
  message= messageQueue.receive();//waits until a message arrives to the queue
  cout<<messageQueue<<endl;
  while (message->getHdr()!="End"){
    cout<<"Received "<<message->getSdu() << endl;
    delete(message);
    message=messageQueue.receive();
    cout<<messageQueue<<endl;
  }
  messageQueue.del();
  cout<<"Finished"<<endl;
}