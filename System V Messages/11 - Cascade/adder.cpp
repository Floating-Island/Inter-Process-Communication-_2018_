#include <iostream>
#include "../primitives/sv_mq.h"

/* Adder */

using namespace std;

int main()
{
    sv_mq adder("adder");
    sv_mq printer("printer");
    int contiguous = 0;
    while (true)
    {
        cout << "Waiting on writer message to add it a contiguous number (Currently on " << contiguous << " ) and a space" << endl;
        mpdu *message;
        message = adder.receive();
        if (message->getHdr() == "END")
        {
            cout << "message received from writer to finish this process" << endl;
            cout << "sending message to printer to finish it" << endl;
            printer.send(*message);
            break;
        }
        cout << "received message from writer to modify" << endl;
        string toModify;
        toModify = message->getSdu();
        cout << "message to modify: " << toModify << endl;
        toModify.append(to_string(contiguous));
        string spaceAtEnd = " ";
        spaceAtEnd.append(toModify);
        message->setSdu(spaceAtEnd);
        cout << "message received transformed and ready to send to printer" << endl;
        printer.send(*message);
        cout << "message sent to printer" << endl;
        ++contiguous;
    }
    adder.del();
    cout << "finished" << endl;
}