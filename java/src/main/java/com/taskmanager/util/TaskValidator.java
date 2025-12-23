package com.taskmanager.util;

/**
 * TaskValidator - Validation utilities for tasks
 * Used by: TaskService
 */
public class TaskValidator {
    
    private static final int MIN_TITLE_LENGTH = 1;
    private static final int MAX_TITLE_LENGTH = 200;
    private static final int MAX_DESCRIPTION_LENGTH = 1000;

    /**
     * Validate task title
     */
    public boolean validateTitle(String title) {
        if (title == null || title.trim().isEmpty()) {
            return false;
        }
        
        int length = title.trim().length();
        return length >= MIN_TITLE_LENGTH && length <= MAX_TITLE_LENGTH;
    }

    /**
     * Validate task description
     */
    public boolean validateDescription(String description) {
        if (description == null) {
            return true; // Description is optional
        }
        
        return description.length() <= MAX_DESCRIPTION_LENGTH;
    }

    /**
     * Validate task ID
     */
    public boolean validateId(int id) {
        return id > 0;
    }
}

