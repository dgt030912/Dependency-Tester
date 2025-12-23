package com.taskmanager.model;

/**
 * Priority enum
 * References: backend/models.py (Python Priority enum)
 *            frontend/src/types.ts (TypeScript Priority enum)
 */
public enum Priority {
    LOW("low"),
    MEDIUM("medium"),
    HIGH("high");

    private final String value;

    Priority(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public static Priority fromString(String value) {
        for (Priority priority : Priority.values()) {
            if (priority.value.equalsIgnoreCase(value)) {
                return priority;
            }
        }
        return MEDIUM; // Default
    }
}

