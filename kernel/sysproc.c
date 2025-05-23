#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "uproc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}


uint64
sys_getppid(void)
{
  struct proc *p = myproc();
  if (p->parent)
    return p->parent->pid;
  else
    return -1;  // in case there's no parent (very unlikely)
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
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
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

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
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

  argint(0, &pid);
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
extern struct proc proc[NPROC];
uint64 sys_getptable(void)
{
  char *states[] = {
    [UNUSED]   = "UNUSED",
    [USED]     = "USED",
    [SLEEPING] = "SLEEPING",
    [RUNNABLE] = "RUNNABLE",
    [RUNNING]  = "RUNNING",
    [ZOMBIE]   = "ZOMBIE"
};

    int n;
    uint64 uaddr;

    argint(0, &n);
    argaddr(1, &uaddr);
    struct uproc up[n];
    int count = 0;

    for (int i = 0; i < NPROC && count < n; i++) {
        struct proc *p = &proc[i];
        if (p->state != UNUSED) {
            up[count].pid = p->pid;
            up[count].ppid = p->parent ? p->parent->pid : 0;
            safestrcpy(up[count].state, states[p->state], sizeof(up[count].state));
            safestrcpy(up[count].name, p->name, sizeof(p->name));
            up[count].sz = p->sz;
            count++;
        }
    }

    if (copyout(myproc()->pagetable, uaddr, (char *)up, count * sizeof(struct uproc)) < 0)
        return 0;

    return 1;
}



////////////////////////////////////////nm
extern int sched_mode; // define this in proc.c

uint64
sys_schedtest(void)
{
  int mode;
  argint(0, &mode);
  sched_mode = mode;
  return 0;
}

////////////////////////////////////////nm
uint64 sys_setpriority(void) {
  int pri;
  argint(0, &pri);

  if(pri < 1 || pri > 10)
    return -1;

  struct proc *p = myproc();
  p->priority = pri;
  return 0;
}


uint64 sys_setsched(void) {
  int mode;
  argint(0, &mode);

  if(mode < SCHED_ROUND_ROBIN || mode > SCHED_PRIORITY)
    return -1;

  sched_mode = mode;
  return 0;
}
