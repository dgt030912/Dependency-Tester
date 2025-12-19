#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>

/**
 * Task Processor - C++ utility for processing tasks
 */

class TaskProcessor {
private:
    std::vector<std::string> tasks;
    int taskCount;

public:
    TaskProcessor() : taskCount(0) {}
    
    /**
     * Add a task to the processor
     */
    void addTask(const std::string& task) {
        tasks.push_back(task);
        taskCount++;
    }
    
    /**
     * Get total number of tasks
     */
    int getTaskCount() const {
        return taskCount;
    }
    
    /**
     * Get all tasks as a vector
     */
    std::vector<std::string> getTasks() const {
        return tasks;
    }
    
    /**
     * Remove a task by index
     */
    bool removeTask(int index) {
        if (index >= 0 && index < static_cast<int>(tasks.size())) {
            tasks.erase(tasks.begin() + index);
            taskCount--;
            return true;
        }
        return false;
    }
    
    /**
     * Sort tasks alphabetically
     */
    void sortTasks() {
        std::sort(tasks.begin(), tasks.end());
    }
    
    /**
     * Find tasks containing a substring
     */
    std::vector<int> findTasks(const std::string& searchTerm) {
        std::vector<int> indices;
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].find(searchTerm) != std::string::npos) {
                indices.push_back(static_cast<int>(i));
            }
        }
        return indices;
    }
    
    /**
     * Clear all tasks
     */
    void clear() {
        tasks.clear();
        taskCount = 0;
    }
    
    /**
     * Get formatted task list as string
     */
    std::string toString() const {
        std::ostringstream oss;
        oss << "Tasks (" << taskCount << "):\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            oss << "  " << (i + 1) << ". " << tasks[i] << "\n";
        }
        return oss.str();
    }
};

/**
 * Calculate priority score based on task properties
 */
int calculatePriorityScore(const std::string& task, int length) {
    int score = 0;
    
    // Base score on length
    score += length * 2;
    
    // Check for priority keywords
    std::string lowerTask = task;
    std::transform(lowerTask.begin(), lowerTask.end(), lowerTask.begin(), ::tolower);
    
    if (lowerTask.find("urgent") != std::string::npos) {
        score += 50;
    }
    if (lowerTask.find("important") != std::string::npos) {
        score += 30;
    }
    if (lowerTask.find("high") != std::string::npos) {
        score += 20;
    }
    
    return score;
}

/**
 * Format timestamp as string
 */
std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

