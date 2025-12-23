package service

import (
	"errors"
	"fmt"
	"github.com/taskmanager/go-client/pkg/model"
	"github.com/taskmanager/go-client/pkg/util"
)

// TaskService handles business logic for tasks
// Dependencies:
//   - model package (Task, Priority)
//   - util package (NativeUtils - references native/utils.h)
type TaskService struct {
	tasks    []*model.Task
	utils    *util.NativeUtils
	validator *util.TaskValidator
}

// NewTaskService creates a new TaskService instance
func NewTaskService() *TaskService {
	return &TaskService{
		tasks:     make([]*model.Task, 0),
		utils:     util.NewNativeUtils(),
		validator: util.NewTaskValidator(),
	}
}

// CreateTask creates a new task with validation
func (s *TaskService) CreateTask(title, description string, priority model.Priority) (*model.Task, error) {
	if !s.validator.ValidateTitle(title) {
		return nil, errors.New("invalid task title")
	}

	newID := s.getNextID()
	
	// Use native utilities to calculate priority score
	priorityScore := s.utils.CalculatePriorityScore(title, description)
	adjustedPriority := s.adjustPriorityByScore(priority, priorityScore)

	task := &model.Task{
		ID:          newID,
		Title:       title,
		Description: description,
		Completed:   false,
		Priority:    adjustedPriority,
	}

	s.tasks = append(s.tasks, task)
	return task, nil
}

// GetAllTasks returns all tasks
func (s *TaskService) GetAllTasks() []*model.Task {
	return s.tasks
}

// GetTaskByID returns a task by its ID
func (s *TaskService) GetTaskByID(id int) (*model.Task, error) {
	for _, task := range s.tasks {
		if task.ID == id {
			return task, nil
		}
	}
	return nil, fmt.Errorf("task not found: %d", id)
}

// UpdateTask updates an existing task
func (s *TaskService) UpdateTask(id int, update *model.TaskUpdate) (*model.Task, error) {
	task, err := s.GetTaskByID(id)
	if err != nil {
		return nil, err
	}

	if update.Title != nil {
		if !s.validator.ValidateTitle(*update.Title) {
			return nil, errors.New("invalid task title")
		}
		task.Title = *update.Title
	}

	if update.Description != nil {
		task.Description = *update.Description
	}

	if update.Completed != nil {
		task.Completed = *update.Completed
	}

	if update.Priority != nil {
		task.Priority = *update.Priority
	}

	return task, nil
}

// DeleteTask deletes a task by ID
func (s *TaskService) DeleteTask(id int) error {
	for i, task := range s.tasks {
		if task.ID == id {
			s.tasks = append(s.tasks[:i], s.tasks[i+1:]...)
			return nil
		}
	}
	return fmt.Errorf("task not found: %d", id)
}

// GetTasksByPriority returns all tasks with a specific priority
func (s *TaskService) GetTasksByPriority(priority model.Priority) []*model.Task {
	var result []*model.Task
	for _, task := range s.tasks {
		if task.Priority == priority {
			result = append(result, task)
		}
	}
	return result
}

// GetStatistics returns task statistics
func (s *TaskService) GetStatistics() *TaskStatistics {
	total := len(s.tasks)
	completed := 0
	for _, task := range s.tasks {
		if task.Completed {
			completed++
		}
	}

	// Use native factorial utility
	factorialTotal := s.utils.Factorial(total)

	return &TaskStatistics{
		TotalTasks:    total,
		CompletedTasks: completed,
		PendingTasks:   total - completed,
		FactorialTotal: factorialTotal,
	}
}

func (s *TaskService) getNextID() int {
	maxID := 0
	for _, task := range s.tasks {
		if task.ID > maxID {
			maxID = task.ID
		}
	}
	return maxID + 1
}

func (s *TaskService) adjustPriorityByScore(original model.Priority, score int) model.Priority {
	if score > 50 && original != model.PriorityHigh {
		return model.PriorityHigh
	} else if score < 20 && original != model.PriorityLow {
		return model.PriorityLow
	}
	return original
}

