/*  philopher   */
#include "../primitives/primitives.h"
#include "Area.h"

using namespace std;

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

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "I use: " << argv[0] << " as my philosopher number" << endl;
		exit(2);
	}
	int me = atoi(argv[1]);
	int myID = getpid();
	cout << "I'm philosopher " << me << " with pid=" << myID << endl;
	
	p_sem *philosopherSemaphore[5];
	for (int i = 0; i < 5; i++)
	{
		philosopherSemaphore[i] = new p_sem(string("Philosopher") + to_string(i), 0);
	}

	p_sem mutex("Mutex", 1);
	Area *table;
	p_shm areaPhilosophers("AreaPhilosophers");
	table = static_cast<Area *>(areaPhilosophers.map(sizeof(Area)));

	cout << "Philosopher " << me << " thinking .... (insert a string to eat)" << endl;
	string answer;
	cin >> answer;

	mutex.wait(); //stops thinkins, gets hungry
	table->setStatus(me, hungry);
	cout << "Philosopher " << me << " hungry .... " << endl;

	if ((table->getStatus(rightNeighbour(me)) == eating) or
		(table->getStatus(vecinoIzquierdo(me)) == eating))
	{
		mutex.post();
		philosopherSemaphore[me]->wait();
		mutex.wait();
	}

	table->setStatus(me, eating);
	mutex.post();

	cout << "Philosopher " << me << " eating .... (insert string to think and leave)" << endl;
	cin >> answer;

	mutex.wait();
	table->setStatus(me, thinking);
	if ((table->getStatus(rightNeighbour(me)) == hungry) and
		(table->getStatus(rightNeighbour(rightNeighbour((me)))) != eating))
	{
		philosopherSemaphore[rightNeighbour(me)]->post();
	}
	if ((table->getStatus(leftNeighbour(me)) == hungry) and
		(table->getStatus(leftNeighbour(leftNeighbour((me)))) != eating))
	{
		philosopherSemaphore[leftNeighbour(me)]->post();
	}
	mutex.post();
}