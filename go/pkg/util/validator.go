package util

// TaskValidator provides validation utilities for tasks
// Used by: service.TaskService
type TaskValidator struct {
	minTitleLength int
	maxTitleLength int
	maxDescLength  int
}

const (
	MinTitleLength = 1
	MaxTitleLength = 200
	MaxDescLength  = 1000
)

// NewTaskValidator creates a new TaskValidator
func NewTaskValidator() *TaskValidator {
	return &TaskValidator{
		minTitleLength: MinTitleLength,
		maxTitleLength: MaxTitleLength,
		maxDescLength:  MaxDescLength,
	}
}

// ValidateTitle validates a task title
func (v *TaskValidator) ValidateTitle(title string) bool {
	if title == "" {
		return false
	}
	length := len(title)
	return length >= v.minTitleLength && length <= v.maxTitleLength
}

// ValidateDescription validates a task description
func (v *TaskValidator) ValidateDescription(description string) bool {
	if description == "" {
		return true // Description is optional
	}
	return len(description) <= v.maxDescLength
}

// ValidateID validates a task ID
func (v *TaskValidator) ValidateID(id int) bool {
	return id > 0
}

