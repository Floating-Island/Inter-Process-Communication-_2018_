#include "includes.h"
/* coordinator */

int leftNeighbour(int me)
{
	int left = me - 1;
	if (left == -1)
		left = 4;
	return left;
}

int rightNeighbour(int me)
{
	int right = me + 1;
	if (right == 5)
		right = 0;
	return right;
}

enum states
{
	thinking,
	hungry,
	eating
};

using namespace std;
int main(int argc, char *argv[])
{
	states philosopherStates[5] = {thinking, thinking, thinking, thinking, thinking};// initial states of philosophers
	mpdu message, *p_messageRequest;//mpdu for messages
	string request;
	int philosopherNumber;
	message.setSdu("continue");//always sends a message to the philosopher to unblock itself and continue execution
	sv_mq *philosophers_queue[5];
	for (int i = 0; i < 5; i++)
	{
		philosophers_queue[i] = new sv_mq(string("Philosopher") + to_string(i));//create a queue for each philosopher
	}
	sv_mq control("control");//general message queue
	p_messageRequest = control.receive();
	request = p_messageRequest->getHdr();
	cout << (*p_messageRequest) << endl;
	while (request != END)
	{
		philosopherNumber = stoi(p_messageRequest->getSdu());//first philosopher in the table
		if (request == EAT)
		{
			philosopherStates[philosopherNumber] = hungry;
			if ((philosopherStates[rightNeighbour(philosopherNumber)] != eating) and
				(philosopherStates[izq(filo)] != com))
			{
				cout << "Philosopher " << philosopherNumber << " is able to eat" << endl;
				philosopherStates[philosopherNumber] = eating;//changes philosopherStates of philosopher
				philosophers_queue[philosopherNumber]->send(message);//sends message to philosopher to unblock itself and continue execution
			}
		}
		if (request == THINK)
		{
			philosopherStates[philosopherNumber] = thinking;//changes philosopherStates of philosopher
			if ((philosopherStates[rightNeighbour(philosopherNumber)] == hungry) and
				(philosopherStates[der(der(filo))] != com))
			{
				cout << "Philosopher " << rightNeighbour(philosopherNumber) << " is able to eat" << endl;
				philosopherStates[rightNeighbour(philosopherNumber)] = eating;//right one is able to eat, changes that philosopherStates to eating
				philosophers_queue[rightNeighbour(philosopherNumber)]->send(message);//sends message to right neighbour so it's able to continue its execution
			}
			if ((philosopherStates[leftNeighbour(philosopherNumber)] == hungry) and
				(philosopherStates[izq(izq(filo))]) != com)
			{
				cout << "Philosopher " << leftNeighbour(philosopherNumber) << " is able to eat" << endl;
				philosopherStates[leftNeighbour(philosopherNumber)] = eating;//left one is able to eat, changes that philosopherStates to eating
				philosophers_queue[leftNeighbour(philosopherNumber)]->send(message);//sends message to left neighbour so it's able to continue its execution
			}
		}
		delete (p_messageRequest);//eliminates the message
		p_messageRequest = control.receive();//receives a new message
		request = p_messageRequest->getHdr();//stores the request
		cout << (*p_messageRequest) << endl;//shows the request
	}
	control.del();//eliminates its queue
}