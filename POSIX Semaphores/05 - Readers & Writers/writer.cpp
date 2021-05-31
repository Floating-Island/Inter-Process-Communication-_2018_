/*  writer   */

#include "../primitives/primitives.h"

using namespace std;

int main()
{
	p_sem access("Access", 1);
	cout << "Writer " << getpid() << " tries to enter" << endl;
	access.wait(); //enters if no readers in area.
	cout << "Writer " << getpid()
		 << " inside, insert a character to exit" << endl;
	cin.get();
	access.post(); //leaves the database
}
