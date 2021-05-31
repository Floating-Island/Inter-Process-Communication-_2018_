#include <iostream>
#include "../primitives/primitives.h"

using namespace std;

int main(int argc, char *argv[])
{
    p_sem mutex("Mutex", 1);
    p_sem access("Access", 1);
    p_shm area("Area");
    mutex.del();
    access.del();
    area.del();
}