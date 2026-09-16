#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patientDetails
{
    char patientID[50];
    char patientFullName[100];
    int patientAge;
    int urgencyLevel;
    double billAmount;
};
struct patientDetails patients[100];
int patientCount = 0;

void displaySpecialtyID();
void registerNewPatient();

int main()
{
    int choice = 0;
    int specialtyID = 0;



    do {
        printf("\n==================================================\n");
        printf("    SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM   \n");
        printf("==================================================\n");
        printf("1. Register New Patient\n");
        printf("2. View Patient Records\n");
        printf("3. Display Hospital Billing & Reports\n");
        printf("4. Exit System\n");
        printf("--------------------------------------------------\n");
        printf("Enter choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n[System] Registration coming in Phase 2!\n");
                registerNewPatient();
                break;
            case 2:
                printf("\n[System] Queue view coming soon!\n");
                break;
            case 3:
                printf("\n[System] Analytics coming soon!\n");
                break;
            case 4:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\n[Error] Invalid choice! Try again.\n");
        }
    } while (choice != 4);





    return 0;
}
void displaySpecialtyID()
{
    int choice = 0;
    printf(" General Practice (OPD): 1\n");
    printf(" Paediatrics           : 2\n");
    printf(" Cardiology            : 3\n");
    printf(" Neurology             : 4\n");
    printf(" Enter your choice: ");
    scanf("%d", &choice);

}
void registerNewPatient()
{
    if (patientCount >= 100)
    {
        printf(" Error: Database full!\n");
        return;

    }
    struct patientDetails p;
    printf("Enter Patient ID: ");
    scanf("%s", p.patientID);

    printf("Enter Age: ");
    scanf("%d", &p.patientAge);
    displaySpecialtyID();

    p.billAmount = 0.0;

    patients[patientCount] = p;
    patientCount++;
    printf("[Success] Patient registered! Total registered: %d\n",
           patientCount);
}
