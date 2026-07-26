#include <iostream>
#include <fstream>
using namespace std;

/*
====================================================
                    STRUCTURES
====================================================
*/
//***************************************************8*********************************************
struct Request
{
    int patientID;
    char bloodGroup[5];
    int units;
    Request* next;
};

Request* frontReq = NULL;
Request* rearReq = NULL;

struct DonationHistory
{
    int donorID;
    char bloodGroup[5];
    int units;
    DonationHistory* next;
};

DonationHistory* topDonation = NULL;
//********************************************************************************************888
struct Donor {
    int id;
    char name[50];
    int age;
    char blood[5];
    char phone[12];
    char cnic[14];
    char disease[50];
    Donor* next;
};

struct Patient {
    int id;
    char name[50];
    int age;
    char blood[5];
    char phone[12];
    char cnic[14];
    char disease[50];
    int emergency;
    Patient* next;
};

struct Blood {
    char group[5];
    int units;
    Blood* next;
};

Blood* bHead = NULL;
/*
====================================================
                GLOBAL VARIABLES
====================================================
*/

Donor* dHead = NULL;
Patient* pHead = NULL;

int dID = 1;
int pID = 1;

void addDonor();
void showDonors();
void deleteDonor(int);

void addPatient();
void showPatients();

void donorMenu();
void patientMenu();
void nurseMenu();
void managerMenu();

void showInventory();
void addUnits();
void removeUnits();
//********************************************** ************************************
// Queue functions
void enqueueRequest(int pid, char blood[], int units);
void dequeueRequest();
void showRequests();

// Stack functions
void pushDonation(int donorID, char blood[], int units);
void showDonationHistory();
//*********************************************************************************
Donor* searchDonor(int);
Patient* searchPatient(int);

/*
====================================================
                STRING HELPERS
====================================================
*/

bool strEqual(char a[], char b[]) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

int strLen(char a[]) {
    int i = 0;
    while (a[i]) i++;
    return i;
}

/*
====================================================
              VALIDATION FUNCTIONS
====================================================
*/

/*
====================================================
              VALIDATION FUNCTIONS
====================================================
*/

// Check phone length = 11 digits
bool validPhone(char phone[])
{
    if (strLen(phone) != 11)
    {
        return false;
    }

    // check all are digits
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return false;
        }
    }

    return true;
}

// Check CNIC length = 13 digits
bool validCNIC(char cnic[])
{
    if (strLen(cnic) != 13)
    {
        return false;
    }

    // check all are digits
    for (int i = 0; cnic[i] != '\0'; i++)
    {
        if (cnic[i] < '0' || cnic[i] > '9')
        {
            return false;
        }
    }

    return true;
}

// Check duplicate phone
bool phoneExists(char phone[])
{
    Donor* d = dHead;

    while (d != NULL)
    {
        if (strEqual(d->phone, phone))
        {
            return true;
        }

        d = d->next;
    }

    Patient* p = pHead;

    while (p != NULL)
    {
        if (strEqual(p->phone, phone))
        {
            return true;
        }

        p = p->next;
    }

    return false;
}

// Check duplicate CNIC
bool cnicExists(char cnic[])
{
    Donor* d = dHead;

    while (d != NULL)
    {
        if (strEqual(d->cnic, cnic))
        {
            return true;
        }

        d = d->next;
    }

    Patient* p = pHead;

    while (p != NULL)
    {
        if (strEqual(p->cnic, cnic))
        {
            return true;
        }

        p = p->next;
    }

    return false;
}

/*
====================================================
              LOGIN SYSTEM (3 ATTEMPTS)
====================================================
*/

bool login(const char role[]) {
    char u[20], p[20];
    int attempts = 3;

    while (attempts--) {
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        if ((strEqual((char*)role, (char*)"manager") &&
            strEqual(u, (char*)"manager") &&
            strEqual(p, (char*)"123")) ||

            (strEqual((char*)role, (char*)"nurse") &&
                strEqual(u, (char*)"nurse") &&
                strEqual(p, (char*)"123"))) {

            return true;
        }

        cout << "Wrong login. Attempts left: " << attempts << "\n";
    }

    cout << "ACCOUNT LOCKED!\n";
    return false;
}

/*
====================================================
              FILE SYSTEM
====================================================
*/

