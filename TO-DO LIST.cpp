#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string name;
    string due_date;
    int priority;
    bool completed;
};

void addTask(vector<Task>& tasks, const string& task_name, const string& due_date, int priority) {
    Task new_task = {task_name, due_date, priority, false};
    tasks.push_back(new_task);
}

void removeTask(vector<Task>& tasks, const string& task_name) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->name == task_name) {
            tasks.erase(it);
            break;
        }
    }
}

void updateTask(vector<Task>& tasks, const string& task_name, const string& new_due_date, int new_priority) {
    for (auto& task : tasks) {
        if (task.name == task_name) {
            task.due_date = new_due_date;
            task.priority = new_priority;
            break;
        }
    }
}

void markAsCompleted(vector<Task>& tasks, const string& task_name) {
    for (auto& task : tasks) {
        if (task.name == task_name) {
            task.completed = true;
            break;
        }
    }
}

void viewAllTasks(const vector<Task>& tasks) {
    cout << "All Tasks:" << endl;
    for (const auto& task : tasks) {
        string status = task.completed ? "Completed" : "Pending";
        cout << "- " << task.name << " (Due: " << task.due_date << ", Priority: " << task.priority << ", Status: " << status << ")" << endl;
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    do {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Update Task\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. View All Tasks\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, due_date;
            int priority;
            cout << "Enter task name: ";
            cin.ignore();  // to clear the newline character from the input buffer
            getline(cin, name);
            cout << "Enter due date (YYYY-MM-DD): ";
            getline(cin, due_date);
            cout << "Enter priority (1-5): ";
            cin >> priority;
            addTask(tasks, name, due_date, priority);
        } else if (choice == 2) {
            string name;
            cout << "Enter task name to remove: ";
            cin.ignore();
            getline(cin, name);
            removeTask(tasks, name);
        } else if (choice == 3) {
            string name, new_due_date;
            int new_priority;
            cout << "Enter task name to update: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new due date (YYYY-MM-DD): ";
            getline(cin, new_due_date);
            cout << "Enter new priority (1-5): ";
            cin >> new_priority;
            updateTask(tasks, name, new_due_date, new_priority);
        } else if (choice == 4) {
            string name;
            cout << "Enter task name to mark as completed: ";
            cin.ignore();
            getline(cin, name);
            markAsCompleted(tasks, name);
        } else if (choice == 5) {
            viewAllTasks(tasks);
        }

    } while (choice != 6);

    return 0;
}

