
/*  smoker  */
#include "../primitives/primitives.h"

using namespace std;

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
    sh = reinterpret_cast<shar *>(shArea.map(sizeof(shar)));

    mutex.wait();
    cout << "Smoker " << getpid() << " looks for paper\n";
    while (!sh->paperLeft)
    {
        cout << "Smoker " << getpid() << " waits paper" << endl;
        mutex.post();
        cout << "Waiting ..." << endl;
        paper.wait();
        cout << "...paper arrived." << endl;
        mutex.wait();
    }
    sh->paper--;
    if (sh->paper == 0)
        sh->paperLeft = false;
    cout << "Smoker " << getpid() << " has paper, " << sh->paper << " units left\n";
    cout << "Smoker " << getpid() << " searches for matches\n";
    while (!sh->matchesLeft)
    {
        cout << "Smoker " << getpid() << " waits for matches" << endl;
        mutex.post();
        cout << "Waiting ..." << endl;
        matches.wait();
        cout << "...match arrived." << endl;
        mutex.wait();
    }
    sh->matches--;
    if (sh->matches == 0)
        sh->matchesLeft = false;
    cout << "Smoker " << getpid() << " has matches, " << sh->matches << " units left\n"
         << endl;
    cout << "Smoker " << getpid() << " searches for tobacco\n";
    while (!sh->tobaccoLeft)
    {
        cout << "Smoker " << getpid() << " waits for tobacco";
        mutex.post();
        cout << "Waiting ..." << endl;
        tobacco.wait();
        cout << "...tobacco arrived." << endl;
        mutex.wait();
    }
    sh->tobacco--;
    if (sh->tobacco == 0)
        sh->tobaccoLeft = false;
    cout << "Smoker " << getpid() << " has tobacco, " << sh->tobacco << " units left\n";
    mutex.post();

    cout << "Smoker " << getpid() << " smoking, insert a character to finish\n";
    char c;
    cin >> c;
    cout << "Smoker " << getpid() << " finished\n";
}
