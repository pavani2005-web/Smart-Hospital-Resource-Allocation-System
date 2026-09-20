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
    int bedNumber;
    float waitTime;
};
struct patientDetails patients[100];

int bedOccupancy[4][20] = {0};
int wardCapacities[4] = {20, 10, 10, 5};
int specialtyQueue[4] = {0};
int specialtyAvgTimes[4] = {15, 20, 30, 30};
int specialtyDailyCaps[4] = {30, 20, 12, 10};

int patientCount = 0;

int displaySpecialtyID();
void registerNewPatient();
void viewPatientsRecords();
void displayBillingAndReport();
void sortByUrgency();

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
            printf("\n\tError. Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }
        switch (choice) {
            case 1:
                registerNewPatient();
                break;
            case 2:
                sortByUrgency();
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
                printf("\n\n\tError. Invalid choice. Try again.\n");
          }
   }  while (choice != 4);

    return 0;
}
int displaySpecialtyID()
{
    int choice = 0;
    do {
            printf("\n\t    Doctor Specialties Data     \n\n");
            printf("\t 1. General Practice (OPD) - LKR 1500.00 (Capacity: 30)\n");
            printf("\t 2. Paediatrics            - LKR 2500.00 (Capacity: 20)\n");
            printf("\t 3. Cardiology             - LKR 4500.00 (Capacity: 12)\n");
            printf("\t 4. Neurology              - LKR 5000.00 (Capacity: 10)\n");
            printf("\n\t Enter choice: ");

    if (scanf("%d", &choice) != 1) {
            printf("\n\n\tError. Please enter a valid number!\n\n");
            while (getchar() != '\n');
            choice = 0;
        }
        else if (choice < 1 || choice > 4) {
            printf("\n\n\tError. Invalid choice.\n\n");
        }
        else if (specialtyQueue[choice - 1] >= specialtyDailyCaps[choice - 1]) {
            printf("\tLimit reached. Specialty is full for today.\n");
            choice = 0;}
    }
     while (choice < 1 || choice > 4);

    return choice;}

