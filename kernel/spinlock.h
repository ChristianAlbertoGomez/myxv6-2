// Mutual exclusion lock.
#define NSEM 100

struct spinlock {
  uint locked;       // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
};

//Christian Gomez Lab 4 Task 2
struct semaphore{
  struct spinlock lock;
  int count;
  int valid;
};

struct semtab{
  struct spinlock lock;
  struct semaphore sem[NSEM];
};

extern struct semtab semtable;
