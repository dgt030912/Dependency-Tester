#include "task_processor.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>

// ============ Task Implementation ============

Task::Task(int id, const std::string& title, const std::string& desc, TaskPriority prio)
    : id(id), title(title), description(desc), priority(prio), 
      status(TaskStatus::PENDING), createdAt(0), completedAt(0) {
    auto now = std::chrono::system_clock::now();
    createdAt = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
}

// ============ TaskProcessor Implementation ============

TaskProcessor::TaskProcessor() 
    : nextId(1), processedCount(0), failedCount(0) {
    std::cout << "[TaskProcessor] Initialized" << std::endl;
}

TaskProcessor::~TaskProcessor() {
    std::cout << "[TaskProcessor] Destroyed. Stats: " 
              << processedCount << " processed, "
              << failedCount << " failed, "
              << getTotalCount() << " total" << std::endl;
}

long long TaskProcessor::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
}

void TaskProcessor::updateCounts() {
    priorityCount.clear();
    statusCount.clear();
    
    for (const auto& task : tasks) {
        priorityCount[task->priority]++;
        statusCount[task->status]++;
    }
}

// Task management
int TaskProcessor::addTask(const std::string& title, const std::string& description,
                           TaskPriority priority) {
    auto task = std::make_shared<Task>(nextId++, title, description, priority);
    tasks.push_back(task);
    updateCounts();
    
    std::cout << "[TaskProcessor] Added task #" << task->id 
              << ": " << title 
              << " [" << priorityToString(priority) << "]" << std::endl;
    
    return task->id;
}

bool TaskProcessor::removeTask(int taskId) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                          [taskId](const std::shared_ptr<Task>& t) { 
                              return t->id == taskId; 
                          });
    
    if (it != tasks.end()) {
        std::cout << "[TaskProcessor] Removed task #" << taskId << std::endl;
        tasks.erase(it);
        updateCounts();
        return true;
    }
    
    std::cerr << "[TaskProcessor] Task #" << taskId << " not found" << std::endl;
    return false;
}

bool TaskProcessor::updateTaskStatus(int taskId, TaskStatus status) {
    auto task = getTask(taskId);
    if (task) {
        task->status = status;
        if (status == TaskStatus::COMPLETED || status == TaskStatus::FAILED) {
            task->completedAt = getCurrentTimestamp();
        }
        updateCounts();
        
        std::cout << "[TaskProcessor] Task #" << taskId 
                  << " status updated to " << statusToString(status) << std::endl;
        return true;
    }
    return false;
}

bool TaskProcessor::updateTaskPriority(int taskId, TaskPriority priority) {
    auto task = getTask(taskId);
    if (task) {
        task->priority = priority;
        updateCounts();
        
        std::cout << "[TaskProcessor] Task #" << taskId 
                  << " priority updated to " << priorityToString(priority) << std::endl;
        return true;
    }
    return false;
}

// Processing
void TaskProcessor::processTask(int taskId) {
    auto task = getTask(taskId);
    if (!task) {
        std::cerr << "[TaskProcessor] Cannot process task #" << taskId 
                  << " - not found" << std::endl;
        return;
    }
    
    if (task->status != TaskStatus::PENDING) {
        std::cout << "[TaskProcessor] Task #" << taskId 
                  << " already processed (status: " 
                  << statusToString(task->status) << ")" << std::endl;
        return;
    }
    
    std::cout << "[TaskProcessor] Processing task #" << taskId 
              << ": " << task->title << std::endl;
    
    updateTaskStatus(taskId, TaskStatus::IN_PROGRESS);
    
    // Simulate processing based on priority
    bool success = true; // In real scenario, this would be actual processing logic
    
    if (success) {
        updateTaskStatus(taskId, TaskStatus::COMPLETED);
        processedCount++;
        std::cout << "[TaskProcessor] Task #" << taskId << " completed successfully" << std::endl;
    } else {
        updateTaskStatus(taskId, TaskStatus::FAILED);
        failedCount++;
        std::cerr << "[TaskProcessor] Task #" << taskId << " failed" << std::endl;
    }
}

void TaskProcessor::processAll() {
    std::cout << "[TaskProcessor] Processing all " << tasks.size() << " tasks..." << std::endl;
    
    // Process by priority: CRITICAL -> HIGH -> MEDIUM -> LOW
    processByPriority(TaskPriority::CRITICAL);
    processByPriority(TaskPriority::HIGH);
    processByPriority(TaskPriority::MEDIUM);
    processByPriority(TaskPriority::LOW);
    
    std::cout << "[TaskProcessor] Batch processing complete. "
              << processedCount << " successful, "
              << failedCount << " failed" << std::endl;
}

