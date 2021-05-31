#include "../primitives/sv_mq.h"

using namespace std;
/*prints queue*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "usage:" << argv[0] << " <message-queue>" << endl;
        exit(1);
    }
    sv_mq messageQueue(argv[1]);
    cout << messageQueue << endl;
}
