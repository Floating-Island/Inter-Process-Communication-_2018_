#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "../primitives/sv_mq.h"

/* Client */

using namespace std;

int main(int argc, char *argv[])
{
  string to_figaro("CB");//goes from client to barber
  if (argc > 1)
    to_figaro = "end"; // last client
  sv_mq figaro("Barber");
  sv_mq client("Client");
  sv_mq exit_queue("Exit");

  mpdu to_barber, exitShop, *answerMessage;
  to_barber.setSdu("Client");
  to_barber.setHdr(to_figaro);
  cout << to_barber << endl;
  cout << "Figaro! Son qua." << endl
       << "Ehi, Figaro! Son qua." << endl;
  client.send(to_barber);//wants to enter the barber shop
  answerMessage = figaro.receive();//waits for barber to let him in and shave him. Or receive a confirmation of its 'end'
  cout << "Ah, bravo Figaro! Bravo, bravissimo;" << endl
       << "a te fortuna non manchera." << endl;
  delete (answerMessage);
  answerMessage = exit_queue.receive();//waits for barber to finish shaving and be able to exit the shop. Allows 'end' to finish
  cout << " ... presto la barba, presto il biglietto ..." << endl;
}