void TaskProcessor::processByPriority(TaskPriority priority) {
    auto priorityTasks = getTasksByPriority(priority);
    for (const auto& task : priorityTasks) {
        if (task->status == TaskStatus::PENDING) {
            processTask(task->id);
        }
    }
}

// Query methods
std::shared_ptr<Task> TaskProcessor::getTask(int taskId) const {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                          [taskId](const std::shared_ptr<Task>& t) { 
                              return t->id == taskId; 
                          });
    return (it != tasks.end()) ? *it : nullptr;
}

std::vector<std::shared_ptr<Task>> TaskProcessor::getAllTasks() const {
    return tasks;
}

std::vector<std::shared_ptr<Task>> TaskProcessor::getTasksByStatus(TaskStatus status) const {
    std::vector<std::shared_ptr<Task>> filtered;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(filtered),
                [status](const std::shared_ptr<Task>& t) { 
                    return t->status == status; 
                });
    return filtered;
}

std::vector<std::shared_ptr<Task>> TaskProcessor::getTasksByPriority(TaskPriority priority) const {
    std::vector<std::shared_ptr<Task>> filtered;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(filtered),
                [priority](const std::shared_ptr<Task>& t) { 
                    return t->priority == priority; 
                });
    return filtered;
}

// Statistics
int TaskProcessor::getProcessedCount() const {
    return processedCount;
}

int TaskProcessor::getFailedCount() const {
    return failedCount;
}

int TaskProcessor::getTotalCount() const {
    return static_cast<int>(tasks.size());
}

int TaskProcessor::getPendingCount() const {
    return static_cast<int>(getTasksByStatus(TaskStatus::PENDING).size());
}

std::map<TaskPriority, int> TaskProcessor::getPriorityStats() const {
    return priorityCount;
}

std::map<TaskStatus, int> TaskProcessor::getStatusStats() const {
    return statusCount;
}

// Utility
void TaskProcessor::clearTasks() {
    tasks.clear();
    updateCounts();
    std::cout << "[TaskProcessor] All tasks cleared" << std::endl;
}

void TaskProcessor::clearCompleted() {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                            [](const std::shared_ptr<Task>& t) {
                                return t->status == TaskStatus::COMPLETED;
                            });
    size_t removed = std::distance(it, tasks.end());
    tasks.erase(it, tasks.end());
    updateCounts();
    
    std::cout << "[TaskProcessor] Cleared " << removed << " completed tasks" << std::endl;
}

std::string TaskProcessor::getTaskSummary() const {
    std::ostringstream oss;
    oss << "\n=== Task Processor Summary ===\n";
    oss << "Total Tasks: " << getTotalCount() << "\n";
    oss << "Processed: " << processedCount << "\n";
    oss << "Failed: " << failedCount << "\n";
    oss << "Pending: " << getPendingCount() << "\n\n";
    
    oss << "By Priority:\n";
    for (const auto& [priority, count] : priorityCount) {
        oss << "  " << priorityToString(priority) << ": " << count << "\n";
    }
    
    oss << "\nBy Status:\n";
    for (const auto& [status, count] : statusCount) {
        oss << "  " << statusToString(status) << ": " << count << "\n";
    }
    oss << "============================\n";
    
    return oss.str();
}

// ============ Helper Functions ============

std::string priorityToString(TaskPriority priority) {
    switch (priority) {
        case TaskPriority::LOW: return "LOW";
        case TaskPriority::MEDIUM: return "MEDIUM";
        case TaskPriority::HIGH: return "HIGH";
        case TaskPriority::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

std::string statusToString(TaskStatus status) {
    switch (status) {
        case TaskStatus::PENDING: return "PENDING";
        case TaskStatus::IN_PROGRESS: return "IN_PROGRESS";
        case TaskStatus::COMPLETED: return "COMPLETED";
        case TaskStatus::FAILED: return "FAILED";
        default: return "UNKNOWN";
    }
}

TaskPriority stringToPriority(const std::string& str) {
    if (str == "LOW") return TaskPriority::LOW;
    if (str == "HIGH") return TaskPriority::HIGH;
    if (str == "CRITICAL") return TaskPriority::CRITICAL;
    return TaskPriority::MEDIUM;
}

TaskStatus stringToStatus(const std::string& str) {
    if (str == "PENDING") return TaskStatus::PENDING;
    if (str == "IN_PROGRESS") return TaskStatus::IN_PROGRESS;
    if (str == "COMPLETED") return TaskStatus::COMPLETED;
    if (str == "FAILED") return TaskStatus::FAILED;
    return TaskStatus::PENDING;
}