void saveDonor(Donor* d) {
    ofstream f("donor.txt", ios::app);
    f << d->id << " " << d->name << " " << d->age << " "
        << d->blood << " " << d->phone << " "
        << d->cnic << " " << d->disease << "\n";
}

void savePatient(Patient* p) {
    ofstream f("patient.txt", ios::app);
    f << p->id << " " << p->name << " " << p->age << " "
        << p->blood << " " << p->phone << " "
        << p->cnic << " " << p->disease << " "
        << p->emergency << "\n";
}

/*
====================================================
              INIT INVENTORY
====================================================
*/
void initBlood()
{
    const char* g[] =
    {
        "A+",
        "A-",
        "B+",
        "B-",
        "AB+",
        "AB-",
        "O+",
        "O-"
    };

    int u[] =
    {
        4,
        2,
        5,
        2,
        8,
        2,
        3,
        2
    };

    for (int i = 0; i < 8; i++)
    {
        Blood* b = new Blood();

        int j = 0;

        while (g[i][j])
        {
            b->group[j] = g[i][j];
            j++;
        }

        b->group[j] = '\0';

        b->units = u[i];

        b->next = bHead;
        bHead = b;
    }
}
///////////////////////////////////////////////////////////////
void toUpperCase(char str[])
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        }

        i++;
    }
}


//=================Validate blood group==============
//                Validate blood group
// ===================================================

bool validBloodGroup(char g[])
{
    toUpperCase(g);

    if (strEqual(g, (char*)"A+")) return true;
    if (strEqual(g, (char*)"A-")) return true;
    if (strEqual(g, (char*)"B+")) return true;
    if (strEqual(g, (char*)"B-")) return true;
    if (strEqual(g, (char*)"AB+")) return true;
    if (strEqual(g, (char*)"AB-")) return true;
    if (strEqual(g, (char*)"O+")) return true;
    if (strEqual(g, (char*)"O-")) return true;

    return false;
}

//=============================BLOOD COMPATIBILITY
void showCompatibility(char g[])
{
    toUpperCase(g);

    if (!validBloodGroup(g))
    {
        cout << "Invalid Blood Group!\n";
        return;
    }

    cout << "\nCompatibility for "
        << g
        << ":\n";

    if (strEqual(g, (char*)"A+"))
    {
        cout << "A+, A-, O+, O-\n";
    }

    else if (strEqual(g, (char*)"A-"))
    {
        cout << "A-, O-\n";
    }

    else if (strEqual(g, (char*)"B+"))
    {
        cout << "B+, B-, O+, O-\n";
    }

    else if (strEqual(g, (char*)"B-"))
    {
        cout << "B-, O-\n";
    }

    else if (strEqual(g, (char*)"AB+"))
    {
        cout << "All blood groups\n";
    }

    else if (strEqual(g, (char*)"AB-"))
    {
        cout << "AB-, A-, B-, O-\n";
    }

    else if (strEqual(g, (char*)"O+"))
    {
        cout << "O+, O-\n";
    }

    else if (strEqual(g, (char*)"O-"))
    {
        cout << "O- only\n";
    }
}

//====================================================INVENTORY FUNCTIONS (ADD / REMOVE / SHOW)

Blood* findBlood(char g[])
{
    toUpperCase(g);

    Blood* t = bHead;

    while (t)
    {
        if (strEqual(t->group, g))
            return t;

        t = t->next;
    }

    return NULL;
}

void showInventory() {
    Blood* t = bHead;

    cout << "\n--- BLOOD INVENTORY ---\n";

    while (t) {
        cout << t->group << " : " << t->units << endl;
        t = t->next;
    }
}

void addUnits() {
    char g[5];
    int u;

    cout << "Enter blood group: ";
    cin >> g;

    cout << "Enter units to add: ";
    cin >> u;

    Blood* b = findBlood(g);
    if (b) b->units += u;

    cout << "Updated!\n";
}

void removeUnits() {
    char g[5];
    int u;

    cout << "Enter blood group: ";
    cin >> g;

    cout << "Enter units to remove: ";
    cin >> u;

    Blood* b = findBlood(g);

    if (b) {
        if (b->units >= u)
            b->units -= u;
        else
            cout << "Not enough stock!\n";
    }
}

//======================================================SEARCH FUNCTIONS (DONOR + PATIENT)

