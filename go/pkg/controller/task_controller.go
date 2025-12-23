package controller

import (
	"github.com/taskmanager/go-client/pkg/api"
	"github.com/taskmanager/go-client/pkg/model"
	"github.com/taskmanager/go-client/pkg/service"
)

// TaskController handles task operations
// Dependencies:
//   - service.TaskService (local service)
//   - api.TaskAPIClient (API client for Python backend)
//   - model package (Task, Priority, TaskUpdate)
type TaskController struct {
	taskService *service.TaskService
	apiClient   *api.TaskAPIClient
	useLocal    bool
}

// NewTaskController creates a new TaskController
func NewTaskController(useLocal bool) *TaskController {
	return &TaskController{
		taskService: service.NewTaskService(),
		apiClient:   api.NewTaskAPIClient(),
		useLocal:    useLocal,
	}
}

// CreateTask creates a new task
func (c *TaskController) CreateTask(title, description string, priority model.Priority) (*model.Task, error) {
	if c.useLocal {
		return c.taskService.CreateTask(title, description, priority)
	} else {
		create := &model.TaskCreate{
			Title:       title,
			Description: description,
			Completed:   false,
			Priority:    priority,
		}
		return c.apiClient.CreateTask(create)
	}
}

// GetAllTasks returns all tasks
func (c *TaskController) GetAllTasks() ([]*model.Task, error) {
	if c.useLocal {
		return c.taskService.GetAllTasks(), nil
	} else {
		return c.apiClient.GetAllTasks()
	}
}

// GetTaskByID returns a task by ID
func (c *TaskController) GetTaskByID(id int) (*model.Task, error) {
	if c.useLocal {
		return c.taskService.GetTaskByID(id)
	} else {
		return c.apiClient.GetTaskByID(id)
	}
}

// UpdateTask updates a task
func (c *TaskController) UpdateTask(id int, update *model.TaskUpdate) (*model.Task, error) {
	if c.useLocal {
		return c.taskService.UpdateTask(id, update)
	} else {
		return c.apiClient.UpdateTask(id, update)
	}
}

// DeleteTask deletes a task
func (c *TaskController) DeleteTask(id int) error {
	if c.useLocal {
		return c.taskService.DeleteTask(id)
	} else {
		return c.apiClient.DeleteTask(id)
	}
}

// GetTasksByPriority returns tasks filtered by priority
func (c *TaskController) GetTasksByPriority(priority model.Priority) ([]*model.Task, error) {
	if c.useLocal {
		return c.taskService.GetTasksByPriority(priority), nil
	} else {
		tasks, err := c.apiClient.GetAllTasks()
		if err != nil {
			return nil, err
		}
		var filtered []*model.Task
		for _, task := range tasks {
			if task.Priority == priority {
				filtered = append(filtered, task)
			}
		}
		return filtered, nil
	}
}

// GetStatistics returns task statistics
func (c *TaskController) GetStatistics() (*service.TaskStatistics, error) {
	if c.useLocal {
		return c.taskService.GetStatistics(), nil
	} else {
		tasks, err := c.apiClient.GetAllTasks()
		if err != nil {
			return nil, err
		}
		total := len(tasks)
		completed := 0
		for _, task := range tasks {
			if task.Completed {
				completed++
			}
		}
		return &service.TaskStatistics{
			TotalTasks:     total,
			CompletedTasks: completed,
			PendingTasks:   total - completed,
			FactorialTotal: 0,
		}, nil
	}
}

