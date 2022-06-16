#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>
#include <ctime> 
#include <climits>

using namespace std;
bool RUN = true;

int amountOfLines()
{
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile("tasks.txt");
    while (std::getline(myfile, line))
        ++number_of_lines;

    return number_of_lines;
}

int taskCounter = amountOfLines();

void initialScreen();
void clearScreen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    system("cls");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void writeToFile(string line)
{
    clearScreen();
    ofstream MyFile("tasks.txt", fstream::app);
    string task;
    taskCounter++;
    cout << "Dodac date utworzenia zadania?" << endl;
    cout << "1.Tak 2. Nie" << endl;
    int input;
    cin >> input;
    if (input ==1 )
    {
        std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        task=to_string(taskCounter) + ". " + line + " " + "data dodania: " + ctime(&currentTime) + "\n";

    }
    else
    {
        task=to_string(taskCounter) + ". " + line + " "  + "\n";
    }
    MyFile << task;
    MyFile.close();
}

void displayTasks()
{
    clearScreen();
    ifstream infile("tasks.txt");
    string line;
    while (std::getline(infile, line))
    {
        cout << line << endl;
    }      
    getchar();

}

void displayFinishedTasks()
{
    clearScreen();
    ifstream infile("finished.txt");
    string line;
    while (std::getline(infile, line))
    {
        cout << line << endl;
    }      
    cout << "wcisnij guzik aby powrocic do menu";

    getchar();

}

void addNewTask()
{
    clearScreen();
    cout << "Wpisz swoje zadanie : " << endl;
    string task;
    // cin.ignore(256, '\n');
    std::getline(cin >>std::ws, task);
    writeToFile(task);
    clearScreen();
    cout << "Czy chcesz dodać kolejne zadanie : " << endl;
    cout << "1.Tak 2. Nie" <<endl;
    int ingut;
    cin >> ingut;
    while (cin.fail())
    {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << "You can only enter numbers.\n";
        cout << "Enter a number.\n";
        cin >> ingut;
    }
    if (ingut == 1)
    {
        addNewTask();
    }
    else
    {
        initialScreen();
    }
}

void removeTask(int id)
{
    ifstream fin("tasks.txt");
    ofstream temp;
    ofstream finished;
    string line;
    temp.open("temp.txt");
    finished.open("finished.txt", fstream::app);

    while (getline(fin, line)) {
        string firstCharacter{line[0]};
        if (firstCharacter != to_string(id))
        {
            temp << line << std::endl;
        }
        else
        {
            string task;
            cout << "Dodac date zakonczenia zadania?" << endl;
            cout << "1.Tak 2. Nie" << endl;
            int input;
            cin >> input;
            while (cin.fail())
            {
                cin.clear(); // clear input buffer to restore cin to a usable state
                cin.ignore(INT_MAX, '\n'); // ignore last input
                cout << "You can only enter numbers.\n";
                cout << "Enter a number.\n";
                cin >> input;
            }
            if (input ==1 )
            {
                std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                task=line + " " + "data zakonczenia: " + ctime(&currentTime) + "\n";
            }
            else
            {
                cin.clear();
                task = line;
            }
            finished << task << std::endl;
        }
    }
    temp.close();
    fin.close();
    remove("tasks.txt");
    rename("temp.txt", "tasks.txt");
}

void initialScreen()
{
    clearScreen();
    cout <<"############################"<<endl;
    cout <<"############################"<<endl;
    cout <<"############################"<<endl;

    cout << "Co chcesz zrobić?:     " << endl;
    cout << "1.Dodaj nowe zadanie \n2. Usun zadanie \n3. Przegladaj zadania \n4. zamknij \n5. Przegladaj skonczone zadania" <<endl;

    cout <<"############################"<<endl;
    cout <<"############################"<<endl;
    cout <<"############################"<<endl;
    int input;
    cin >> input;
    while (cin.fail())
    {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << "You can only enter numbers.\n";
        cout << "Enter a number.\n";
        cin >> input;
    }
    if (input ==4)
    {
        RUN = false;
    }
    else if (input == 1)
    {
        addNewTask();
    }

    else if (input == 2)
    {
        displayTasks();
        cout << "Ktore zadanie usunac";
        int id;
        cin >> id;
        removeTask(id);
    }
    else if (input == 3)
    {
        displayTasks();
        cout << "wcisnij guzik aby powrocic do menu";

        getchar();
    }
    else  if (input == 5)
    {
        displayFinishedTasks();
        cout << "wcisnij guzik aby powrocic do menu";
        getchar();
    }
    else 
    {
        initialScreen();
    }
}


int main()
{
    while (RUN)
    {
        initialScreen();
    }
    
    return 0;
}