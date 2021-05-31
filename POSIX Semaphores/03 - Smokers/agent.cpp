
/*  Agent  */

#include "../primitives/primitives.h"

using namespace std;

// Must be zero and false when initializing
// area is dynamically allocated and cannot be an object nor be initialized

typedef struct
{
    int paper = 0, matches = 0, tobacco = 0;
    bool paperLeft = false, matchesLeft = false, tobaccoLeft = false;
} shar;

int main()
{
    p_sem mutex("Mutex", 1);
    p_sem paper("Paper", 0);
    p_sem tobacco("Tobacco", 0);
    p_sem matches("Match", 0);
    p_shm shArea("shArea");
    shar *sh;
    sh = reinterpret_cast<shar *>(shArea.map(sizeof(shar))); //a struct of type shar is added to shArea's area

    mutex.wait(); //access to shArea blocked
    if (!sh->tobaccoLeft)
    {
        cout << "Agent puts tobacco " << endl;
        sh->tobacco++;
        sh->tobaccoLeft = true;
        if (sh->tobacco == 1)
        {
            tobacco.post();
        }
    }
    if (!sh->paperLeft)
    {
        cout << "Agent puts paper " << endl;
        sh->paper++;
        sh->paperLeft = true;
        if (sh->paper == 1)
        {
            paper.post();
        }
    }
    if (!sh->matchesLeft)
    {
        cout << "Agent puts matches " << endl;
        sh->matches++;
        sh->matchesLeft = true;
        if (sh->matches == 1)
        {
            matches.post();
        }
    }
    mutex.post();
}