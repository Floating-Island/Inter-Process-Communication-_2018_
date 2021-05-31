#include "../primitives/primitives.h"

int main()
{
    p_sem mutex("Mutex", 1);
    p_sem paper("Paper", 0);
    p_sem tobacco("Tobacco", 0);
    p_sem matches("Match", 0);
    p_shm shArea("shArea");
    mutex.del();
    paper.del();
    tobacco.del();
    matches.del();
    shArea.del();
}
