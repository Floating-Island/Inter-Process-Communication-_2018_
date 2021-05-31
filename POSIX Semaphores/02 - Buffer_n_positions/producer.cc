#include "Area.h"
#include "../primitives/primitives.h"

using namespace std;

int main()
{
  Area *area;
  p_shm a51("Area51");
  area = static_cast<Area *>(a51.map(sizeof(Area)));
  p_sem prod("A51p", 5); //5 is the size of the area, the buffer
  p_sem cons("A51c", 0);
  string reads;
  cout << "Insert a string" << endl;
  while (cin >> reads)
  {
    prod.wait();
    cout << "Inserting " << reads << endl;
    area->put(Message(reads));
    cons.post();
    cout << "Insert a string" << endl;
  }
  area->setLast();
  cons.post();
  cout << "Producer finished" << endl;
}
