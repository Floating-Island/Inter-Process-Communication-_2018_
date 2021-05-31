#include "../primitives/sv_mq.h"

using namespace std;

int main(){
  mpdu message;
  string stringMessage;
  sv_mq messageQueue("/myqueue");//creates message queue
  cout<<"Send ... ";
  while (cin>>stringMessage){
    message.setHdr("Data");//message header to differentiate different types of messages
    message.setSdu(stringMessage);//message sdu (content)
    messageQueue.send(message);//sends message to queue
    cout<<messageQueue<<endl;
    cout<<"...Sent, \nSend ... ";
  }
  message.setHdr("End");
  messageQueue.send(message);
  cout<<"End"<<endl;
}