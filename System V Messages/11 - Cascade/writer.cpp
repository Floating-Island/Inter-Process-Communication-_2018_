#include <iostream>
#include "../primitives/sv_mq.h"

/* Writer */

using namespace std;

int main()
{
    sv_mq adder("adder");

    while (true)
    {
        cout << "Insert message to send:" << endl;
        string letter;
        cin >> letter;
        mpdu message;
        message.setHdr("MSG");//MeSsaGe
        message.setSdu(letter);
        adder.send(message);
        cout << "do you want to keep writing messages? yes/no" << endl;
        string answer;
        cin >> answer;
        if (answer == "no")
        {
            message.setHdr("END");
            adder.send(message);
            break;
        }
    }
    cout << "finished" << endl;
}