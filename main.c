#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patientDetails
{
    char patientID[50];
    char patientFullName[100];
    int patientAge;
    int specialtyID;
    int urgencyLevel;
    int isAdmitted;
    int wardID;
    int admittedDays;
    double baseFee;
    double emergencySurcharge;
    double wardCost;
    double grossTotal;
    double discount;
    double finalPayable;
};
struct patientDetails patients[100];
int patientCount = 0;

int displaySpecialtyID();
void registerNewPatient();
void viewPatientsRecords();
void displayBillingAndReport();

int main()
{
    int choice = 0;
    int specialtyID = 0;

    do {
        printf("\n\t==================================================\n");
        printf("\t    SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM   \n");
        printf("\t==================================================\n");
        printf("\t1. Register New Patient\n");
        printf("\t2. View Patient Records\n");
        printf("\t3. Display Hospital Billing & Reports\n");
        printf("\t4. Exit System\n");
        printf("\t==================================================\n");
        printf("\n\tEnter choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n\t[Error] Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }
        switch (choice) {
            case 1:
                registerNewPatient();
                break;
            case 2:
                viewPatientsRecords();
                break;
            case 3:
                displayBillingAndReport();
                break;
            case 4:
                printf("\t=============================================\n");
                printf("\t  Thank you for using Smart Hospital System!\n");
                printf("\t=============================================\n");
                break;
            default:
                printf("\n\n\t[Error] Invalid choice! Try again.\n");
        }
   }  while (choice != 4);

    return 0;
}



int displaySpecialtyID()
{
    int choice = 0;
    do {
            printf("\n\t    Doctor Specialties Data     \n\n");
            printf("\t 1. General Practice (OPD) - LKR 1500.00\n");
            printf("\t 2. Paediatrics            - LKR 2500.00\n");
            printf("\t 3. Cardiology             - LKR 4500.00\n");
            printf("\t 4. Neurology              - LKR 5000.00\n");

            printf("\n\t Enter choice: ");

    if (scanf("%d", &choice) != 1) {
            printf("\n\n\t[Error] Please enter a valid number!\n\n");
            while (getchar() != '\n');
            choice = 0;
        }
        else if (choice < 1 || choice > 4) {
            printf("\n\n\t[Error] Invalid choice! Choose between 1 and 4.\n\n");
        }
    }
     while (choice < 1 || choice > 4);

    return choice;
}

void registerNewPatient()
{
    if (patientCount >= 100)
    {
        printf("\n\n\tError: Database full!\n");
        return;

    }
    struct patientDetails p;
    printf("\n\tEnter Patient ID  : ");
    scanf("%s", p.patientID);

    printf("\tEnter Patient Name: ");
    scanf("%s", p.patientFullName);

    printf("\tEnter Age         : ");
    scanf("%d", &p.patientAge);

    do {
    printf("\n\t  Urgency Level\n");
    printf("\t1 = Normal \n\t2 = Urgent \n\t3 = Critical");
    printf("\n\tEnter Urgency Level (1 - 3): ");

    if (scanf("%d", &p.urgencyLevel) != 1) {
            while (getchar() != '\n');
            p.urgencyLevel = 0;
        }
        if (p.urgencyLevel < 1 || p.urgencyLevel > 3) {
            printf("\n\t[Error] Invalid choice! .\n");
        }

    } while (p.urgencyLevel < 1 || p.urgencyLevel > 3);

    p.specialtyID = displaySpecialtyID();

     switch (p.specialtyID) {
        case 1: p.baseFee = 1500.00; break;
        case 2: p.baseFee = 2500.00; break;
        case 3: p.baseFee = 4500.00; break;
        case 4: p.baseFee = 5000.00; break;
        default: p.baseFee = 1500.00; break;
    }
    if (p.urgencyLevel == 2) {
        p.emergencySurcharge = p.baseFee * 0.20;
    } else if (p.urgencyLevel == 3) {
        p.emergencySurcharge = p.baseFee * 0.50;
    } else {
        p.emergencySurcharge = 0.00;
    }
    do {
    printf("\n\tIs Patient Admitted to Ward? (1 = Yes, 0 = No): ");
    if (scanf("%d", &p.isAdmitted) != 1) {
            printf("\n\t[Error] Invalid input! Enter 1 or 0.\n");
            while (getchar() != '\n');
            p.isAdmitted = -1;
    }

    } while (p.isAdmitted != 0 && p.isAdmitted != 1);

    if (p.isAdmitted == 1) {
        do {
        printf("\n\t   Ward details\n");
        printf("\t1-General: 3000/day \n\t2-Paediatric: 6000/day \n\t3-Surgical: 12000/day \n\t4-ICU: 25000/day\n");
        printf("\n\tSelect Ward : ");

        if (scanf("%d", &p.wardID) != 1) {
                printf("\n\t[Error] Enter a valid number!\n");
                while (getchar() != '\n');
                p.wardID = 0;
            }
        } while (p.wardID < 1 || p.wardID > 4);

        do {
        printf("\tEnter Days Admitted: ");
        if (scanf("%d", &p.admittedDays) != 1) {
                printf("\n\t[Error] Enter a valid number!\n");
                while (getchar() != '\n');
                p.admittedDays = 0;
            }
        } while (p.admittedDays <= 0);

        double dailyRate = 0.0;
        if (p.wardID == 1) dailyRate = 3000.00;
        else if (p.wardID == 2) dailyRate = 6000.00;
        else if (p.wardID == 3) dailyRate = 12000.00;
        else if (p.wardID == 4) dailyRate = 25000.00;

        p.wardCost = p.admittedDays * dailyRate;
    } else {
        p.wardID = 0;
        p.admittedDays = 0;
        p.wardCost = 0.00;
    }

    p.grossTotal = p.baseFee + p.emergencySurcharge + p.wardCost;

    if (p.patientAge < 5 || p.patientAge > 65) {
        p.discount = p.grossTotal * 0.15;
    } else {
        p.discount = 0.00;
    }
    p.finalPayable = p.grossTotal - p.discount;
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
        printf("\n\t=========================================\n");
        printf("\t       Registered patients records ");
        printf("\n\t=========================================\n");
        printf("\t Record #%d\n", i + 1);
        printf("\tPatient ID      : %s\n", patients[i].patientID);
        printf("\tPatient Name    : %s\n", patients[i].patientFullName);
        printf("\tAge             : %d Years\n", patients[i].patientAge);
        printf("\tUrgency Level   : %d\n", patients[i].urgencyLevel);
        printf("\tBase Bill Amount: LKR %.2f\n", patients[i].finalPayable);

        printf("\tBase Consultation Fee: LKR %.2f\n", patients[i].baseFee);
        printf("\tEmergency Surcharge  : LKR %.2f\n", patients[i].emergencySurcharge);
        printf("\tWard Stay Cost       : LKR %.2f (%d Days)\n", patients[i].wardCost, patients[i].admittedDays);
        printf("\tGross Total Bill     : LKR %.2f\n", patients[i].grossTotal);
        printf("\tAge Subsidy Discount : LKR -%.2f\n", patients[i].discount);
        printf("\tFinal Amount Payable : LKR %.2f\n", patients[i].finalPayable);

  }
}
}
void displayBillingAndReport()
{
    if (patientCount == 0)
    {
        printf("\tNo patients records\n");
        return;
    }
    double totalRevenue = 0.0;
    double totalDiscounts = 0.0;
    double totalSurcharges = 0.0;
    int totalAdmitted = 0;

    for ( int i = 0; i < patientCount; i++)
    {
        totalRevenue += patients[i].finalPayable;
        totalDiscounts += patients[i].discount;
        totalSurcharges += patients[i].emergencySurcharge;
        if (patients[i].isAdmitted == 1 )
            {
                totalAdmitted++;
                }
    }
    printf("\n\t=========================================\n");
    printf("\n\t          Final report\n");
    printf("\n\t=========================================\n");
    printf("\tTotal Patients Registered   : %d\n", patientCount);
    printf("\tTotal Admitted Patients     : %d\n", totalAdmitted);
    printf("\tTotal outpatients           : %d\n", patientCount - totalAdmitted);
    printf("\tTotal Surcharges & Discounts: %.2lf  %.2lf\n", totalSurcharges, totalDiscounts);
    printf("\tTotal Net Revenue           : %.2lf\n", totalRevenue);
    printf("\tAverage Payable per Patient : %.2lf\n", totalRevenue/patientCount);
    printf("\n\t=========================================\n");
}
