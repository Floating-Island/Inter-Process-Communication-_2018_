#include "../primitives/sv_mq.h"

using namespace std;

int main()
{
  mpdu message;
  sv_mq mutex("/mutex");
  mutex.send(message);
}