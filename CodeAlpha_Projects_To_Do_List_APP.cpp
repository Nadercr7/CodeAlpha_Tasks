// *************************************************************************************
// **                                                                                 **
// **                         To-Do List Application                                  **
// **                                                                                 **
// **                            Developed by Nader                                   **
// **                                                                                 **
// *************************************************************************************

#include <bits/stdc++.h>
using namespace std;

struct Task {
    string description;
    bool isCompleted;
};
// This structure defines a task with two members:
//     description: a string representing the task description.
//     isCompleted: a boolean indicating whether the task is completed (true) or not (false).

void saveTasks(const map<int, Task>& tasks) {
    ofstream file("tasks.txt");
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.first << "," << task.second.description << "," << task.second.isCompleted << endl;
        }
        file.close();
        cout << "Tasks saved to file.\n";
    } else {
        cout << "Unable to open file for saving tasks.\n";
    }
}
// This function saves the tasks to a file named "tasks.txt".
// It takes a map<int, Task> containing tasks as input.
// For each task in the map, it writes the task's ID (map key), description, and completion status to the file separated by commas.
// If the file is successfully opened, it writes the tasks and prints a message indicating success. Otherwise, it prints an error message.

void loadTasks(map<int, Task>& tasks) {
    ifstream file("tasks.txt");
    if (file.is_open()) {
        tasks.clear();
        int id;
        char comma;
        string description;
        bool isCompleted;
        while (file >> id >> comma >> ws && getline(file, description, ',') && file >> isCompleted) {
            tasks[id] = {description, isCompleted};
        }
        file.close();
        cout << "Tasks loaded from file.\n";
    } else {
        cout << "No existing tasks file found. Starting with an empty task list.\n";
    }
}
// This function loads tasks from the "tasks.txt" file.
// It takes a reference to a map<int, Task> as input.
// It clears the existing task list and reads task data from the file.
// For each line in the file, it reads the task ID, description, and completion status, and adds the task to the map.
// If the file is successfully opened, it prints a message indicating success. Otherwise, it prints a message indicating that no file was found.

void removeTask(map<int, Task>& tasks, int id) {
    auto it = tasks.find(id);
    if (it != tasks.end()) {
        tasks.erase(it);
        cout << "Task " << id << " removed.\n";
        saveTasks(tasks);
    } else {
        cout << "No task found with ID: " << id << "\n";
    }
}
// This function removes a task from the map based on its ID.
// It takes a reference to the task map and the ID of the task to be removed as input.
// It searches for the task with the given ID in the map.
// If the task is found, it erases it from the map and prints a message indicating success. Then, it calls saveTasks() to update the file.
// If the task is not found, it prints a message indicating that no task was found with the given ID.

void editTask(map<int, Task>& tasks, int id) {
    auto it = tasks.find(id);
    if (it != tasks.end()) {
        cout << "Enter new description for task " << id << ": ";
        cin.ignore();
        getline(cin, it->second.description);
        saveTasks(tasks);
    } else {
        cout << "No task found with ID: " << id << "\n";
    }
}
// This function allows users to edit the description of a task.
// It takes a reference to the task map and the ID of the task to be edited as input.
// It searches for the task with the given ID in the map.
// If the task is found, it prompts the user to enter a new description for the task, updates the task's description, and then calls saveTasks() to update the file.
// If the task is not found, it prints a message indicating that no task was found with the given ID.

int main() {
    map<int, Task> tasks;
    loadTasks(tasks);

    int id = (tasks.empty() ? 1 : tasks.rbegin()->first + 1);

    while (true) {
        cout << "1. Add task\n2. Complete task\n3. View tasks\n4. Remove task\n5. Edit task\n6. Exit\n\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();
                Task task;
                cout << "Enter task description: ";
                getline(cin, task.description);
                task.isCompleted = false;
                tasks[id] = task;
                id++;
                saveTasks(tasks);
                break;
            }
            case 2: {
                cout << "Enter task ID to mark as completed: ";
                int taskId;
                cin >> taskId;

                auto it = tasks.find(taskId);
                if (it != tasks.end()) {
                    it->second.isCompleted = true;
                    saveTasks(tasks);
                } else {
                    cout << "No task found with ID: " << taskId << "\n";
                }
                break;
            }
            case 3: {
                if (tasks.empty()) {
                    cout << "No tasks found.\n";
                } else {
                    for (const auto& task : tasks) {
                        cout << "ID: " << task.first << ", Description: " << task.second.description  
                              << ", Completed: " << (task.second.isCompleted ? "Yes" : "No") << "\n";
                    }
                }
                break;
            }
            case 4: {
                cout << "Enter task ID to remove: ";
                int taskId;
                cin >> taskId;
                removeTask(tasks, taskId);
                break;
            }
            case 5: {
                cout << "Enter task ID to edit: ";
                int taskId;
                cin >> taskId;
                editTask(tasks, taskId);
                break;
            }
            case 6: {
                return 0;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }

    return 0;
}
