#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "ps.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//Turn of the computer
int 
sys_halt(void){
  cprintf("Shutting down ...\n");
  outw (0xB004, 0x0 | 0x2000);
  return 0;
}

//******New Addition P2******
int
sys_date(void)
{
  struct rtcdate* d;

  if(argptr(0, (void*)&d, sizeof(*d)) < 0)
    return -1;
  cmostime(d);
  return 0;
}

//******New Addition P3******
int
sys_getuid(void)
{
  return proc->uid;
}

int
sys_getgid(void)
{
  return proc->gid;
}

int
sys_getppid(void)
{
  if(proc->parent)
    return proc->parent->pid;
  return 0; //if parent is null return zero since there is no parent id
}

int
sys_setuid(void)
{
  int uid;

  if(argint(0, &uid) < 0)
    return -1;

  if(uid <= 0)
      return -1;
  proc->uid = uid;
  return 0;
}

int
sys_setgid(void)
{
  int gid;

  if(argint(0, &gid) < 0)
    return -1;

  if(gid <= 0)
      return -1;
  proc->gid = gid;
  return 0;
}

int
sys_getprocs(void)
{
  struct uproc* table;
  int max;

  if(argint(0, &max) < 0)
    return -1;
  if(argptr(1, (void*)&table, sizeof(*table)) < 0)
    return -1;

  return copy_ptable(max, table);
}

int
sys_setpriority(void)
{
  int pid, value;

  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &value) < 0)
    return -1;
  if(value < 0 || value > 2)
    return -1;
  return set_value(pid, value);
}
