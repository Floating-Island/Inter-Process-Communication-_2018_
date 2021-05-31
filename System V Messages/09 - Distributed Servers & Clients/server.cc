#include <unistd.h>
#include <algorithm>
#include "../primitives/sv_mq.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " <process-name>" << endl;
		exit(1);
	}
	string processName, receivedCommand, assignedClient, req_payload, rsp_payload;
	mpdu message, *p_answerMessage;
	processName = string(argv[1]) + "-" + to_string(getpid());
	cout << "server " << processName << endl;
	sv_mq ownPrivateQueue(processName.c_str());//creates its private queue
	sv_mq servers("/servers");//access to the public server's queue
	message.setHdr("SRV");
	message.setSdu(processName);
	cout << "Registered " << endl;

	servers.send(message);//sends its name to the server's queue so clients are able to communicate with it.
	p_answerMessage = ownPrivateQueue.receive();//waits for a client to communicate with him

	cout << "Received " << (*p_answerMessage) << endl;
	receivedCommand = p_answerMessage->getHdr();
	if (receivedCommand != "CLN")
	{
		cerr << "Not a CLN " << receivedCommand << endl;
		ownPrivateQueue.del();//eliminates its private queue and shutdowns
		exit(2);
	}
	assignedClient = p_answerMessage->getSdu();
	free(p_answerMessage);
	sv_mq cliente(assignedClient);//access to the client's private queue which sent a message to this server's private queue
	cout << "Waiting request on " << ownPrivateQueue << endl;

	p_answerMessage = ownPrivateQueue.receive();//waits a message (command) from the assigned client.

	cout << " Received: " << (*p_answerMessage) << endl;
	receivedCommand = p_answerMessage->getHdr();
	req_payload = p_answerMessage->getSdu();
	free(p_answerMessage);
	cout << "Command =" << receivedCommand << " <" << req_payload << ">" << endl;//muestra el Command recibido
	if (receivedCommand != "REV")//REV means revert the payload message
	{
		cerr << "Unknown command: " << receivedCommand << endl;
		ownPrivateQueue.del();
		exit(2);
	}
	rsp_payload = req_payload;
	reverse(rsp_payload.begin(), rsp_payload.end());//reverts the string
	message.setHdr("ANS");
	message.setSdu(rsp_payload);
	cout << "Sending " << message << " to " << cliente << endl;

	cliente.send(message);//sends answer to the client's requested command (service), string reversal

	cout << "Server finished " << endl;
	ownPrivateQueue.del();//eliminates its private queue
}
