#include "../include/process.h"

int get_process_list(ProcessInfo **list) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;
    int capacity = 10;
    *list = malloc(sizeof(ProcessInfo) * capacity);

    if (!(dir = opendir("/proc"))) {
        perror("opendir /proc");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Only look for directories that are numeric (PIDs)
        if (isdigit(entry->d_name[0])) {
            int pid = atoi(entry->d_name);
            char path[512];
            FILE *fp;

            if (count >= capacity) {
                capacity *= 2;
                *list = realloc(*list, sizeof(ProcessInfo) * capacity);
            }

            // Read process name and state from /proc/[pid]/stat
            snprintf(path, sizeof(path), "/proc/%d/stat", pid);
            fp = fopen(path, "r");
            if (fp) {
                ProcessInfo *p = &((*list)[count]);
                p->pid = pid;
                // Format: pid (name) state ppid ...
                fscanf(fp, "%d (%[^)]) %c", &p->pid, p->name, &p->state);
                
                // Skip to utime (14th field) and stime (15th field)
                // and rss (24th field)
                for(int i=0; i<10; i++) fscanf(fp, "%*s"); // Skip fields
                fscanf(fp, "%lu %lu", &p->utime, &p->stime);
                for(int i=0; i<8; i++) fscanf(fp, "%*s"); // Skip more
                fscanf(fp, "%ld", &p->rss);

                fclose(fp);
                count++;
            }
        }
    }
    closedir(dir);
    return count;
}

void free_process_list(ProcessInfo *list, int count) {
    free(list);
}

int kill_process(int pid) {
    char confirm;
    printf("Are you sure you want to terminate process %d? (y/N): ", pid);
    scanf(" %c", &confirm);
    if (confirm == 'y' || confirm == 'Y') {
        if (kill(pid, 9) == 0) {
            printf("Process %d terminated.\n", pid);
            return 0;
        } else {
            perror("kill");
            return -1;
        }
    }
    printf("Operation cancelled.\n");
    return 0;
}

void search_process(ProcessInfo *list, int count, const char *query) {
    printf("\nSearch Results for '%s':\n", query);
    printf("%-8s %-25s %-10s %-10s\n", "PID", "NAME", "STATE", "MEM(KB)");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strstr(list[i].name, query) || atoi(query) == list[i].pid) {
            printf("%-8d %-25s %-10c %-10ld\n", list[i].pid, list[i].name, list[i].state, list[i].rss * 4); // RSS is in pages, usually 4KB
        }
    }
}

int compare_cpu(const void *a, const void *b) {
    ProcessInfo *p1 = (ProcessInfo *)a;
    ProcessInfo *p2 = (ProcessInfo *)b;
    return (p2->utime + p2->stime) - (p1->utime + p1->stime);
}

void sort_processes_by_cpu(ProcessInfo *list, int count) {
    qsort(list, count, sizeof(ProcessInfo), compare_cpu);
}
