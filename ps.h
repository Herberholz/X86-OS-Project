#define MAX   64

struct uproc {
  int pid;
  int uid;
  int gid;
  int ppid;
  char state[16];
  uint size;
  char name[16];
  int priority;
}table[MAX];
