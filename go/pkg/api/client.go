package api

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"time"

	"github.com/taskmanager/go-client/pkg/model"
)

// TaskAPIClient is an HTTP client for the Python FastAPI backend
// References: backend/main.py (Python FastAPI endpoints)
//            backend/models.py (Python Task model structure)
const (
	BaseURL    = "http://localhost:8000/api"
	Timeout    = 10 * time.Second
)

// TaskAPIClient handles HTTP communication with Python backend
type TaskAPIClient struct {
	baseURL    string
	httpClient *http.Client
}

// NewTaskAPIClient creates a new TaskAPIClient
func NewTaskAPIClient() *TaskAPIClient {
	return &TaskAPIClient{
		baseURL: BaseURL,
		httpClient: &http.Client{
			Timeout: Timeout,
		},
	}
}

// GetAllTasks fetches all tasks from Python backend
// References: GET /api/tasks in backend/main.py
func (c *TaskAPIClient) GetAllTasks() ([]*model.Task, error) {
	resp, err := c.httpClient.Get(c.baseURL + "/tasks")
	if err != nil {
		return nil, fmt.Errorf("failed to fetch tasks: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, fmt.Errorf("failed to read response: %w", err)
	}

	var tasks []*model.Task
	if err := json.Unmarshal(body, &tasks); err != nil {
		return nil, fmt.Errorf("failed to parse response: %w", err)
	}

	return tasks, nil
}

// GetTaskByID fetches a task by ID from Python backend
// References: GET /api/tasks/{task_id} in backend/main.py
func (c *TaskAPIClient) GetTaskByID(id int) (*model.Task, error) {
	url := fmt.Sprintf("%s/tasks/%d", c.baseURL, id)
	resp, err := c.httpClient.Get(url)
	if err != nil {
		return nil, fmt.Errorf("failed to fetch task: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, fmt.Errorf("failed to read response: %w", err)
	}

	var task model.Task
	if err := json.Unmarshal(body, &task); err != nil {
		return nil, fmt.Errorf("failed to parse response: %w", err)
	}

	return &task, nil
}

// CreateTask creates a task via Python backend
// References: POST /api/tasks in backend/main.py
func (c *TaskAPIClient) CreateTask(create *model.TaskCreate) (*model.Task, error) {
	jsonData, err := json.Marshal(create)
	if err != nil {
		return nil, fmt.Errorf("failed to marshal task: %w", err)
	}

	resp, err := c.httpClient.Post(
		c.baseURL+"/tasks",
		"application/json",
		bytes.NewBuffer(jsonData),
	)
	if err != nil {
		return nil, fmt.Errorf("failed to create task: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK && resp.StatusCode != http.StatusCreated {
		return nil, fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, fmt.Errorf("failed to read response: %w", err)
	}

	var task model.Task
	if err := json.Unmarshal(body, &task); err != nil {
		return nil, fmt.Errorf("failed to parse response: %w", err)
	}

	return &task, nil
}

// UpdateTask updates a task via Python backend
// References: PUT /api/tasks/{task_id} in backend/main.py
func (c *TaskAPIClient) UpdateTask(id int, update *model.TaskUpdate) (*model.Task, error) {
	jsonData, err := json.Marshal(update)
	if err != nil {
		return nil, fmt.Errorf("failed to marshal update: %w", err)
	}

	url := fmt.Sprintf("%s/tasks/%d", c.baseURL, id)
	req, err := http.NewRequest(http.MethodPut, url, bytes.NewBuffer(jsonData))
	if err != nil {
		return nil, fmt.Errorf("failed to create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")

	resp, err := c.httpClient.Do(req)
	if err != nil {
		return nil, fmt.Errorf("failed to update task: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, fmt.Errorf("failed to read response: %w", err)
	}

	var task model.Task
	if err := json.Unmarshal(body, &task); err != nil {
		return nil, fmt.Errorf("failed to parse response: %w", err)
	}

	return &task, nil
}

// DeleteTask deletes a task via Python backend
// References: DELETE /api/tasks/{task_id} in backend/main.py
func (c *TaskAPIClient) DeleteTask(id int) error {
	url := fmt.Sprintf("%s/tasks/%d", c.baseURL, id)
	req, err := http.NewRequest(http.MethodDelete, url, nil)
	if err != nil {
		return fmt.Errorf("failed to create request: %w", err)
	}

	resp, err := c.httpClient.Do(req)
	if err != nil {
		return fmt.Errorf("failed to delete task: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	return nil
}

