package com.taskmanager.service;

/**
 * TaskStatistics - Statistics data class
 * Used by: TaskService
 */
public class TaskStatistics {
    private int totalTasks;
    private int completedTasks;
    private int pendingTasks;
    private long factorialTotal;

    public TaskStatistics(int totalTasks, int completedTasks, int pendingTasks, long factorialTotal) {
        this.totalTasks = totalTasks;
        this.completedTasks = completedTasks;
        this.pendingTasks = pendingTasks;
        this.factorialTotal = factorialTotal;
    }

    public int getTotalTasks() {
        return totalTasks;
    }

    public int getCompletedTasks() {
        return completedTasks;
    }

    public int getPendingTasks() {
        return pendingTasks;
    }

    public long getFactorialTotal() {
        return factorialTotal;
    }

    @Override
    public String toString() {
        return "TaskStatistics{" +
                "totalTasks=" + totalTasks +
                ", completedTasks=" + completedTasks +
                ", pendingTasks=" + pendingTasks +
                ", factorialTotal=" + factorialTotal +
                '}';
    }
}

