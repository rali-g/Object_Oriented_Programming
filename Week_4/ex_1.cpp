#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning(disable : 4996)

class Task {
private:
    char name[20];
    char description[128];
    unsigned points;
public:

    Task()
    {
        Task("", "", 0);
    }

    Task(const char* name, const char* description, unsigned points)
    {
        strcpy(this->name, name);
        strcpy(this->description, description);
        this->points = points;
    }

    const char* getName() const
    {
        return name;
    }

    const char* getDescription() const
    {
        return description;
    }

    unsigned getPoints() const
    {
        return points;
    }

    void setName(const char* name)
    {
        strcpy(this->name, name);
    }

    void setDescription(const char* description)
    {
        strcpy(this->description, description);
    }

    void setPoints(unsigned points)
    {
        this->points = points;
    }

    void printTask()
    {
        std::cout << "Name: " << name << "\nDescription: " << description << "\nPoints: " << points;
    }
};

class Test {
private:
    Task tasks[100];
    unsigned size = 0;
    unsigned minPoints = 0;
    char password[20];
public:
    Test(const char* password) : size(0), minPoints(0)
    {
        strcpy(this->password, password);
    }

    Test(const Task* tasks, unsigned size, unsigned minPoints, const char* password)
    {
        this->size = size;
        for (int i = 0; i < size; i++)
        {
            this->tasks[i] = tasks[i];
        }
        this->minPoints = minPoints;
        strcpy(this->password, password);
    }

    void setPoints(unsigned minPoints)
    {
        this->minPoints = minPoints;
    }

    unsigned getPoints() const
    {
        return minPoints;
    }

    unsigned getSize() const
    {
        return size;
    }

    const Task* getTasks() const
    {
        return tasks;
    }

    void addTask(const Task& task, const char* password)
    {
        if (strcmp(this->password, password))
        {
            std::cout << "Wrong password" << std::endl;
            return;
        }
        if (size >= 100)
        {
            std::cout << "Array is full";
            return;
        }
        this->tasks[this->size++] = task;
    }

    void removeTaskByName(const char* name, const char* password)
    {
        if (strcmp(this->password, password))
        {
            std::cout << "Wrong password" << std::endl;
            return;
        }

        int index = size;
        bool elementExists = false;
        for (int i = 0; i < this->size; i++)
        {
            if (strcmp(this->tasks[i].getName(), name) == 0)
            {
                index = i;
                elementExists = true;
                break;
            }
        }
        
        for (int i = index; i < size - 1; i++)
        {
            std::swap(tasks[i], tasks[i + 1]);
        }
        if (elementExists)
        {
            size--;
        }
    }

    void printTest(const char* password)
    {
        if (strcmp(this->password, password))
        {
            std::cout << "Wrong password" << std::endl;
            return;
        }
        for (int i = 0; i < size; i++)
        {
            tasks[i].printTask();
            std::cout << std::endl;
        }
    }

    int maxPoints()
    {
        int maxPoints = 0;
        for (int i = 0; i < size; i++)
        {
            maxPoints += tasks[i].getPoints();
        }
        return maxPoints;
    }

    void writeInFile(const char* filePath)
    {
        std::ofstream ofs(filePath, std::ios::binary);
        if (!ofs.is_open())
        {
            return;
        }
        ofs.write((const char*)this, sizeof(Test));
        ofs.close();
    }

    void readFromFile(const char* filePath)
    {
        std::ifstream ifs(filePath, std::ios::binary);
        if (!ifs.is_open())
        {
            return;
        }
        ifs.read((char*)this, sizeof(Test));
        ifs.close();
    }

    void setPassword(const char* newPassword, const char* oldPassword)
    {
        if (strcmp(this->password, oldPassword) == 0)
        {
            strcpy(this->password, newPassword);
        }
    }
};

int main()
{
    Task task1{"points", "find distance", 5};
    Task task2{"equation", "find smth", 10};
    Task task3{"sum", "find sum", 12};
    
    Test test("1234");
    Test test2("1234");
    test.addTask(task1, "6746");
    test.addTask(task1, "1234");
    test.addTask(task2, "1234");
    test.addTask(task3, "1234");
    test.printTest("1234");
    std::cout << test.maxPoints();
    std::cout << std::endl;
    test.writeInFile("test.dat");
    test2.readFromFile("test.dat");

    test.removeTaskByName("points", "1234");
    test.printTest("1234");
    std::cout << std::endl;
    test2.printTest("1234");
}

