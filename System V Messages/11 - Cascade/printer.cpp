#include <iostream>
#include "../primitives/sv_mq.h"

/* Printer */

using namespace std;

int main()
{
    sv_mq printer("printer");
    while (true)
    {
        cout << "waiting on adder message to print it" << endl;
        mpdu *message;
        message = printer.receive();
        if (message->getHdr() == "END")
            break;
        cout << "message from adder received" << endl;
        cout << "message: " << message->getSdu() << endl;
    }
    cout << "message from adder received to finish this process" << endl;
    printer.del();
    cout << "finished" << endl;
}

