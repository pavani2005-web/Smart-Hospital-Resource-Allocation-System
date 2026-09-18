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
                displayBillingAndReport();
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
    printf(" 1. General Practice (OPD) - LKR 1500.00\n");
    printf(" 2. Paediatrics            - LKR 2500.00\n");
    printf(" 3. Cardiology             - LKR 4500.00\n");
    printf(" 4. Neurology              - LKR 5000.00\n");
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

    printf("Enter Urgency Level (1 = Normal, 2 = Urgent, 3 = Critical): ");
    scanf("%d", &p.urgencyLevel);

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

    // 3. Ward Admission
    printf("Is Patient Admitted to Ward? (1 = Yes, 0 = No): ");
    scanf("%d", &p.isAdmitted);

    if (p.isAdmitted == 1) {
        printf("Select Ward (1-General: 3000/day, 2-Paediatric: 6000/day, 3-Surgical: 12000/day, 4-ICU: 25000/day): ");
        scanf("%d", &p.wardID);
        printf("Enter Days Admitted: ");
        scanf("%d", &p.admittedDays);

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
      printf(" Registered patients records \n");
      printf(" Record #%d\n", i + 1);
        printf("Patient ID      : %s\n", patients[i].patientID);
        printf("Patient Name    : %s\n", patients[i].patientFullName);
        printf("Age             : %d Years\n", patients[i].patientAge);
        printf("Urgency Level   : %d\n", patients[i].urgencyLevel);
        printf("Base Bill Amount: LKR %.2f\n", patients[i].finalPayable);

        printf("Base Consultation Fee: LKR %.2f\n", patients[i].baseFee);
        printf("Emergency Surcharge  : LKR %.2f\n", patients[i].emergencySurcharge);
        printf("Ward Stay Cost       : LKR %.2f (%d Days)\n", patients[i].wardCost, patients[i].admittedDays);
        printf("Gross Total Bill     : LKR %.2f\n", patients[i].grossTotal);
        printf("Age Subsidy Discount : LKR -%.2f\n", patients[i].discount);
        printf("Final Amount Payable : LKR %.2f\n", patients[i].finalPayable);

  }
}
}
void displayBillingAndReport()
{
    if (patientCount == 0)
    {
        printf(" No patients records\n");
        return;
    }
    double totalRevenue = 0.0;
    double totalDiscounts = 0.0;
    double totalSurcharges = 0.0;
    int totalAdmitted = 0.0;

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
    printf(" Final report\n");
    printf("Total Patients Registered: %d\n", patientCount);
    printf("Total Admitted Patients: %d\n", totalAdmitted);
    printf("Total outpatients: %d\n", patientCount - totalAdmitted);
    printf("Total Surcharges & Discounts: %.2lf  %.2lf\n", totalSurcharges, totalDiscounts);
    printf("Total Net Revenue: %.2lf\n", totalRevenue);
    printf("Average Payable per Patient: %.2lf\n", totalRevenue/patientCount);
}
