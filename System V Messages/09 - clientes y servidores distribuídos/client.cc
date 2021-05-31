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
	string processName, auxiliaryAnswer;
	processName = string(argv[1]) + "-" + to_string(getpid());
	cout << "client " << processName << endl;
	mpdu message, *p_answerMessage;
	string server, command, payload, payload_answer;
	command = "REV";//revert message
	payload = "SuperNiceChocolero";//string to revert
	// 							searches for a server
	sv_mq ownPrivateQueue(processName.c_str());//client's private queue
	sv_mq servers("/servers");//access to the servers queue
	message.setHdr("CLN");//so the one receiving it is able to access the client's queue (when sending to a server)
	message.setSdu(processName);//adds its name to the message to send it to the assigned server
	cout << "Waits for a server " << endl;

	p_answerMessage = servers.receive();//waits for a server available in the server's queue

	cout << "Received: " << (*p_answerMessage) << endl;
	server = p_answerMessage->getSdu();//now it has the server's name (private queue)
	free(p_answerMessage);//eliminates the answer
	//							Communicates with the server
	sv_mq mi_server(server);//access to the assigned server's private queue
	cout << "I identify myself " << message << " to " << mi_server << endl;

	mi_server.send(message);//sends a message to the server so it's able to communicate with it.

	message.setHdr(command);//to ask for services (revert the message sent in this case)
	message.setSdu(payload);
	cout << "I ask a service " << message << " to " << mi_server << endl;

	mi_server.send(message);//sends a message to the server asking for a service. The server already has its private queue.

	cout << "Waiting anser on " << ownPrivateQueue << endl;

	p_answerMessage = ownPrivateQueue.receive();//waits a message in its private queue from the server (the answer to the message sent)

	cout << "Received: " << (*p_answerMessage) << endl;
	payload_answer = p_answerMessage->getSdu();
	free(p_answerMessage);//eliminates the message
	cout << "Received answer: <" << payload_answer << ">" << endl;//shows the answer
	ownPrivateQueue.del();//eliminates its private queue
	cout << "Client finished" << endl;
}