void registerNewPatient()
{
    int assignedBed = -1;
    if (patientCount >= 100)
    {
        printf("\n\n\tData Base full. No space.\n");
        return;
    }
    struct patientDetails p;
    printf("\n\tEnter Patient ID  : ");
    scanf(" %[^\n]", p.patientID);

    printf("\tEnter Patient Name: ");
    scanf(" %[^\n]", p.patientFullName);

   do {
    printf("\tEnter Age         : ");
    if (scanf("%d", &p.patientAge) != 1) {
        printf("\n\tError. Enter a valid number!\n");
        while (getchar() != '\n');
        p.patientAge = -1;
    }
    } while (p.patientAge < 0 || p.patientAge > 120);


    do {
    printf("\n\t   Urgency Level\n");
    printf("\t1 = Normal \n");
    printf("\t2 = Urgent \n");
    printf("\t3 = Critical\n");
    printf("\n\tEnter Urgency Level (1 - 3): ");

    if (scanf("%d", &p.urgencyLevel) != 1) {
            while (getchar() != '\n');
            p.urgencyLevel = 0;
        }
        if (p.urgencyLevel < 1 || p.urgencyLevel > 3) {
            printf("\n\tError. Invalid choice.\n");
        }

    } while (p.urgencyLevel < 1 || p.urgencyLevel > 3);
    int specialtyLimit = -1;
    do {
        p.specialtyID = displaySpecialtyID();
        specialtyLimit = p.specialtyID - 1;

        if (specialtyQueue[specialtyLimit] >= specialtyDailyCaps[specialtyLimit]) {
            printf("\n\tError. Specialty daily limit reached. Choose another.\n");
            specialtyLimit = -1;
        }
    } while (specialtyLimit == -1);

    p.waitTime = (float)(specialtyQueue[specialtyLimit] * specialtyAvgTimes[specialtyLimit]);
    specialtyQueue[specialtyLimit]++;

     switch (p.specialtyID) {
        case 1:
            p.baseFee = 1500.00;
            break;
        case 2:
             p.baseFee = 2500.00;
             break;
        case 3:
            p.baseFee = 4500.00;
            break;
        case 4:
            p.baseFee = 5000.00;
            break;
        default:
            p.baseFee = 1500.00;
            break;
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
            printf("\n\t[Error] Invalid input Enter 1 or 0.\n");
            while (getchar() != '\n');
            p.isAdmitted = -1;
        }
    } while (p.isAdmitted != 0 && p.isAdmitted != 1);

    if (p.isAdmitted == 1) {
        do {
            printf("\n\t    Ward details\n");
            printf("\t1. General: 3000 per day \n");
            printf("\t2. Paediatric: 6000 per day \n");
            printf("\t3. Surgical: 12000 per day \n");
            printf("\t4. ICU: 25000/day\n");
            printf("\n\tSelect a Ward : ");

            if (scanf("%d", &p.wardID) != 1) {
                printf("\n\tError. Enter a valid number\n");
                while (getchar() != '\n');
                p.wardID = 0;
            }
        } while (p.wardID < 1 || p.wardID > 4);

        int wardLimit = p.wardID - 1;
        for (int b = 0; b < wardCapacities[wardLimit]; b++) {
            if (bedOccupancy[wardLimit][b] == 0) {
                bedOccupancy[wardLimit][b] = 1;
                assignedBed = b + 1;
                break;
            }
        }

        if (assignedBed == -1) {
            printf("\n\tWard is full. Registered as outpatient.\n");
            p.isAdmitted = 0;
            p.wardID = 0;
            p.bedNumber = 0;
            p.admittedDays = 0;
            p.wardCost = 0.00;
        } else {
            p.bedNumber = assignedBed;
            do {
                printf("\tEnter Days Admitted: ");
                if (scanf("%d", &p.admittedDays) != 1) {
                    printf("\n\tError. Enter a valid number\n");
                    while (getchar() != '\n');
                    p.admittedDays = 0;
                }
            } while (p.admittedDays <= 0);

            double dailyRate = 0.0;
            if (p.wardID == 1) dailyRate = 3000.00;
            else if (p.wardID == 2)
                dailyRate = 6000.00;
            else if (p.wardID == 3)
                dailyRate = 12000.00;
            else if (p.wardID == 4)
                dailyRate = 25000.00;
            p.wardCost = p.admittedDays * dailyRate;
        }
    } else {
        p.wardID = 0;
        p.bedNumber = 0;
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

    printf("\n\t==================================================\n");
    printf("\t       SMART HOSPITAL ADMISSION & BILL           \n");
    printf("\t==================================================\n");
    printf("\tPatient ID             : %s\n", p.patientID);
    printf("\tPatient Name           : %s\n", p.patientFullName);
    printf("\tAge                    : %d Years %s\n", p.patientAge,
           (p.patientAge < 5 || p.patientAge > 65) ? "(15% Subsidy Eligible)" : "");
    switch (p.specialtyID) {
    case 1:
        printf("\tSpecialty              : General Practice\n");
        break;
    case 2:
        printf("\tSpecialty              : Paediatrics\n");
        break;
    case 3:
        printf("\tSpecialty              : Cardiology\n");
        break;
    case 4:
        printf("\tSpecialty              : Neurology\n");
        break;
    default:
        printf("\tSpecialty              : General Practice\n");
        break;
}
    if (p.isAdmitted) {
        if (p.wardID == 1) {
            printf("\tAssigned Ward          : General Ward (Bed #%02d)\n", p.bedNumber);
    } else if (p.wardID == 2) {
            printf("\tAssigned Ward          : Paediatric Ward (Bed #%02d)\n", p.bedNumber);
    } else if (p.wardID == 3) {
            printf("\tAssigned Ward          : Surgical Ward (Bed #%02d)\n", p.bedNumber);
    } else if (p.wardID == 4) {
            printf("\tAssigned Ward          : ICU (Bed #%02d)\n", p.bedNumber);
    }
    } else {
            printf("\tAssigned Ward          : Outpatient / OPD\n");
}
        if (p.urgencyLevel == 1)
            printf("\tUrgency level          : Level 1 (Normal)\n");
        else if (p.urgencyLevel == 2)
            printf("\tUrgency level          : Level 2 (Urgent)\n");
        else if (p.urgencyLevel == 3)
            printf("\tUrgency level          : Level 3 (Critical)\n");

        printf("\tBase Consultation Fee  : LKR %.2f\n", p.baseFee);
    if (p.urgencyLevel == 2)
        printf("\tEmergency Surcharge    : LKR %.2f (20%%)\n", p.emergencySurcharge);
    else if (p.urgencyLevel == 3)
        printf("\tEmergency Surcharge    : LKR %.2f (50%%)\n", p.emergencySurcharge);
    else
        printf("\tEmergency Surcharge    : LKR 0.00\n");

        printf("\tWard Stay Cost (%d Days): LKR %.2f\n", p.admittedDays, p.wardCost);
        printf("\tGross Total Bill       : LKR %.2f\n", p.grossTotal);
    if (p.discount > 0)
        printf("\tAge Subsidy Discount   : LKR -%.2f (15%%)\n", p.discount);
    else
        printf("\tAge Subsidy Discount   : LKR 0.00\n");
        printf("\tFinal Payable Amount   : LKR %.2f\n", p.finalPayable);
    if (p.waitTime == 0.0f)
        printf("\tWaiting Time           : %.2f mins (Immediate Attention)\n", p.waitTime);
    else
        printf("\tWaiting Time           : %.2f mins\n", p.waitTime);
    printf("\t==================================================\n");
}

