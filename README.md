# These are classic IPC problems solved with POSIX semaphores and SYSTEM-V messages

Producer & Consumer:
    A process producer produces an  item y puts it inside a shared area.
    A process consumer retrieves the item from the shared area.

Buffer N-Positions:
    Same as Producer & Consumer but the shared area allows multiple items and the consumer retrieves all of them each time it access the area.

Smokers:
    In a table there're many units of paper, tobacco and matches. There's a group of process that smoke their entire life.
    For each cigarette consumption, one unit of tobacco, paper and match are consumed.
    If any resource (paper, tobacco or matches) is missing, the processes that need them enter a wait state.
    Randomly, an agent appears whom restock the units of resources.

Barber & Customers:
    A barber waits for clients sleeping in a couch of the waiting room.
    When a client arrives, the barber attends him and if more clients arrive in the meantime, they wait on the waiting room, which has a limited capacity.
    The barber attends all its customers before taking another nap.

Readers & Writers:
    A group of readers are allowed to enter a database in conjunction. That's because their operations are non-destructive.
    On the contrary, writers require exclusive access to it.

Philosophers:
    Philosophers spend their life waiting, and eating with chinese sticks in a round table of unlimited spaghetti.
    To eat spaghetti, each one requires two sticks.
    In this exercise, there're 5 philosophers (this can be generalized to have 2*n + 1 philosophers).
    The problem is that there's the same quantity of philosophers as sticks, and each philosopher needs two to eat.
    A philospher thinks, then eats, and then it's hungry.

N-Barrier Guardian:
    There're processes that want to enter the barrier to do something inside. The barrier guardian let's a bunch of them (N) to enter. Once every process leaves the barrier, the guardian allows (or not) a new batch of processes to enter.

Entry In Pairs:
    There're A and B type of processes. Exists a controller that only allows to enter process of type A and B in pairs (a pair consist of a process of type A and another of type B).

## The messages section has two different exercises (and some others missing)

Cascade
    There's a writer, an accumulator and a printer. The printer only prints messages sent from the accumulator. The accumulator adds a consecutive number to a message that receives from the writer and sends it to the printer. The writer writes messages and passes them to the accumulator.

Servers & Clients
    There's a controller, a client and a server. The client tells the controller that it needs a server to communicate with it privately. The server notifies the controller that it exists and awaits a connection with a client. The controller is a mediator between the other two and sets a connection for them.

Distributed Servers & Clients
    Same as Servers & Clients but without a controller between them.
