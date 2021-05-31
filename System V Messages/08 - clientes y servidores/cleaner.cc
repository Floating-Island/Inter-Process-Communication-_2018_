#include "../primitives/sv_mq.h"
/* cleaner  */
using namespace std;

int main()
{
  sv_mq control("control");
  sv_mq servers("servers");
  sv_mq clients("clients");
  mpdu endPDU;
  endPDU.setHdr("END");
  endPDU.setSdu("Bye");
  control.send(endPDU);
  servers.del();
  clients.del();
  control.del();
}
