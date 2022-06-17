#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>
#include <ctime> 
#include <climits>
#include <vector>

using namespace std;
bool RUN = true;
int amountOfLines(string name)
{
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(name);
    while (std::getline(myfile, line))
        ++number_of_lines;

    return number_of_lines;
}
int taskCounter = amountOfLines("tasks.txt");

class Display
{
public:
    void clearScreen()
    {
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }
    int createDate()
    {
        cout << "Dodac date utworzenia zadania?" << endl;
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
        return input;
    }
    int deleteDate()
    {
        cout << "Dodac date utworzenia zadania?" << endl;
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
        return input;
    }
    string addDate()
    {
        std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return ctime(&currentTime);
    }

    string getTask()
    {
        clearScreen();
        cout << "Wpisz swoje zadanie : " << endl;
        string task;
        std::getline(cin >>std::ws, task);
        return(task);
    }
    void pressButtonToContinue()
    {
        cout << "wcisnij guzik aby kontynuowac";
        getchar(); 
        getchar();
    }
    void displayTasks(vector<string> tasks)
    {
        clearScreen();
        for( const auto &task : tasks)
        {
            cout << task << endl;
        }

    }
    int getIdTask()
    {
        cout << "Ktore zadanie usunac";
        int id;
        cin >> id;
        while (cin.fail())
        {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "You can only enter numbers.\n";
            cout << "Enter a number.\n";
            cin >> id;
        }
        return id;
    }
    int addAgain()
    {
        cout << "Czy chcesz dodać kolejne zadanie : " << endl;
        cout << "1.Tak 2. Nie" <<endl;
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
        return input;
    }
    int initialScreen()
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
        return 4;
    }
    else
        return input;
}
private:

};


class File
{
public:
    void writeToFile(string line, string date)
    {
        ofstream MyFile("tasks.txt", fstream::app);
        string task;
        taskCounter++;
        task = to_string(taskCounter) + ". " + line + " " + "data dodania: " + date + "\n";
        MyFile << task;
        MyFile.close();
    }
    void removeTask(int id, string date)
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
                task = line + " " + "data ukonczenia: " + date + "\n";
                finished << task << std::endl;
            }
        }

        temp.close();
        fin.close();
        remove("tasks.txt");
        rename("temp.txt", "tasks.txt");        
    }
    std::vector<string> readTasks(string fileName)
    {
        ifstream infile(fileName);
        vector<string> result;
        string line;
        while (std::getline(infile, line))
        {
            result.push_back(line);
        }
        return result;
    }

};




class ListaToDo
{
public:
    ListaToDo()
    {
        file = File();
        display = Display();
    }
    void addNewTask()
    {
        auto task = display.getTask();
        string date = "";
        if (display.createDate() ==1)
            date = display.addDate();
        file.writeToFile(task, date);
    }

    void logic()
    {
        auto action = display.initialScreen();
        switch(action)
        {
            case 1:
            {
                addNewTask();
                if (display.addAgain() == 1)
                {
                    addNewTask();
                }
                break;
            }
            case 2:
                {
                    auto tasks = file.readTasks("tasks.txt");
                    display.displayTasks(tasks);
                    auto id = display.getIdTask();
                    string date = "";
                    if (display.deleteDate())
                        date = display.addDate();
                    file.removeTask(id, date);
                    break;
                }
            case 3:
            {
                auto tasks = file.readTasks("tasks.txt");
                display.displayTasks(tasks);
                display.pressButtonToContinue();
                break;
            }
            
            case 4:
            {
                RUN = false;
                break;
            }
            case 5:
            {
                auto tasks = file.readTasks("finished.txt");
                display.displayTasks(tasks);
                break;
            }
            default:
                logic();
        }
    }

private:
    File file;
    Display display;

};


int main(int argc, const char** argv) {
    auto lista = ListaToDo();
    while (RUN)
    {
        lista.logic();
    }

    return 0;
}