import React, { useState, useEffect, useCallback } from 'react';
import './App.css';
import TaskList from './components/TaskList';
import TaskForm from './components/TaskForm';
import { Task, Priority } from './types';
import { fetchTasks, createTask, updateTask, deleteTask } from './services/api';

const App: React.FC = () => {
  const [tasks, setTasks] = useState<Task[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  const loadTasks = useCallback(async () => {
    try {
      setLoading(true);
      const data = await fetchTasks();
      setTasks(data);
      setError(null);
    } catch (err) {
      setError('Failed to load tasks');
      console.error(err);
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => {
    loadTasks();
  }, [loadTasks]);

  const handleCreateTask = useCallback(async (task: Omit<Task, 'id'>) => {
    try {
      const newTask = await createTask(task);
      setTasks(prevTasks => [...prevTasks, newTask]);
    } catch (err) {
      setError('Failed to create task');
      console.error(err);
    }
  }, []);

  const handleUpdateTask = useCallback(async (id: number, updates: Partial<Task>) => {
    try {
      const updatedTask = await updateTask(id, updates);
      setTasks(prevTasks => prevTasks.map(t => t.id === id ? updatedTask : t));
    } catch (err) {
      setError('Failed to update task');
      console.error(err);
    }
  }, []);

  const handleDeleteTask = useCallback(async (id: number) => {
    try {
      await deleteTask(id);
      setTasks(prevTasks => prevTasks.filter(t => t.id !== id));
    } catch (err) {
      setError('Failed to delete task');
      console.error(err);
    }
  }, []);

  return (
    <div className="App">
      <header className="App-header">
        <h1>Task Manager</h1>
        <p>Manage your tasks efficiently</p>
      </header>
      
      <main className="App-main">
        {error && <div className="error-message">{error}</div>}
        
        <TaskForm onSubmit={handleCreateTask} />
        
        {loading ? (
          <div className="loading">Loading tasks...</div>
        ) : (
          <TaskList
            tasks={tasks}
            onUpdate={handleUpdateTask}
            onDelete={handleDeleteTask}
          />
        )}
      </main>
    </div>
  );
};

export default App;
