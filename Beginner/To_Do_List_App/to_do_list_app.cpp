#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool done;

    Task(const string& desc) : description(desc), done(false) {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& description) {
        tasks.emplace_back(description);
        cout << "Task added successfully.\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks in the list.\n";
            return;
        }
        cout << "To-Do List:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].done ? 'X' : ' ') << "] " << tasks[i].description << "\n";
        }
    }

    void markTaskDone(int index) {
        if (index < 1 || index > static_cast<int>(tasks.size())) {
            cout << "Invalid task number.\n";
            return;
        }
        if (tasks[index - 1].done) {
            cout << "Task already marked as done.\n";
        } else {
            tasks[index - 1].done = true;
            cout << "Task marked as done.\n";
        }
    }

    void deleteTask(int index) {
        if (index < 1 || index > static_cast<int>(tasks.size())) {
            cout << "Invalid task number.\n";
            return;
        }
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task deleted successfully.\n";
    }
};

int main() {
    ToDoList todo;
    int choice;
    string desc;
    int taskNumber;

    cout << "Welcome to the To-Do List App\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Done\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, desc);
                todo.addTask(desc);
                break;
            case 2:
                todo.viewTasks();
                break;
            case 3:
                cout << "Enter task number to mark as done: ";
                cin >> taskNumber;
                todo.markTaskDone(taskNumber);
                break;
            case 4:
                cout << "Enter task number to delete: ";
                cin >> taskNumber;
                todo.deleteTask(taskNumber);
                break;
            case 5:
                cout << "Exiting To-Do List App. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter 1-5.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
