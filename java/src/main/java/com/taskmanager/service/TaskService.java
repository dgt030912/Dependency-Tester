package com.taskmanager.service;

import com.taskmanager.model.Task;
import com.taskmanager.model.Priority;
import com.taskmanager.util.NativeUtils;
import com.taskmanager.util.TaskValidator;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * TaskService - Business logic for task management
 * Dependencies:
 *   - Task (model)
 *   - Priority (model)
 *   - NativeUtils (utility - references native/utils.h)
 *   - TaskValidator (utility)
 */
public class TaskService {
    private List<Task> tasks;
    private TaskValidator validator;
    private NativeUtils nativeUtils;

    public TaskService() {
        this.tasks = new ArrayList<>();
        this.validator = new TaskValidator();
        this.nativeUtils = new NativeUtils();
    }

    /**
     * Create a new task with validation and priority scoring
     */
    public Task createTask(String title, String description, Priority priority) {
        if (!validator.validateTitle(title)) {
            throw new IllegalArgumentException("Invalid task title");
        }

        int newId = tasks.isEmpty() ? 1 : tasks.stream()
                .mapToInt(Task::getId)
                .max()
                .orElse(0) + 1;

        Task task = new Task(newId, title, description, false, priority);
        
        // Use native utility to calculate priority score
        int priorityScore = nativeUtils.calculatePriorityScore(title, description);
        task.setPriority(adjustPriorityByScore(priority, priorityScore));
        
        tasks.add(task);
        return task;
    }

    /**
     * Get all tasks
     */
    public List<Task> getAllTasks() {
        return new ArrayList<>(tasks);
    }

    /**
     * Get task by ID
     */
    public Task getTaskById(int id) {
        return tasks.stream()
                .filter(t -> t.getId() == id)
                .findFirst()
                .orElseThrow(() -> new IllegalArgumentException("Task not found: " + id));
    }

    /**
     * Update task
     */
    public Task updateTask(int id, String title, String description, Boolean completed, Priority priority) {
        Task task = getTaskById(id);
        
        if (title != null) {
            if (!validator.validateTitle(title)) {
                throw new IllegalArgumentException("Invalid task title");
            }
            task.setTitle(title);
        }
        
        if (description != null) {
            task.setDescription(description);
        }
        
        if (completed != null) {
            task.setCompleted(completed);
        }
        
        if (priority != null) {
            task.setPriority(priority);
        }
        
        return task;
    }

    /**
     * Delete task
     */
    public void deleteTask(int id) {
        Task task = getTaskById(id);
        tasks.remove(task);
    }

    /**
     * Get tasks by priority
     */
    public List<Task> getTasksByPriority(Priority priority) {
        return tasks.stream()
                .filter(t -> t.getPriority() == priority)
                .collect(Collectors.toList());
    }

    /**
     * Get completed tasks
     */
    public List<Task> getCompletedTasks() {
        return tasks.stream()
                .filter(Task::isCompleted)
                .collect(Collectors.toList());
    }

    /**
     * Calculate statistics using native utilities
     */
    public TaskStatistics getStatistics() {
        int total = tasks.size();
        int completed = (int) tasks.stream().filter(Task::isCompleted).count();
        
        // Use native factorial for some calculation
        long factorialTotal = nativeUtils.factorial(total);
        
        return new TaskStatistics(total, completed, total - completed, factorialTotal);
    }

    private Priority adjustPriorityByScore(Priority original, int score) {
        if (score > 50 && original != Priority.HIGH) {
            return Priority.HIGH;
        } else if (score < 20 && original != Priority.LOW) {
            return Priority.LOW;
        }
        return original;
    }
}

