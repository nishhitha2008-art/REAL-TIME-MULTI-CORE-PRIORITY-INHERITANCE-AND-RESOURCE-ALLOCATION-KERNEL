#include <stdio.h>

#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3

typedef struct {
    char name;
    int originalPriority;
    int currentPriority;
    int resourceLocked;
    int completed;
} Task;

void displayTask(Task t) {
    printf("Task %c | Original Priority: %d | Current Priority: %d\n",
           t.name, t.originalPriority, t.currentPriority);
}

int main() {
    Task L = {'L', LOW_PRIORITY, LOW_PRIORITY, 0, 0};
    Task M = {'M', MEDIUM_PRIORITY, MEDIUM_PRIORITY, 0, 0};
    Task H = {'H', HIGH_PRIORITY, HIGH_PRIORITY, 0, 0};
    int resourceLocked = 0;

    printf("======================================\n");
    printf("   PRIORITY INHERITANCE PROTOCOL (PIP)\n");
    printf("======================================\n\n");

    printf("Initial Task Priorities:\n");
    displayTask(L);
    displayTask(M);
    displayTask(H);

    printf("\n--- EXECUTION STARTS ---\n");

    /* Step 1: Low-priority task locks resource */
    printf("1. Task L locks the shared resource.\n");
    resourceLocked = 1;
    L.resourceLocked = 1;

    /* Step 2: High-priority task requests resource */
    printf("\n2. Task H requests the shared resource.\n");
    if (resourceLocked) {
        printf(" -> Task H is blocked because Task L holds the resource.\n");
    }

    /* Step 3: Apply Priority Inheritance Protocol */
    printf("\n3. Applying Priority Inheritance Protocol.\n");
    L.currentPriority = H.currentPriority;
    printf(" -> Task L inherits Task H's priority.\n");
    displayTask(L);

    /* Step 4: Medium task cannot preempt boosted Task L */
    printf("\n4. Task M becomes ready for execution.\n");
    if (L.currentPriority > M.currentPriority) {
        printf(" -> Task M cannot preempt Task L (Priority %d > %d).\n", L.currentPriority, M.currentPriority);
        printf(" -> Task L continues its critical section.\n");
    }

    /* Step 5: Low task completes and releases resource */
    printf("\n5. Task L completes its critical section.\n");
    resourceLocked = 0;
    L.resourceLocked = 0;
    L.completed = 1;
    printf(" -> Task L releases the shared resource.\n");

    /* Step 6: Restore original priority */
    printf("\n6. Task L restores its original priority.\n");
    L.currentPriority = L.originalPriority;
    displayTask(L);

    /* Step 7: High task resumes */
    if (!resourceLocked) {
        printf("\n7. Task H acquires the shared resource.\n");
        H.resourceLocked = 1;
        printf(" -> Task H executes its critical section.\n");
        H.resourceLocked = 0;
        H.completed = 1;
        printf(" -> Task H releases the shared resource.\n");
    }

    printf("\n=== FINAL STATUS ===\n");
    printf("Task L: %s\n", L.completed ? "Completed" : "Pending");
    printf("Task M: %s\n", M.completed ? "Completed" : "Pending");
    printf("Task H: %s\n", H.completed ? "Completed" : "Pending");

    printf("\nResult: Priority Inheritance Protocol demonstrated.\n");
    return 0;
}