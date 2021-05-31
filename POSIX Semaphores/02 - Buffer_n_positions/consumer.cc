#include "Area.h"
#include "../primitives/primitives.h"

using namespace std;

int main()
{
  Area *area;
  p_shm a51("Area51");
  area = static_cast<Area *>(a51.map(sizeof(Area)));
  p_sem prod("A51p", 5);
  p_sem cons("A51c", 0);
  Message data;
  string aux;
  cout << "Consuming  ... (insert a string to continue)" << endl;
  cin >> aux;
  while (true)
  {
    cons.wait();
    if (area->isLast())
      break;
    data = area->retrieve();
    cout << "Read<" << data.getData() << ">" << endl;
    cout << "Consuming  ... (insert a string to continue)" << endl;
    cin >> aux;
    prod.post();
  }
  cout << "Consumer finished" << endl;
  a51.del();
  prod.del();
  cons.del();
}