Donor* searchDonor(int id) {
    Donor* t = dHead;

    while (t) {
        if (t->id == id) return t;
        t = t->next;
    }
    return NULL;
}

Patient* searchPatient(int id) {
    Patient* t = pHead;

    while (t) {
        if (t->id == id) return t;
        t = t->next;
    }
    return NULL;
}

/*
====================================================
              DONOR FUNCTIONS
====================================================
*/

void showDonors() {
    if (!dHead) {
        cout << "No donors found!\n";
        return;
    }

    Donor* t = dHead;

    while (t) {
        cout << "\n-------------------\n";
        cout << "ID: " << t->id << endl;
        cout << "Name: " << t->name << endl;
        cout << "Age: " << t->age << endl;
        cout << "Blood: " << t->blood << endl;
        cout << "Phone: " << t->phone << endl;
        cout << "CNIC: " << t->cnic << endl;
        cout << "Disease: " << t->disease << endl;
        t = t->next;
    }
}

void addDonor() {
    Donor* d = new Donor();
    d->id = dID++;

    cout << "Name: ";
    cin >> d->name;

    do {
        cout << "Age (18-65): ";
        cin >> d->age;
    } while (d->age < 18 || d->age > 65);

    do
    {
        cout << "Blood Group (A+,A-,B+,B-,AB+,AB-,O+,O-): ";
        cin >> d->blood;

        toUpperCase(d->blood);

        if (!validBloodGroup(d->blood))
        {
            cout << "Invalid Blood Group!\n";
        }

    } while (!validBloodGroup(d->blood));

    do
    {
        cout << "Phone (11 digits): ";
        cin >> d->phone;

        if (!validPhone(d->phone))
        {
            cout << "Invalid Phone Number!\n";
        }

        else if (phoneExists(d->phone))
        {
            cout << "Phone number already exists in system!\n";
        }

    } while (!validPhone(d->phone)
        || phoneExists(d->phone));

    do
    {
        cout << "CNIC (13 digits): ";
        cin >> d->cnic;

        if (!validCNIC(d->cnic))
        {
            cout << "Invalid CNIC!\n";
        }

        else if (cnicExists(d->cnic))
        {
            cout << "CNIC already exists in system!\n";
        }

    } while (!validCNIC(d->cnic)
        || cnicExists(d->cnic));

    cout << "Disease: ";
    cin >> d->disease;

    d->next = dHead;
    dHead = d;

    saveDonor(d);

    cout << "Donor Added Successfully!\n";
}

void deleteDonor(int id) {
    Donor* t = dHead;
    Donor* prev = NULL;

    while (t && t->id != id) {
        prev = t;
        t = t->next;
    }

    if (!t) {
        cout << "Not found!\n";
        return;
    }

    if (!prev) dHead = t->next;
    else prev->next = t->next;

    delete t;
    cout << "Deleted!\n";
}

/*
====================================================
              PATIENT FUNCTIONS
====================================================
*/

void showPatients()
{
    if (pHead == NULL)
    {
        cout << "No patients found!\n";
        return;
    }

    Patient* t = pHead;

    while (t)
    {
        cout << "\n------------------------\n";
        cout << "ID: " << t->id << endl;
        cout << "Name: " << t->name << endl;
        cout << "Age: " << t->age << endl;
        cout << "Blood Group: " << t->blood << endl;
        cout << "Phone: " << t->phone << endl;
        cout << "CNIC: " << t->cnic << endl;
        cout << "Disease: " << t->disease << endl;
        cout << "Emergency Level: " << t->emergency << endl;

        t = t->next;
    }
}

