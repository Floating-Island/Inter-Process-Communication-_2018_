#include "../primitives/sv_mq.h"
/* controller  */

using namespace std;

int main()//connects servers with clients
{
  mpdu serverMessage, clientMessage, *p_requestMessage;
  string request, type, server, client;
  sv_mq control("/control");
  sv_mq servers("/servers");
  sv_mq clients("/clients");
  int serversQuantity = 0, clientsQuantity = 0;
  cout << "Waiting on " << control << endl;
  p_requestMessage = control.receive();
  request = p_requestMessage->getSdu();
  type = p_requestMessage->getHdr();
  cout << type << "->" << request << endl;
  while (type != "END")
  {
    if (type == "SRV")
    {
      servers.send(*p_requestMessage);//stores the server in the servers queue
      serversQuantity++;
    }
    if (type == "CLN")
    {
      clients.send(*p_requestMessage);//stores the client in the clients queue
      clientsQuantity++;
    }
    cout << "Servers = " << serversQuantity << " Clients = " << clientsQuantity << endl;
    free(p_requestMessage);//deletes the message
    if ((clientsQuantity != 0) and (cant_srv != 0))//if there're servers available and clients needing one
    {
      p_requestMessage = servers.receive();
      server = p_requestMessage->getSdu();
      cout << "Server" << (*p_requestMessage) << " with queue " << server << endl;
      clientMessage.setHdr("CTLCL");//control links client
      clientMessage.setSdu(server);
      free(p_requestMessage);
      p_requestMessage = clients.receive();
      client = p_requestMessage->getSdu();
      cout << "Client " << (*p_requestMessage) << " with queue " << client << endl;
      serverMessage.setHdr("CTLSR");//control links server
      serverMessage.setSdu(client);
      free(p_requestMessage);
      sv_mq serverPrivateQueue(server);//has access to the server private queue
      serverPrivateQueue.send(serverMessage);//sends a message to the server with the client's queue
      sv_mq clientPrivateQueue(client);//has access to the client private queue
      clientPrivateQueue.send(clientMessage);//sends a message to the client with the server's queue
      //...server and client communicate without the controller as mediator...
      clientsQuantity--;//client has been attended
      serversQuantity--;//server has served
    }
    cout << "Waiting on " << control << endl;
    p_requestMessage = control.receive();
    request = p_requestMessage->getSdu();
    type = p_requestMessage->getHdr();
    cout << (*p_requestMessage) << endl;
  }
  cout << " Controller finished " << endl;
}