#include "../primitives/primitives.h"

using namespace std;

typedef struct
{
    int paper, matches, tobacco;
    bool paperLeft = false, matchesLeft = false, tobaccoLeft = false;
} shar;

int main()
{
    p_shm shArea("shArea");
    shar *sh;
    sh = reinterpret_cast<shar *>(shArea.map(sizeof(shar)));
    cout << "Area state: " << endl
         << boolalpha << "paper " << sh->paper << " " << sh->paperLeft << endl
         << "tobacco " << sh->tobacco << " " << sh->tobaccoLeft << endl
         << "matches " << sh->matches << " " << sh->matchesLeft << endl;
}