void addPatient()
{
    Patient* p = new Patient();

    p->id = pID++;

    cout << "Name: ";
    cin >> p->name;

    do
    {
        cout << "Age (1-120): ";
        cin >> p->age;

        if (p->age < 1 || p->age > 120)
            cout << "Invalid Age!\n";

    } while (p->age < 1 || p->age > 120);

    do
    {
        cout << "Blood Group (A+,A-,B+,B-,AB+,AB-,O+,O-): ";
        cin >> p->blood;

        toUpperCase(p->blood);

        if (!validBloodGroup(p->blood))
        {
            cout << "Invalid Blood Group!\n";
        }

    } while (!validBloodGroup(p->blood));

    do
    {
        cout << "Phone (11 digits): ";
        cin >> p->phone;

        if (!validPhone(p->phone))
        {
            cout << "Invalid Phone Number!\n";
        }

        else if (phoneExists(p->phone))
        {
            cout << "Phone number already exists in system!\n";
        }

    } while (!validPhone(p->phone)
        || phoneExists(p->phone));

    do
    {
        cout << "CNIC (13 digits): ";
        cin >> p->cnic;

        if (!validCNIC(p->cnic))
        {
            cout << "Invalid CNIC!\n";
        }

        else if (cnicExists(p->cnic))
        {
            cout << "CNIC already exists in system!\n";
        }

    } while (!validCNIC(p->cnic)
        || cnicExists(p->cnic));

    cout << "Disease: ";
    cin >> p->disease;

    do
    {
        cout << "Emergency Level (1-10): ";
        cin >> p->emergency;

        if (p->emergency < 1 || p->emergency > 10)
            cout << "Invalid Level!\n";

    } while (p->emergency < 1 || p->emergency > 10);

    p->next = pHead;
    pHead = p;

    savePatient(p);

    cout << "\nPatient Added Successfully!\n";
    cout << "Patient ID: " << p->id << endl;
}

/*
====================================================
              PATIENT FUNCTIONS
====================================================
*/
//****************************************************************************************************
void enqueueRequest(int pid, char blood[], int units)
{
    Request* r = new Request();

    r->patientID = pid;

    int i = 0;
    while (blood[i] != '\0')
    {
        r->bloodGroup[i] = blood[i];
        i++;
    }
    r->bloodGroup[i] = '\0';

    r->units = units;
    r->next = NULL;

    if (rearReq == NULL)
    {
        frontReq = rearReq = r;
    }
    else
    {
        rearReq->next = r;
        rearReq = r;
    }

    cout << "Blood Request Added To Queue!\n";
}

/////////////////////////////////////////////
void dequeueRequest()
{
    if (frontReq == NULL)
    {
        cout << "No pending requests!\n";
        return;
    }

    Request* temp = frontReq;

    cout << "\nProcessing Request:\n";
    cout << "Patient ID: " << temp->patientID << endl;
    cout << "Blood Group: " << temp->bloodGroup << endl;
    cout << "Units: " << temp->units << endl;

    frontReq = frontReq->next;

    if (frontReq == NULL)
        rearReq = NULL;

    delete temp;
}
// /////////////////////////////////////////////////////////////////
void showRequests()
{
    if (frontReq == NULL)
    {
        cout << "No requests in queue!\n";
        return;
    }

    Request* t = frontReq;

    cout << "\n--- BLOOD REQUEST QUEUE ---\n";

    while (t)
    {
        cout << "Patient ID: " << t->patientID
            << " | Blood: " << t->bloodGroup
            << " | Units: " << t->units << endl;

        t = t->next;
    }
}
// ///////////////////////////////////////////////////////////
//**************************************************************************************


