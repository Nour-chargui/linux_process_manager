#include "../include/process.h"

void display_processes(ProcessInfo *list, int count) {
    printf("\n%-8s %-25s %-10s %-10s\n", "PID", "NAME", "STATE", "MEM(KB)");
    printf("------------------------------------------------------------\n");
    // Show top 20 processes
    int limit = (count > 20) ? 20 : count;
    for (int i = 0; i < limit; i++) {
        printf("%-8d %-25s %-10c %-10ld\n", list[i].pid, list[i].name, list[i].state, list[i].rss * 4);
    }
    if (count > 20) {
        printf("... and %d more processes.\n", count - 20);
    }
}
