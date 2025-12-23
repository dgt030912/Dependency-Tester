package model

import "time"

// Task represents a task in the system
// References: backend/models.py (Python Task model)
//            frontend/src/types.ts (TypeScript Task interface)
//            java/src/main/java/com/taskmanager/model/Task.java (Java Task class)
type Task struct {
	ID          int       `json:"id"`
	Title       string    `json:"title"`
	Description string    `json:"description"`
	Completed   bool      `json:"completed"`
	Priority    Priority  `json:"priority"`
	CreatedAt   time.Time `json:"created_at"`
	UpdatedAt   time.Time `json:"updated_at"`
}

// TaskCreate represents the data needed to create a new task
// References: backend/models.py TaskCreate
type TaskCreate struct {
	Title       string   `json:"title"`
	Description string   `json:"description"`
	Completed   bool     `json:"completed"`
	Priority    Priority `json:"priority"`
}

// TaskUpdate represents the data needed to update a task
// References: backend/models.py TaskUpdate
type TaskUpdate struct {
	Title       *string   `json:"title,omitempty"`
	Description *string   `json:"description,omitempty"`
	Completed   *bool     `json:"completed,omitempty"`
	Priority    *Priority `json:"priority,omitempty"`
}

