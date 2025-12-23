package com.taskmanager.controller;

import com.taskmanager.model.Task;
import com.taskmanager.model.Priority;
import com.taskmanager.service.TaskService;
import com.taskmanager.api.TaskAPIClient;
import java.util.List;

/**
 * TaskController - Controller layer for task management
 * Dependencies:
 *   - TaskService (service layer)
 *   - TaskAPIClient (API client for Python backend)
 *   - Task, Priority (models)
 */
public class TaskController {
    private TaskService taskService;
    private TaskAPIClient apiClient;
    private boolean useLocalService;

    public TaskController() {
        this.taskService = new TaskService();
        this.apiClient = new TaskAPIClient();
        this.useLocalService = true; // Can switch between local and API
    }

    public TaskController(boolean useLocalService) {
        this();
        this.useLocalService = useLocalService;
    }

    /**
     * Create a new task
     */
    public Task createTask(String title, String description, Priority priority) {
        if (useLocalService) {
            return taskService.createTask(title, description, priority);
        } else {
            return apiClient.createTask(title, description, priority);
        }
    }

    /**
     * Get all tasks
     */
    public List<Task> getAllTasks() {
        if (useLocalService) {
            return taskService.getAllTasks();
        } else {
            return apiClient.getAllTasks();
        }
    }

    /**
     * Get task by ID
     */
    public Task getTaskById(int id) {
        if (useLocalService) {
            return taskService.getTaskById(id);
        } else {
            return apiClient.getTaskById(id);
        }
    }

    /**
     * Update task
     */
    public Task updateTask(int id, String title, String description, Boolean completed, Priority priority) {
        if (useLocalService) {
            return taskService.updateTask(id, title, description, completed, priority);
        } else {
            return apiClient.updateTask(id, title, description, completed, priority);
        }
    }

    /**
     * Delete task
     */
    public void deleteTask(int id) {
        if (useLocalService) {
            taskService.deleteTask(id);
        } else {
            apiClient.deleteTask(id);
        }
    }

    /**
     * Get tasks by priority
     */
    public List<Task> getTasksByPriority(Priority priority) {
        if (useLocalService) {
            return taskService.getTasksByPriority(priority);
        } else {
            // Filter from API results
            return apiClient.getAllTasks().stream()
                    .filter(t -> t.getPriority() == priority)
                    .toList();
        }
    }

    /**
     * Get statistics
     */
    public com.taskmanager.service.TaskStatistics getStatistics() {
        if (useLocalService) {
            return taskService.getStatistics();
        } else {
            // Calculate from API results
            List<Task> tasks = apiClient.getAllTasks();
            int total = tasks.size();
            int completed = (int) tasks.stream().filter(Task::isCompleted).count();
            return new com.taskmanager.service.TaskStatistics(
                total, completed, total - completed, 0
            );
        }
    }
}

