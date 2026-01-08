#ifndef TASK_PROCESSOR_H
#define TASK_PROCESSOR_H

#include <string>
#include <vector>
#include <map>
#include <memory>

// Task priority levels
enum class TaskPriority {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

// Task status
enum class TaskStatus {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    FAILED
};

// Task structure
struct Task {
    int id;
    std::string title;
    std::string description;
    TaskPriority priority;
    TaskStatus status;
    long long createdAt;
    long long completedAt;
    
    Task(int id, const std::string& title, const std::string& desc = "", 
         TaskPriority prio = TaskPriority::MEDIUM);
};

// Task processor class
class TaskProcessor {
private:
    std::vector<std::shared_ptr<Task>> tasks;
    std::map<TaskPriority, int> priorityCount;
    std::map<TaskStatus, int> statusCount;
    int nextId;
    int processedCount;
    int failedCount;

    void updateCounts();
    long long getCurrentTimestamp() const;

public:
    TaskProcessor();
    ~TaskProcessor();
    
    // Task management
    int addTask(const std::string& title, const std::string& description = "",
                TaskPriority priority = TaskPriority::MEDIUM);
    bool removeTask(int taskId);
    bool updateTaskStatus(int taskId, TaskStatus status);
    bool updateTaskPriority(int taskId, TaskPriority priority);
    
    // Processing
    void processTask(int taskId);
    void processAll();
    void processByPriority(TaskPriority priority);
    
    // Query methods
    std::shared_ptr<Task> getTask(int taskId) const;
    std::vector<std::shared_ptr<Task>> getAllTasks() const;
    std::vector<std::shared_ptr<Task>> getTasksByStatus(TaskStatus status) const;
    std::vector<std::shared_ptr<Task>> getTasksByPriority(TaskPriority priority) const;
    
    // Statistics
    int getProcessedCount() const;
    int getFailedCount() const;
    int getTotalCount() const;
    int getPendingCount() const;
    std::map<TaskPriority, int> getPriorityStats() const;
    std::map<TaskStatus, int> getStatusStats() const;
    
    // Utility
    void clearTasks();
    void clearCompleted();
    std::string getTaskSummary() const;
};

// Helper functions
std::string priorityToString(TaskPriority priority);
std::string statusToString(TaskStatus status);
TaskPriority stringToPriority(const std::string& str);
TaskStatus stringToStatus(const std::string& str);

#endif // TASK_PROCESSOR_H
