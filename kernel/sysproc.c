#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

//Christian Gomez Code Lab 3 Task 1
uint64 kfreepagecount(void);

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//Christian A. Gomez Code

uint64
sys_getprocs(void)
{
  uint64 address; // user pointer to struct stat

  if(argaddr(0, &address) < 0)
    return -1;
  return procinfo(address);
}

//Christian A. Gomez Code
uint64
sys_wait2(void){
  uint64 p1, p2;
  if(argaddr(0, &p1) < 0 || argaddr(1, &p2) < 0){
	return -1;
  }
  return wait2(p1, p2);
}

//Christian Gomez Code Lab 3 Task 1
uint64
sys_freepmem(void){
  int count = kfreepagecount();
  return count*PGSIZE;
}

//Christian Gomez Code lab 4
uint64
sys_sem_init(void){
  uint64 sem_addr;
  int init_val, pshared;

  if(argaddr(0,&sem_addr)<0)
    return -1;
  if(argint(1,&init_val)<0||argint(2,&pshared)<0)
    return -1;
  if(pshared != 1)
    return -1;

  int index = semalloc();
  semtable.sem[index].count = init_val;

  if(copyout(myproc()->pagetable,sem_addr,(char*)&index,sizeof(int)<0)){
    semdealloc(index);
    return -1;
  }
 return 0;
}

uint64
sys_sem_destroy(void){
  uint64 sem_addr;

  if(argaddr(0,&sem_addr)<0)
    return -1;

  int sem_index;

  if(copyin(myproc()->pagetable,(char*)&sem_index,sem_addr,sizeof(int)<0 ))
    return -1;

  semdealloc(sem_index);
  return 0;
}

uint64
sys_sem_wait(void){
  uint64 sem_addr;

  if(argaddr(0,&sem_addr)<0)
    return -1;

  int sem_index;

  if(copyin(myproc()->pagetable,(char*)&sem_index,sem_addr,sizeof(int)<0))
     return -1;

  if(semtable.sem[sem_index].valid==0)
    return -1;


  acquire(&semtable.sem[sem_index].lock);

  while(semtable.sem[sem_index].count == 0)
    sleep((void*)&semtable.sem[sem_index],&semtable.sem[sem_index].lock);
  semtable.sem[sem_index].count -=1;
  release(&semtable.sem[sem_index].lock);
  return 0;
}

uint64
sys_sem_post(void){
  uint64 sem_addr;

  if(argaddr(0,&sem_addr)<0)
    return -1;

  int sem_index;

  if(copyin(myproc()->pagetable,(char*)&sem_index,sem_addr,sizeof(int)<0))
     return -1;

  if(semtable.sem[sem_index].valid == 0)
     return -1;

  acquire(&semtable.sem[sem_index].lock);
  semtable.sem[sem_index].count +=1;
  wakeup((void*)&semtable.sem[sem_index]);
  release(&semtable.sem[sem_index].lock);
  return 0;
}
