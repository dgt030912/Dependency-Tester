package com.taskmanager;

import com.taskmanager.controller.TaskController;
import com.taskmanager.model.Task;
import com.taskmanager.model.Priority;
import com.taskmanager.service.TaskStatistics;

/**
 * Main application entry point
 * Demonstrates Java code dependencies:
 *   - Uses TaskController
 *   - TaskController uses TaskService and TaskAPIClient
 *   - TaskService uses NativeUtils (references native/utils.h)
 *   - TaskAPIClient references backend/main.py (Python API)
 *   - All classes use Task and Priority models
 */
public class Main {
    public static void main(String[] args) {
        System.out.println("=== Task Manager Java Application ===\n");

        TaskController controller = new TaskController(true); // Use local service

        try {
            // Create some tasks
            System.out.println("Creating tasks...");
            Task task1 = controller.createTask(
                "Complete project documentation",
                "Write comprehensive documentation for the project",
                Priority.HIGH
            );
            System.out.println("Created: " + task1);

            Task task2 = controller.createTask(
                "Review code changes",
                "Review all pending code changes",
                Priority.MEDIUM
            );
            System.out.println("Created: " + task2);

            Task task3 = controller.createTask(
                "Urgent: Fix critical bug",
                "Fix the critical bug in production",
                Priority.HIGH
            );
            System.out.println("Created: " + task3);

            // Get all tasks
            System.out.println("\nAll tasks:");
            controller.getAllTasks().forEach(System.out::println);

            // Get statistics
            System.out.println("\nTask Statistics:");
            TaskStatistics stats = controller.getStatistics();
            System.out.println(stats);

            // Get tasks by priority
            System.out.println("\nHigh priority tasks:");
            controller.getTasksByPriority(Priority.HIGH).forEach(System.out::println);

            // Update a task
            System.out.println("\nUpdating task 1...");
            Task updated = controller.updateTask(
                task1.getId(),
                "Complete project documentation (Updated)",
                null,
                true,
                null
            );
            System.out.println("Updated: " + updated);

            // Final statistics
            System.out.println("\nFinal Statistics:");
            System.out.println(controller.getStatistics());

        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

