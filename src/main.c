#include "../include/process.h"

void print_menu() {
    printf("\n--- Linux Process Manager ---\n");
    printf("1. List all processes\n");
    printf("2. Sort by CPU usage\n");
    printf("3. Search process (Name/PID)\n");
    printf("4. Terminate process\n");
    printf("5. Refresh\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    ProcessInfo *list = NULL;
    int count = 0;
    int choice;
    char query[256];

    count = get_process_list(&list);
    if (count < 0) return 1;

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                display_processes(list, count);
                break;
            case 2:
                sort_processes_by_cpu(list, count);
                display_processes(list, count);
                break;
            case 3:
                printf("Enter name or PID to search: ");
                scanf("%s", query);
                search_process(list, count, query);
                break;
            case 4:
                printf("Enter PID to terminate: ");
                int pid_to_kill;
                scanf("%d", &pid_to_kill);
                kill_process(pid_to_kill);
                // Refresh list after kill
                free_process_list(list, count);
                count = get_process_list(&list);
                break;
            case 5:
                free_process_list(list, count);
                count = get_process_list(&list);
                printf("List refreshed.\n");
                break;
            case 0:
                free_process_list(list, count);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    free_process_list(list, count);
    return 0;
}
