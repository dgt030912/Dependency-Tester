#include <iostream>
#include "task_processor.h"

/**
 * Example C++ program demonstrating TaskProcessor usage
 */
int main() {
    std::cout << "=== Task Processor Demo ===\n\n";
    
    TaskProcessor processor;
    
    // Add some tasks
    processor.addTask("Complete project documentation");
    processor.addTask("Review code changes");
    processor.addTask("Urgent: Fix critical bug");
    processor.addTask("Important: Update dependencies");
    processor.addTask("High priority: Deploy to production");
    
    std::cout << processor.toString() << "\n";
    
    // Sort tasks
    std::cout << "Sorting tasks...\n";
    processor.sortTasks();
    std::cout << processor.toString() << "\n";
    
    // Find tasks
    std::cout << "Searching for 'urgent' tasks:\n";
    std::vector<int> urgentTasks = processor.findTasks("urgent");
    for (int idx : urgentTasks) {
        std::cout << "  Found at index: " << idx << "\n";
    }
    
    // Calculate priority scores
    std::cout << "\nPriority Scores:\n";
    for (const auto& task : processor.getTasks()) {
        int score = calculatePriorityScore(task, task.length());
        std::cout << "  \"" << task << "\": " << score << "\n";
    }
    
    std::cout << "\nCurrent timestamp: " << getCurrentTimestamp() << "\n";
    
    return 0;
}

