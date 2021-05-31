#include "includes.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " philosopher number" << endl;
		exit(2);
	}
	int me = atoi(argv[1]);
	int myID = getpid();
	cout << "I'm the philosopher " << me << " with pid = " << myID << endl;
	mpdu message, *p_messageRequest;
	string request;
	message.setSdu(to_string(me));
	sv_mq f_me(string("Philosopher") + to_string(me));
	sv_mq control("control");

	cout << "Philosopher " << me << " thinking .... (insert string to be able to eat)" << endl;
	string eatingString;
	cin >> eatingString;

	message.setHdr(EAT);
	cout << "message " << message << endl;
	control.send(message);

	p_messageRequest = f_me.receive();

	cout << "Philosopher " << me << " eating .... (insert string to be able to think)" << endl;
	cin >> eatingString;

	message.setHdr(THINK);
	message.setSdu(to_string(me));
	cout << "message " << message << endl;
	control.send(message);
	f_me.del();//eliminates its own queue
}
