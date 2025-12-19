#ifndef TASK_PROCESSOR_H
#define TASK_PROCESSOR_H

#include <string>
#include <vector>

class TaskProcessor {
private:
    std::vector<std::string> tasks;
    int taskCount;

public:
    TaskProcessor();
    void addTask(const std::string& task);
    int getTaskCount() const;
    std::vector<std::string> getTasks() const;
    bool removeTask(int index);
    void sortTasks();
    std::vector<int> findTasks(const std::string& searchTerm);
    void clear();
    std::string toString() const;
};

int calculatePriorityScore(const std::string& task, int length);
std::string getCurrentTimestamp();

#endif // TASK_PROCESSOR_H

