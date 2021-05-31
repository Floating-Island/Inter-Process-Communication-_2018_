#include <iostream>
#include <unistd.h>
#include "../primitives/sv_mq.h"

/* Process */

using namespace std;

int main(int argc, char *argv[])
{
	int me;
	me = getpid();
	char auxiliaryName[20];
	sprintf(auxiliaryName, "%d", static_cast<int>(getpid())); //the to_string before c++11
	string processName(auxiliaryName);
	sv_mq processPrivateQueue(processName.c_str()); //queue is private, only the process has access to it
	sv_mq entranceToBarrier("barrierEntrance");

	cout << "me, " << processName << " want to get inside the barrier..." << endl;
	mpdu inMessage;
	inMessage.setHdr("PRC");//PRoCess
	inMessage.setSdu(processName);
	entranceToBarrier.send(inMessage);
	mpdu *answerMessage = processPrivateQueue.receive();
	cout << "me, " << processName << " enter the barrier..." << endl;
	cout << "me, " << processName << " do something inside the barrier..." << endl;

	cout << "me, " << processName << " want to leave the barrier..." << endl;
	sv_mq guardianPrivateQueue(answerMessage->getSdu());
	mpdu outMessage;
	outMessage.setHdr("PRC");
	outMessage.setSdu(processName);
	cout << "me, " << processName << " notify the guardian that I leave the barrier..." << endl;
	guardianPrivateQueue.send(outMessage);
	cout << "me, " << processName << " leave the barrier..." << endl;
	processPrivateQueue.del();
}