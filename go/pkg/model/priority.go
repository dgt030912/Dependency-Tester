package model

// Priority represents task priority levels
// References: backend/models.py Priority enum
//            frontend/src/types.ts Priority enum
//            java/src/main/java/com/taskmanager/model/Priority.java
type Priority string

const (
	PriorityLow    Priority = "low"
	PriorityMedium Priority = "medium"
	PriorityHigh   Priority = "high"
)

// String returns the string representation of Priority
func (p Priority) String() string {
	return string(p)
}

// FromString creates a Priority from a string value
func PriorityFromString(s string) Priority {
	switch s {
	case "low":
		return PriorityLow
	case "high":
		return PriorityHigh
	default:
		return PriorityMedium
	}
}

