#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/procinfo.h"

int
main(void) {
    struct procinfo buf[64];
    int success = getptable(64, (uint64)buf);

    if (!success) {
        printf("Failed to retrieve process table.\n");
        exit(1);
    }

    for (int i = 0; i < 64 && buf[i].pid != 0; i++) {
        printf("PID: %d | PPID: %d | State: %d | Name: %s | Size: %d\n",
               buf[i].pid, buf[i].ppid, buf[i].state,
               buf[i].name, buf[i].memsize);
    }

    exit(0);
}
