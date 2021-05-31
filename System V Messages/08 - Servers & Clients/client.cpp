#include <unistd.h>
#include "../primitives/sv_mq.h"
/* client */

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
	string server, command, payload;
	command = "HACER";
	payload = "Bla bla bla";
	sv_mq processQueue(processName.c_str());//private queue of the client
	sv_mq control("/control");//controller queue
	message.setHdr("CLN");//means that the client sends the message
	message.setSdu(processName);//client puts its name
	cout << "Message to controller <" << message << ">" << endl;
	control.send(message);//sends message to controller
	cout << "...Controller notified ... waiting activation" << endl;
	p_answerMessage = processQueue.receive();//waits for a message to its queue with a server
	cout << "Received: " << (*p_answerMessage) << endl;
	server = p_answerMessage->getSdu();
	free(p_answerMessage);//eliminates the received message
	processQueue.del();
	cout << "Communicating with " << server << endl;
	sv_mq privada(server);//access to the server private queue
	message.setHdr(command);
	message.setSdu(payload);
	privada.send(message);//sends a message to the assigned server
	cout << "Sending " << message << endl;
	cout << "Client finished " << endl;
}