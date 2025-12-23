package main

import (
	"fmt"
	"log"

	"github.com/taskmanager/go-client/pkg/controller"
	"github.com/taskmanager/go-client/pkg/model"
)

// Main application entry point
// Demonstrates Go code dependencies:
//   - Uses controller.TaskController
//   - TaskController uses service.TaskService and api.TaskAPIClient
//   - TaskService uses util.NativeUtils (references native/utils.h)
//   - TaskAPIClient references backend/main.py (Python API)
//   - All packages use model.Task and model.Priority
func main() {
	fmt.Println("=== Task Manager Go Application ===\n")

	ctrl := controller.NewTaskController(true) // Use local service

	// Create some tasks
	fmt.Println("Creating tasks...")
	task1, err := ctrl.CreateTask(
		"Complete project documentation",
		"Write comprehensive documentation for the project",
		model.PriorityHigh,
	)
	if err != nil {
		log.Fatalf("Error creating task: %v", err)
	}
	fmt.Printf("Created: %+v\n", task1)

	task2, err := ctrl.CreateTask(
		"Review code changes",
		"Review all pending code changes",
		model.PriorityMedium,
	)
	if err != nil {
		log.Fatalf("Error creating task: %v", err)
	}
	fmt.Printf("Created: %+v\n", task2)

	task3, err := ctrl.CreateTask(
		"Urgent: Fix critical bug",
		"Fix the critical bug in production",
		model.PriorityHigh,
	)
	if err != nil {
		log.Fatalf("Error creating task: %v", err)
	}
	fmt.Printf("Created: %+v\n", task3)

	// Get all tasks
	fmt.Println("\nAll tasks:")
	tasks, err := ctrl.GetAllTasks()
	if err != nil {
		log.Fatalf("Error getting tasks: %v", err)
	}
	for _, task := range tasks {
		fmt.Printf("  - %s (Priority: %s, Completed: %v)\n", task.Title, task.Priority, task.Completed)
	}

	// Get statistics
	fmt.Println("\nTask Statistics:")
	stats, err := ctrl.GetStatistics()
	if err != nil {
		log.Fatalf("Error getting statistics: %v", err)
	}
	fmt.Printf("  Total: %d\n", stats.TotalTasks)
	fmt.Printf("  Completed: %d\n", stats.CompletedTasks)
	fmt.Printf("  Pending: %d\n", stats.PendingTasks)
	fmt.Printf("  Factorial Total: %d\n", stats.FactorialTotal)

	// Get tasks by priority
	fmt.Println("\nHigh priority tasks:")
	highPriorityTasks, err := ctrl.GetTasksByPriority(model.PriorityHigh)
	if err != nil {
		log.Fatalf("Error getting high priority tasks: %v", err)
	}
	for _, task := range highPriorityTasks {
		fmt.Printf("  - %s\n", task.Title)
	}

	// Update a task
	fmt.Println("\nUpdating task 1...")
	updatedTitle := "Complete project documentation (Updated)"
	update := &model.TaskUpdate{
		Title:     &updatedTitle,
		Completed: boolPtr(true),
	}
	updated, err := ctrl.UpdateTask(task1.ID, update)
	if err != nil {
		log.Fatalf("Error updating task: %v", err)
	}
	fmt.Printf("Updated: %+v\n", updated)

	// Final statistics
	fmt.Println("\nFinal Statistics:")
	finalStats, err := ctrl.GetStatistics()
	if err != nil {
		log.Fatalf("Error getting statistics: %v", err)
	}
	fmt.Printf("  Total: %d\n", finalStats.TotalTasks)
	fmt.Printf("  Completed: %d\n", finalStats.CompletedTasks)
	fmt.Printf("  Pending: %d\n", finalStats.PendingTasks)

	fmt.Println("\n=== Application Complete ===")
}

// Helper function to create bool pointer
func boolPtr(b bool) *bool {
	return &b
}

