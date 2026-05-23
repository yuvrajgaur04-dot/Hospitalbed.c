#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

// Structure to hold Patient details
typedef struct {
    char name[50];
    int age;
    int severity; // 1 (Low) to 5 (Critical Emergency)
    int isAllocated; // 0 = Waiting, 1 = Bed Allocated
} Patient;

// Function Prototypes
void sortPatientsBySeverity(Patient list[], int count);
void allocateBeds(Patient list[], int patientCount, int *beds);
void displayStatus(Patient list[], int count, int beds);

int main() {
    Patient patientList[MAX_PATIENTS];
    int patientCount = 0;
    int availableBeds;

    printf("=== HOSPITAL BED ALLOCATION SYSTEM ===\n\n");
    
    // 1. Input: Number of available beds
    printf("Enter number of available hospital beds: ");
    scanf("%d", &availableBeds);

    // 2. Input: Patient Details
    int choice;
    do {
        printf("\n--- Enter Patient Details ---\n");
        printf("Name: ");
        scanf("%s", patientList[patientCount].name);
        printf("Age: ");
        scanf("%d", &patientList[patientCount].age);
        printf("Severity Level (1-Low to 5-Critical): ");
        scanf("%d", &patientList[patientCount].severity);
        
        patientList[patientCount].isAllocated = 0; // Initially waiting
        patientCount++;

        printf("Add another patient? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);
        
    } while (choice == 1 && patientCount < MAX_PATIENTS);

    // 3. Process: Sort by severity so critical patients come first
    sortPatientsBySeverity(patientList, patientCount);

    // 4. Process: Allocate beds based on priority
    allocateBeds(patientList, patientCount, &availableBeds);

    // 5. Output: Display final allocation status
    displayStatus(patientList, patientCount, availableBeds);

    return 0;
}

// Bubble Sort to arrange patients by severity in descending order
void sortPatientsBySeverity(Patient list[], int count) {
    int i, j;
    Patient temp;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (list[j].severity < list[j+1].severity) {
                // Swap patients
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

// Function to allocate beds to the highest priority patients
void allocateBeds(Patient list[], int patientCount, int *beds) {
    for (int i = 0; i < patientCount; i++) {
        if (*beds > 0) {
            list[i].isAllocated = 1; // Bed given
            (*beds)--; // Reduce available beds count
        } else {
            list[i].isAllocated = 0; // Out of beds
        }
    }
}

// Function to print the final list and remaining beds
void displayStatus(Patient list[], int count, int beds) {
    printf("\n==================================================\n");
    printf("              FINAL ALLOCATION REPORT             \n");
    printf("==================================================\n");
    printf("%-20s %-5s %-10s %-15s\n", "Name", "Age", "Severity", "Bed Status");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-20s %-5d %-10d %-15s\n", 
               list[i].name, 
               list[i].age, 
               list[i].severity, 
               (list[i].isAllocated == 1) ? "ALLOCATED" : "WAITING LIST");
    }
    
    printf("--------------------------------------------------\n");
    printf("Remaining Available Beds in Hospital: %d\n", beds);
    printf("==================================================\n");
}
