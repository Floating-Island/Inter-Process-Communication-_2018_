#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "../primitives/sv_mq.h"

using namespace std;

int main(int argc, char *argv[])
{
	sv_mq figaro("Barber");
	sv_mq client("Client");
	sv_mq exit_queue("Exit");
	mpdu to_client, exitShop, *answerMessage;
	string action, answer;
	to_client.setHdr("BC");//from barber to client
	to_client.setSdu("inside");
	exitShop.setSdu("Done");
	cout << "Presto a bottega che l'alba e gia." << endl
		 << "Presto! La la la la la la la LA!" << endl;
	answerMessage = client.receive();//waits to receive a client
	
	action = answerMessage->getHdr();//could be CB or 'end'
	while (action != "end")
	{

		figaro.send(to_client);//tells the client to come in
		cout << "Figaro qua, Figaro la, Figaro qua, Figaro la," << endl
			 << "Figaro su, Figaro giu, Figaro su, Figaro giu" << endl
			 << ".....(enter a string to finish shaving)" << endl;
		cin >> answer;
		exit_queue.send(exitShop);//tells the client that has finished shaving
		cout << "Uno alla volta, per carità!" << endl;
		answerMessage = client.receive();//waits for a new client
		
		action = answerMessage->getHdr();//could be CB or 'end'
	}
	figaro.send(to_client);//to free the client that asked for 'end'
	cout << "Figaro qua, Figaro la, Figaro qua, Figaro la," << endl
		 << "Figaro su, Figaro giu, Figaro su, Figaro giu" << endl
		 << ".....(enter a string to finish attending)" << endl;
	cin >> answer;
	exit_queue.send(exitShop);//allows 'end' to finish
	exit_queue.del();
	figaro.del();
	client.del();
	cout << "Pronto prontissimo son come il fulmine:" << endl
		 << "Sono il factotum della citta ..." << endl;
}
