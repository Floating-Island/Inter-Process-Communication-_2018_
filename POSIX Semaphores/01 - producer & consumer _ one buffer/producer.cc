#include "../primitives/primitives.h"

using namespace std;

int main()
{
  p_sem produce("producer", 1);  //semaphore for producing. unblocked
  p_sem consume("consumer", 0); //semaphore for consuming. blocked
  Message *message;
  p_shm area("area"); //creates a shared memory space, identified as 'area'
  message = reinterpret_cast<Message *>(area.map(BUFSIZ));
  if (message == MAP_FAILED)
  {
    perror("Cannot map area");
    cerr << "Key<" << area.getKey() << "> " << endl;
    exit(1);
  }

  string data;
  do
  {
    produce.wait(); //Blocks semaphore to produce.*1
    cout << "Insert string to store: (end// to finish)" << endl;
    cin >> data;
    if (data.compare("end//"))
    {
      message->setData(data); //updates product's value.
      consume.post();     //unblocks semaphore so consumer is able to read.
    }
  } while (data.compare("end//"));
  message->setData(string(""));
  message->setLast();
  consume.post();
}

/*
*1) At first, it was 1, decrements and continues. 
    In the following operations, it gets blocked so consumer is able to read before the producer modifies the product.

 */