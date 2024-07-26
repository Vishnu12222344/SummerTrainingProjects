#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Message Class
class Message {
public:
    string sender;
    string receiver;
    string content;
    time_t timestamp;

    Message() {}

    Message(string sender, string receiver, string content) {
        this->sender = sender;
        this->receiver = receiver;
        this->content = content;
        this->timestamp = time(0);
    }

    void displayMessage() const {
        cout << "From: " << sender << ", To: " << receiver << ", Message: " << content << ", Timestamp: " << ctime(&timestamp);
    }
};

// SocialGroup Class
class SocialGroup {
public:
    string groupName;
    vector<string> members;
    vector<Message> messages;

    SocialGroup() {}

    SocialGroup(string groupName) {
        this->groupName = groupName;
    }

    void addMember(string userName) {
        members.push_back(userName);
    }

    void addMessage(const Message& message) {
        messages.push_back(message);
    }

    void displayGroupInfo() const {
        cout << "Group: " << groupName << "\nMembers: ";
        for (const auto& member : members) {
            cout << member << " ";
        }
        cout << "\nMessages:\n";
        for (const auto& message : messages) {
            message.displayMessage();
        }
        cout << "\n";
    }
};

// User Class
class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {}

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

// Global Maps
map<string, User> mapUserName;
map<string, set<string>> Friends;
map<pair<string, string>, vector<Message>> userMessages;
map<string, SocialGroup> groups;

// Functions
void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
        cout << "User " << userName << " added successfully.\n";
    } else {
        cout << "Username already taken.\n";
    }
}

void makeThemFriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        Friends[userName1].insert(userName2);
        Friends[userName2].insert(userName1);
        cout << userName1 << " and " << userName2 << " are now friends.\n";
    } else {
        cout << "One or both usernames do not exist.\n";
    }
}

void displayAllUsers() {
    for (const auto& entry : mapUserName) {
        cout << "Username: " << entry.first << ", Name: " << entry.second.firstName << " " << entry.second.lastName << "\n";
    }
}

void displayAllFriendships() {
    for (const auto& entry : Friends) {
        cout << entry.first << " is friends with: ";
        for (const auto& friendName : entry.second) {
            cout << friendName << " ";
        }
        cout << "\n";
    }
}

void sendMessage(string sender, string receiver, string content) {
    if (mapUserName.find(sender) != mapUserName.end() && mapUserName.find(receiver) != mapUserName.end()) {
        Message message(sender, receiver, content);
        userMessages[{sender, receiver}].push_back(message);
        message.displayMessage();
    } else {
        cout << "One or both usernames do not exist.\n";
    }
}

void createGroup(string groupName) {
    if (groups.find(groupName) == groups.end()) {
        groups[groupName] = SocialGroup(groupName);
        cout << "Group " << groupName << " created successfully.\n";
    } else {
        cout << "Group name already taken.\n";
    }
}

void addMemberToGroup(string groupName, string userName) {
    if (groups.find(groupName) != groups.end() && mapUserName.find(userName) != mapUserName.end()) {
        groups[groupName].addMember(userName);
        cout << "User " << userName << " added to group " << groupName << " successfully.\n";
    } else {
        cout << "Group or user does not exist.\n";
    }
}

void sendGroupMessage(string groupName, string userName, string content) {
    if (groups.find(groupName) != groups.end() && mapUserName.find(userName) != mapUserName.end()) {
        Message message(userName, groupName, content);
        groups[groupName].addMessage(message);
        message.displayMessage();
    } else {
        cout << "Group or user does not exist.\n";
    }
}

void displayGroupInfo(string groupName) {
    if (groups.find(groupName) != groups.end()) {
        groups[groupName].displayGroupInfo();
    } else {
        cout << "Group does not exist.\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "1. Add User\n2. Make Friends\n3. Display All Users\n4. Display All Friendships\n5. Send Message\n6. Create Group\n7. Add Member to Group\n8. Send Group Message\n9. Display Group Info\n10. Exit\n";
        cin >> choice;

        if (choice == 1) {
            string userName, firstName, lastName, gender;
            int age;
            cout << "Enter Username: ";
            cin >> userName;
            cout << "Enter First Name: ";
            cin >> firstName;
            cout << "Enter Last Name: ";
            cin >> lastName;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            User newUser(firstName, lastName, age, gender);
            addUser(userName, newUser);
        } else if (choice == 2) {
            string userName1, userName2;
            cout << "Enter First Username: ";
            cin >> userName1;
            cout << "Enter Second Username: ";
            cin >> userName2;
            makeThemFriend(userName1, userName2);
        } else if (choice == 3) {
            displayAllUsers();
        } else if (choice == 4) {
            displayAllFriendships();
        } else if (choice == 5) {
            string sender, receiver, content;
            cout << "Enter Sender Username: ";
            cin >> sender;
            cout << "Enter Receiver Username: ";
            cin >> receiver;
            cout << "Enter Message Content: ";
            cin.ignore();
            getline(cin, content);
            sendMessage(sender, receiver, content);
        } else if (choice == 6) {
            string groupName;
            cout << "Enter Group Name: ";
            cin >> groupName;
            createGroup(groupName);
        } else if (choice == 7) {
            string groupName, userName;
            cout << "Enter Group Name: ";
            cin >> groupName;
            cout << "Enter Username: ";
            cin >> userName;
            addMemberToGroup(groupName, userName);
        } else if (choice == 8) {
            string groupName, userName, content;
            cout << "Enter Group Name: ";
            cin >> groupName;
            cout << "Enter Username: ";
            cin >> userName;
            cout << "Enter Message Content: ";
            cin.ignore();
            getline(cin, content);
            sendGroupMessage(groupName, userName, content);
        } else if (choice == 9) {
            string groupName;
            cout << "Enter Group Name: ";
            cin >> groupName;
            displayGroupInfo(groupName);
        } else if (choice == 10) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
