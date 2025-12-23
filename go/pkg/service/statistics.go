package service

// TaskStatistics holds task statistics
// Used by: TaskService
type TaskStatistics struct {
	TotalTasks     int   `json:"total_tasks"`
	CompletedTasks int   `json:"completed_tasks"`
	PendingTasks   int   `json:"pending_tasks"`
	FactorialTotal int64 `json:"factorial_total"`
}

