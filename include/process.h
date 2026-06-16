#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>

typedef struct {
    int pid;
    char name[256];
    char state;
    unsigned long utime;
    unsigned long stime;
    long rss; // Resident Set Size (Memory)
} ProcessInfo;

// Function prototypes
int get_process_list(ProcessInfo **list);
void free_process_list(ProcessInfo *list, int count);
void display_processes(ProcessInfo *list, int count);
int kill_process(int pid);
void search_process(ProcessInfo *list, int count, const char *query);
void sort_processes_by_cpu(ProcessInfo *list, int count);

#endif