void viewPatientsRecords()
{
    if (patientCount == 0)
    {
        printf("\tNo patient records found\n");
        return;
    }
  else
  {
      for (int i = 0; i < patientCount ; i++)
      {
        printf("\n\t=========================================\n");
        printf("\t        Registered patients records ");
        printf("\n\t=========================================\n");
        printf("\tPatient number          : %d\n", i + 1);
        printf("\tPatient ID              : %s\n", patients[i].patientID);
        printf("\tPatient Name            : %s\n", patients[i].patientFullName);
        printf("\tAge                     : %d Years\n", patients[i].patientAge);
        printf("\tUrgency Level           : %d\n", patients[i].urgencyLevel);
        printf("\tBase Consultation Fee   : LKR %.2f\n", patients[i].baseFee);
        printf("\tEmergency Surcharge     : LKR %.2f\n", patients[i].emergencySurcharge);
        printf("\tWard Stay Cost (%d Days): LKR %.2f\n", patients[i].admittedDays, patients[i].wardCost);
        printf("\tGross Total Bill        : LKR %.2f\n", patients[i].grossTotal);
        printf("\tAge Subsidy Discount    : LKR %.2f\n", patients[i].discount);
        printf("\tFinal Amount Payable    : LKR %.2f\n", patients[i].finalPayable);

  }
}
}
void sortByUrgency()
{
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[j].urgencyLevel < patients[j + 1].urgencyLevel) {
                struct patientDetails temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
  }
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

    int normalCount = 0, urgentCount = 0, criticalCount = 0;
    int highestIndex = 0;

    for ( int i = 0; i < patientCount; i++)
    {
        totalRevenue += patients[i].finalPayable;
        totalDiscounts += patients[i].discount;
        totalSurcharges += patients[i].emergencySurcharge;
        if (patients[i].urgencyLevel == 1) normalCount++;
        else if (patients[i].urgencyLevel == 2) urgentCount++;
        else if (patients[i].urgencyLevel == 3) criticalCount++;

        if (patients[i].isAdmitted == 1 )
        {
            totalAdmitted++;
        }
        if (patients[i].finalPayable > patients[highestIndex].finalPayable) {
            highestIndex = i;
        }
    }
    printf("\n\t=========================================\n");
    printf("\n\t          Final report\n");
    printf("\n\t=========================================\n");
    printf("\tTotal Patients Registered   : %d\n", patientCount);
    printf("\t  - Level 1 (Normal)        : %d\n", normalCount);
    printf("\t  - Level 2 (Urgent)        : %d\n", urgentCount);
    printf("\t  - Level 3 (Critical)      : %d\n", criticalCount);
    printf("\tTotal Admitted Patients     : %d\n", totalAdmitted);
    printf("\tTotal outpatients           : %d\n", patientCount - totalAdmitted);
    printf("\tBed Occupancy Rates:\n");
    char *wardNames[] = {"General", "Paediatric", "Surgical", "ICU"};

    for (int w = 0; w < 4; w++) {
        int occupiedCount = 0;
            for (int b = 0; b < wardCapacities[w]; b++) {
                if (bedOccupancy[w][b] == 1) {
                    occupiedCount++;
            }
            }
    double percentage = ((double)occupiedCount / wardCapacities[w]) * 100.0;

    printf("\t  %s Ward      : %d/%d (%.1f%%)\n",wardNames[w], occupiedCount, wardCapacities[w], percentage);
    }
    printf("\tTotal Surcharges & Discounts: %.2lf  %.2lf\n", totalSurcharges, totalDiscounts);
    printf("\tTotal Net Revenue           : %.2lf\n", totalRevenue);
    printf("\tAverage Payable per Patient : %.2lf\n", totalRevenue/patientCount);
    printf("\n\tHighest-Paying Patient      : %s (%s)\n",patients[highestIndex].patientFullName, patients[highestIndex].patientID);
    printf("\tHighest Bill Amount         : LKR %.2f\n", patients[highestIndex].finalPayable);
    printf("\n\t=========================================\n");
}


