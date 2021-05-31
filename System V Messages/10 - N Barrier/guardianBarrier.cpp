#include <unistd.h>
#include "../primitives/sv_mq.h"
#include "maximumCapacity.hpp"
/* guardian del Barrier */

using namespace std;

int main(int argc, char *argv[])
{
	int me;
	me = getpid();
	char auxiliaryName[20];
	sprintf(auxiliaryName, "%d", static_cast<int>(getpid())); //the to_string before c++11
	string processName(auxiliaryName);
	sv_mq guardianPrivateQueue(processName.c_str()); //queue is private, only the guardian has access to it
	sv_mq entranceToBarrier("barrierEntrance");
	sv_mq insideBarrier("barrier");

	cout << "guardian " << me << " protect the barrier" << endl;

	int inBarrier = 0;
	while (true)
	{
		cout << "guardian " << me << " wait messages to enter the barrier" << endl;
		mpdu *message = entranceToBarrier.receive();
		++inBarrier; //increases the processes quantity inside the barrier
		insideBarrier.send(*message);
		cout << "The process " << message->getSdu() << " wants to enter the barrier" << endl;
		if (inBarrier == BARRIER_MAXIMUM_QUANTITY)
		{
			cout << " maximum number of processes inside barrier has been reached" << endl;
			for (int login = 0; login < BARRIER_MAXIMUM_QUANTITY; ++login)
			{
				cout << "I allow to enter " << (login + 1) << " processes inside the barrier" << endl;
				mpdu *outMessage = insideBarrier.receive();
				string process = outMessage->getSdu();
				sv_mq processPrivateQueue(process);
				mpdu privateMessage;
				privateMessage.setHdr("GDN");//GuarDiaN
				privateMessage.setSdu(processName);
				cout << "guardian " << me << " send my private queue so requesting processes are able to enter the barrier." << endl;
				processPrivateQueue.send(privateMessage);
			}
			for (int logout = 0; logout < BARRIER_MAXIMUM_QUANTITY; ++logout)
			{
				mpdu *outMessage = guardianPrivateQueue.receive();
				--inBarrier; //decreases the number of processes inside the barrier
				cout << "logging out " << (logout + 1) << " processes from barrier" << endl;
			}
			cout << "Do I let in another batch? yes/no:" << endl;
			string userAnswer;
			cin >> userAnswer;
			if (userAnswer == "no")
				break;
		}
	}
	guardianPrivateQueue.del();
	entranceToBarrier.del();
	insideBarrier.del();
}