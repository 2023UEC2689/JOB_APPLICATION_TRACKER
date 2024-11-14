#include <iostream>
#include <unordered_map>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct JobApplication {
    int id;
    string jobTitle;
    string company;
    string status;
    string dateApplied;
    string interviewDate;

    JobApplication(int i, const string& j, const string& c, const string& s, const string& d, const string& iDate)
        : id(i), jobTitle(j), company(c), status(s), dateApplied(d), interviewDate(iDate) {}

    JobApplication() : id(0), jobTitle(""), company(""), status(""), dateApplied(""), interviewDate("") {}
};

unordered_map<int, JobApplication> applications;


void addApplication(int id, const string& jobTitle, const string& company, const string& status, 
                    const string& dateApplied, const string& interviewDate) {
    applications[id] = JobApplication(id, jobTitle, company, status, dateApplied, interviewDate);
    cout << "Application added: " << jobTitle << " at " << company << endl;
}


void updateApplicationStatus(int id, const string& newStatus) {
    if (applications.find(id) != applications.end()) {
        applications[id].status = newStatus;
        cout << "Application status updated to: " << newStatus << endl;
    } else {
        cout << "Application ID not found." << endl;
    }
}


struct Interview {
    int id;
    string interviewDate;

    bool operator<(const Interview& other) const {
        return interviewDate > other.interviewDate;
    }
};


priority_queue<Interview> interviewQueue;

void addInterview(int id, const string& interviewDate) {
    interviewQueue.push({id, interviewDate});
}

void checkNextInterview() {
    if (!interviewQueue.empty()) {
        Interview nextInterview = interviewQueue.top();
        cout << "Next interview for application ID " << nextInterview.id << " on " << nextInterview.interviewDate << endl;
    } else {
        cout << "No upcoming interviews." << endl;
    }
}

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                node->children[ch] = new TrieNode();
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                return false;
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }
};

int main() {
    Trie jobTitleTrie;
    int choice;
    int id;
    string jobTitle, company, status, dateApplied, interviewDate, searchTitle;

    while (true) {
        cout << "\nJob Application Tracker Menu:\n";
        cout << "1. Add Application\n2. Update Application Status\n3. Add Interview Date\n";
        cout << "4. Check Next Interview\n5. Search Job Title\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Enter Application ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Job Title: ";
                getline(cin, jobTitle);
                cout << "Enter Company Name: ";
                getline(cin, company);
                cout << "Enter Status: ";
                getline(cin, status);
                cout << "Enter Date Applied: ";
                getline(cin, dateApplied);
                cout << "Enter Interview Date: ";
                getline(cin, interviewDate);
                
                addApplication(id, jobTitle, company, status, dateApplied, interviewDate);
                jobTitleTrie.insert(jobTitle);
                break;

            case 2:
                cout << "Enter Application ID to update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter new Status: ";
                getline(cin, status);
                updateApplicationStatus(id, status);
                break;

            case 3:
                cout << "Enter Application ID for interview: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Interview Date: ";
                getline(cin, interviewDate);
                addInterview(id, interviewDate);
                break;

            case 4:
                checkNextInterview();
                break;

            case 5:
                cout << "Enter Job Title to search: ";
                cin.ignore();
                getline(cin, searchTitle);
                if (jobTitleTrie.search(searchTitle))
                    cout << searchTitle << " found in applications." << endl;
                else
                    cout << searchTitle << " not found." << endl;
                break;

            case 6:
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
