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

int displaySpecialtyID();
void registerNewPatient();
void viewPatientsRecords();

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
                registerNewPatient();
                break;
            case 2:
                viewPatientsRecords();
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
int displaySpecialtyID()
{
    int choice = 0;
    printf(" General Practice (OPD): 1\n");
    printf(" Paediatrics           : 2\n");
    printf(" Cardiology            : 3\n");
    printf(" Neurology             : 4\n");
    printf(" Enter your choice: ");
    scanf("%d", &choice);
    return choice;

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

    printf("Enter Patient Name: ");
    scanf("%s", p.patientFullName);

    printf("Enter Age: ");
    scanf("%d", &p.patientAge);

    p.urgencyLevel = displaySpecialtyID();

    p.billAmount = 1500.0;

    patients[patientCount] = p;
    patientCount++;
    printf("[Success] Patient registered! Total registered: %d\n",
           patientCount);
}
void viewPatientsRecords()
{
    if (patientCount == 0)
    {
        printf("No patient records found\n");
    }
  else
  {
      for (int i = 0; i < patientCount ; i++)
      {
      printf(" Registered patients records \n");
      printf(" Record #%d\n", i + 1);
        printf("Patient ID      : %s\n", patients[i].patientID);
        printf("Patient Name    : %s\n", patients[i].patientFullName);
        printf("Age             : %d Years\n", patients[i].patientAge);
        printf("Urgency Level   : %d\n", patients[i].urgencyLevel);
        printf("Base Bill Amount: LKR %.2f\n", patients[i].billAmount);

  }
}
}
