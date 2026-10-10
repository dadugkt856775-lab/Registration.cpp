#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
    int priority;
};

struct ComparePatient {
    bool operator()(const Patient &a,
                    const Patient &b) const {
        if (a.priority == b.priority)
            return a.id > b.id;

        return a.priority < b.priority;
    }
};

int main() {
    priority_queue<Patient, vector<Patient>,
                   ComparePatient> emergency;
    queue<Patient> regular;

    int nextID = 1;
    int choice;

    do {
        cout << "\n===== HOSPITAL SYSTEM =====\n";
        cout << "1. Register Regular Patient\n";
        cout << "2. Register Emergency Patient\n";
        cout << "3. Call Next Patient\n";
        cout << "4. Display Waiting Counts\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string name;
            int priority = 0;

            cout << "Patient name: ";
            cin >> name;

            if (choice == 2) {
                cout << "Priority (1-5): ";
                cin >> priority;

                if (priority < 1 || priority > 5) {
                    cout << "Invalid priority.\n";
                    continue;
                }

                emergency.push({nextID++, name, priority});
                cout << "Emergency patient registered.\n";
            }
            else {
                regular.push({nextID++, name, priority});
                cout << "Regular patient registered.\n";
            }
        }
        else if (choice == 3) {
            if (!emergency.empty()) {
                Patient p = emergency.top();
                emergency.pop();

                cout << "Emergency patient called: "
                     << p.name << " | Priority: "
                     << p.priority << endl;
            }
            else if (!regular.empty()) {
                Patient p = regular.front();
                regular.pop();

                cout << "Regular patient called: "
                     << p.name << endl;
            }
            else {
                cout << "No patients waiting.\n";
            }
        }
        else if (choice == 4) {
            cout << "Emergency patients: "
                 << emergency.size() << endl;
            cout << "Regular patients: "
                 << regular.size() << endl;
        }

    } while (choice != 5);

    return 0;
}