void patientMenu() {

    int ch;
    Patient* currentPatient = NULL;

    do {
        cout << "\n===== PATIENT MENU =====\n";
        cout << "1. Register Patient\n";
        cout << "2. Show Blood Compatibility\n";
        cout << "3. Display Blood Inventory\n";
        cout << "4. Show Current Patient Details\n";
        cout << "5. Request Blood\n";
        cout << "6. Exit back to main menu\n";
        cout << "Enter Choice: ";
        cin >> ch;

        switch (ch) {

        case 1:
        {
            currentPatient = new Patient();

            currentPatient->id = pID++;

            cout << "Name: ";
            cin >> currentPatient->name;

            do {
                cout << "Age (1-120): ";
                cin >> currentPatient->age;

                if (currentPatient->age < 1 ||
                    currentPatient->age > 120)
                {
                    cout << "Invalid age!\n";
                }

            } while (currentPatient->age < 1 ||
                currentPatient->age > 120);

            do
            {
                cout << "Blood Group (A+,A-,B+,B-,AB+,AB-,O+,O-): ";
                cin >> currentPatient->blood;

                toUpperCase(currentPatient->blood);

                if (!validBloodGroup(currentPatient->blood))
                {
                    cout << "Invalid Blood Group!\n";
                }

            } while (!validBloodGroup(currentPatient->blood));

            do
            {
                cout << "Phone Number (11 digits): ";
                cin >> currentPatient->phone;

                if (!validPhone(currentPatient->phone))
                {
                    cout << "Invalid phone number!\n";
                }

                else if (phoneExists(currentPatient->phone))
                {
                    cout << "Phone number already exists in system!\n";
                }

            } while (!validPhone(currentPatient->phone)
                || phoneExists(currentPatient->phone));

            do
            {
                cout << "CNIC (13 digits): ";
                cin >> currentPatient->cnic;

                if (!validCNIC(currentPatient->cnic))
                {
                    cout << "Invalid CNIC!\n";
                }

                else if (cnicExists(currentPatient->cnic))
                {
                    cout << "CNIC already exists in system!\n";
                }

            } while (!validCNIC(currentPatient->cnic)
                || cnicExists(currentPatient->cnic));

            cout << "Disease: ";
            cin >> currentPatient->disease;

            do {
                cout << "Emergency Level (1-10): ";
                cin >> currentPatient->emergency;

                if (currentPatient->emergency < 1 ||
                    currentPatient->emergency > 10)
                {
                    cout << "Invalid level! Must be 1-10.\n";
                }

            } while (currentPatient->emergency < 1 ||
                currentPatient->emergency > 10);

            currentPatient->next = pHead;
            pHead = currentPatient;

            savePatient(currentPatient);

            cout << "\nPatient Registered Successfully!\n";
            cout << "Your Patient ID is: "
                << currentPatient->id << endl;

            break;
        }

        case 2:
        {
            if (currentPatient == NULL) {
                cout << "No patient registered yet!\n";
            }
            else {
                cout << "\nBlood Compatibility for "
                    << currentPatient->blood
                    << ":\n";

                showCompatibility(currentPatient->blood);
            }

            break;
        }

        case 3:
        {
            showInventory();
            break;
        }

        case 4:
        {
            if (currentPatient == NULL) {
                cout << "No patient registered yet!\n";
            }
            else {
                cout << "\n===== CURRENT PATIENT DETAILS =====\n";

                cout << "ID: "
                    << currentPatient->id << endl;

                cout << "Name: "
                    << currentPatient->name << endl;

                cout << "Age: "
                    << currentPatient->age << endl;

                cout << "Blood Group: "
                    << currentPatient->blood << endl;

                cout << "Phone: "
                    << currentPatient->phone << endl;

                cout << "CNIC: "
                    << currentPatient->cnic << endl;

                cout << "Disease: "
                    << currentPatient->disease << endl;

                cout << "Emergency Level: "
                    << currentPatient->emergency << endl;
            }

            break;
        }
        case 5:
        {
            if (currentPatient == NULL)
            {
                cout << "Register first!\n";
            }
            else
            {
                int units;
                cout << "Enter required units: ";
                cin >> units;

                enqueueRequest(currentPatient->id, currentPatient->blood, units);
            }
            break;
        }
        case 6:
            cout << "Returning to Main Menu...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (ch != 6);
}
////////////////////////////////////*****************************************************************************
//*************************************************************************************
void pushDonation(int donorID, char blood[], int units)
{
    DonationHistory* d = new DonationHistory();

    d->donorID = donorID;

    int i = 0;
    while (blood[i] != '\0')
    {
        d->bloodGroup[i] = blood[i];
        i++;
    }
    d->bloodGroup[i] = '\0';

    d->units = units;

    d->next = topDonation;
    topDonation = d;

    cout << "Donation recorded in history!\n";
}
///////////
void showDonationHistory()
{
    if (topDonation == NULL)
    {
        cout << "No donation history!\n";
        return;
    }

    DonationHistory* t = topDonation;

    cout << "\n--- DONATION HISTORY (STACK) ---\n";

    while (t)
    {
        cout << "Donor ID: " << t->donorID
            << " | Blood: " << t->bloodGroup
            << " | Units: " << t->units << endl;

        t = t->next;
    }
}
//******************************************************************************
void donateBlood()
{
    char group[5];
    int units;

    do
    {
        cout << "Enter Blood Group (A+,A-,B+,B-,AB+,AB-,O+,O-): ";
        cin >> group;

        toUpperCase(group);

        if (!validBloodGroup(group))
        {
            cout << "Invalid Blood Group!\n";
        }

    } while (!validBloodGroup(group));

    do
    {
        cout << "How many units do you want to donate? ";
        cin >> units;

        if (units <= 0)
        {
            cout << "Invalid units!\n";
        }

    } while (units <= 0);

    Blood* b = findBlood(group);

    if (b != NULL)
    {
        b->units += units;

        // STACK ADDED HERE
        pushDonation(0, group, units);

        cout << "\nDonation Successful!\n";
        cout << units << " units added to "
            << group << endl;

        cout << "Updated Stock = "
            << b->units
            << endl;
    }
}
/*
====================================================
              DONOR MENU
====================================================
*/

void donorMenu() {
    int donateChoice;
    int ch;
    Donor* currentDonor = NULL;

    do {
        cout << "\n===== DONOR MENU =====\n";
        cout << "1. Register Donor\n";
        cout << "2. Show Current Donor Details\n";
        cout << "3. Check Blood Compatibility\n";
        cout << "4. Wants to donate blood\n";
        cout << "5. Exit (Back to Main Menu)\n";
        cout << "Enter Choice: ";
        cin >> ch;

        switch (ch) {

        case 1:
        {
            currentDonor = new Donor();

            currentDonor->id = dID++;

            cout << "Name: ";
            cin >> currentDonor->name;

            do {
                cout << "Age (18-65): ";
                cin >> currentDonor->age;

                if (currentDonor->age < 18 ||
                    currentDonor->age > 65)
                {
                    cout << "Invalid age! Donor age must be between 18 and 65.\n";
                }

            } while (currentDonor->age < 18 ||
                currentDonor->age > 65);

            do
            {
                cout << "Blood Group (A+,A-,B+,B-,AB+,AB-,O+,O-): ";
                cin >> currentDonor->blood;

                toUpperCase(currentDonor->blood);

                if (!validBloodGroup(currentDonor->blood))
                {
                    cout << "Invalid Blood Group!\n";
                }

            } while (!validBloodGroup(currentDonor->blood));

            do
            {
                cout << "Phone Number (11 digits): ";
                cin >> currentDonor->phone;

                if (!validPhone(currentDonor->phone))
                {
                    cout << "Invalid phone number!\n";
                }

                else if (phoneExists(currentDonor->phone))
                {
                    cout << "Phone number already exists in system!\n";
                }

            } while (!validPhone(currentDonor->phone)
                || phoneExists(currentDonor->phone));

            do
            {
                cout << "CNIC (13 digits): ";
                cin >> currentDonor->cnic;

                if (!validCNIC(currentDonor->cnic))
                {
                    cout << "Invalid CNIC!\n";
                }

                else if (cnicExists(currentDonor->cnic))
                {
                    cout << "CNIC already exists in system!\n";
                }

            } while (!validCNIC(currentDonor->cnic)
                || cnicExists(currentDonor->cnic));

            cout << "Disease: ";
            cin >> currentDonor->disease;

            currentDonor->next = dHead;
            dHead = currentDonor;

            saveDonor(currentDonor);

            cout << "\nDonor Registered Successfully!\n";
            cout << "Your Donor ID is: "
                << currentDonor->id << endl;

            break;
        }

        case 2:
        {
            if (currentDonor == NULL) {
                cout << "No donor registered yet!\n";
            }
            else {
                cout << "\n===== CURRENT DONOR DETAILS =====\n";
                cout << "ID: "
                    << currentDonor->id << endl;

                cout << "Name: "
                    << currentDonor->name << endl;

                cout << "Age: "
                    << currentDonor->age << endl;

                cout << "Blood Group: "
                    << currentDonor->blood << endl;

                cout << "Phone: "
                    << currentDonor->phone << endl;

                cout << "CNIC: "
                    << currentDonor->cnic << endl;

                cout << "Disease: "
                    << currentDonor->disease << endl;
            }

            break;
        }

        case 3:
        {
            char bloodGroup[5];

            cout << "Enter Blood Group: ";
            cin >> bloodGroup;

            showCompatibility(bloodGroup);

            break;
        }
        case 4:
        {
            cout << "Do you want to donate blood now?\n";
            cout << "1. Yes\n";
            cout << "2. No\n";
            cin >> donateChoice;

            if (donateChoice == 1)
            {
                donateBlood();
            }

            break;
        }
        case 5:
            cout << "Returning to Main Menu...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (ch != 5);
}

/*
====================================================
               Delete Patient
 ===================================================
 */
void deletePatient(int id)
{
    Patient* temp = pHead;
    Patient* prev = NULL;

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Patient not found!\n";
        return;
    }

    // deleting first node
    if (prev == NULL)
    {
        pHead = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    delete temp;

    cout << "Patient deleted successfully!\n";
}


/*
====================================================
              NURSE MENU
====================================================
*/

void nurseMenu() {
    if (!login("nurse")) return;

    int c;

    do {
        cout << "\n===== NURSE MENU =====\n";
        cout << "1. Show Donors\n";
        cout << "2. Show Patients\n";
        cout << "3. Add Donor\n";
        cout << "4. Remove Donor\n";
        cout << "5. Search Donor\n";
        cout << "6. Add Patient\n";
        cout << "7. Remove Patient\n";
        cout << "8. Search Patient\n";
        cout << "9. Show Inventory\n";
        cout << "10. Exit\n";

        cin >> c;

        if (c == 1) showDonors();
        else if (c == 2) showPatients();
        else if (c == 3) addDonor();
        else if (c == 4) {
            int id; cin >> id;
            deleteDonor(id);
        }
        else if (c == 5) {
            int id; cin >> id;
            Donor* d = searchDonor(id);
            if (d) cout << d->name << endl;
        }
        else if (c == 6) addPatient();

        else if (c == 7)
        {
            int id;

            cout << "Enter Patient ID to delete: ";
            cin >> id;

            deletePatient(id);
        }

        else if (c == 8) {
            int id; cin >> id;
            Patient* p = searchPatient(id);
            if (p) cout << p->name << endl;
        }

        else if (c == 9) showInventory();

    } while (c != 10);
}

/*
====================================================
              MANAGER MENU
====================================================
*/

void managerMenu() {
    if (!login("manager")) return;

    int c;

    do {
        cout << "\n===== MANAGER MENU =====\n";
        cout << "1. Show Donors\n";
        cout << "2. Show Patients\n";
        cout << "3. Add Donor\n";
        cout << "4. Remove Donor\n";
        cout << "5. Search Donor by ID\n";
        cout << "6. Add Patient\n";
        cout << "7. Remove Patient\n";
        cout << "8. Search Patient by ID\n";
        cout << "9. Show Inventory\n";
        cout << "10. Add Blood Units\n";
        cout << "11. Remove Blood Units\n";
        cout << "12. Show Blood Requests\n";
        cout << "13. Process Next Request\n";
        cout << "14. Show Donation History\n";
        cout << "15. Exit\n";

        cin >> c;

        if (c == 1) showDonors();
        else if (c == 2) showPatients();
        else if (c == 3) addDonor();

        else if (c == 4) {
            int id; cin >> id;
            deleteDonor(id);
        }

        else if (c == 5) {
            int id; cin >> id;
            Donor* d = searchDonor(id);

            if (d)
                cout << d->name << " " << d->blood << endl;
            else
                cout << "Not found\n";
        }

        else if (c == 6) addPatient();

        else if (c == 7)
        {
            int id;

            cout << "Enter Patient ID to delete: ";
            cin >> id;

            deletePatient(id);
        }

        else if (c == 8) {
            int id; cin >> id;
            Patient* p = searchPatient(id);

            if (p)
                cout << p->name << " " << p->blood << endl;
            else
                cout << "Not found\n";
        }

        else if (c == 9) showInventory();

        else if (c == 10) addUnits();

        else if (c == 11) removeUnits();
        else if (c == 12)
            showRequests();

        else if (c == 13)
            dequeueRequest();

        else if (c == 14)
            showDonationHistory();
    } while (c != 15);
}



/*
====================================================
              MAIN MENU
====================================================
*/

int main() {

    initBlood();

    int choice;

    do {
        cout << "\n===== BLOOD BANK SYSTEM =====\n";
        cout << "1. Donor\n";
        cout << "2. Patient\n";
        cout << "3. Manager\n";
        cout << "4. Nurse\n";
        cout << "5. Exit\n";
        cin >> choice;

        if (choice == 1) donorMenu();
        else if (choice == 2) patientMenu();
        else if (choice == 3) managerMenu();
        else if (choice == 4) nurseMenu();

    } while (choice != 5);

    return 0;
}