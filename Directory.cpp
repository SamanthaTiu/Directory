#include <iostream>
#include <direct.h>  // For _mkdir, _chdir
#include <dos.h>     // For _getcwd, _chdir (older header, some compilers may not support this fully)
#include <io.h>      // For file searching

using namespace std;
void displayMenu();
void listAllFiles();
void createDirectory();
void changeDirectory();

int main() {
    int choice = 0;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                listAllFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Display the main menu
void displayMenu() {
    cout << "\nMAIN MENU\n";
    cout << "----------------------\n";
    cout << "1. Display List of Files\n";
    cout << "2. Create New Directory\n";
    cout << "3. Change the Working Directory\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// List all files in the current directory
void listAllFiles() {
    struct _finddata_t fileinfo;
    intptr_t handle;
    if ((handle = _findfirst("*.*", &fileinfo)) == -1L) {
        cout << "No files found in the current directory.\n";
    } else {
        do {
            cout << fileinfo.name << '\n';
        } while (_findnext(handle, &fileinfo) == 0);
        _findclose(handle);
    }
}

// Create a new directory in the current directory
void createDirectory() {
    string dirName;
    cout << "Enter the name of the new directory: ";
    cin >> dirName;

    if (_mkdir(dirName.c_str()) == 0) {
        cout << "Directory " << dirName << " created successfully.\n";
    } else {
        cout << "Failed to create directory. It may already exist.\n";
    }
}

// Change the current working directory
void changeDirectory() {
	string nullptr;
    char currentDir[FILENAME_MAX];
    if (_getcwd(currentDir, sizeof(currentDir)) == nullptr) {
        cerr << "Error getting current directory.\n";
        return;
    }

    cout << "Current Directory: " << currentDir << '\n';
    cout << "1. Step back one directory\n";
    cout << "2. Go to root directory\n";
    cout << "3. Enter a directory name\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    string dirName;
    switch (choice) {
        case 1:
            _chdir("..");
            break;
        case 2:
            _chdir("\\");
            break;
        case 3:
            cout << "Enter the directory name: ";
            cin >> dirName;
            if (_chdir(dirName.c_str()) != 0) {
                cout << "Directory does not exist.\n";
            }
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    if (_getcwd(currentDir, sizeof(currentDir)) != nullptr) {
        cout << "Current Directory: " << currentDir << '\n';
    }
}



