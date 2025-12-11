import React from 'react';
import TaskItem from './TaskItem';
import { Task } from '../types';
import './TaskList.css';

interface TaskListProps {
  tasks: Task[];
  onUpdate: (id: number, updates: Partial<Task>) => void;
  onDelete: (id: number) => void;
}

const TaskList: React.FC<TaskListProps> = ({ tasks, onUpdate, onDelete }) => {
  if (tasks.length === 0) {
    return (
      <div className="empty-state">
        <p>No tasks yet.</p>
        <strong>Create one to get started!</strong>
      </div>
    );
  }

  return (
    <div className="task-list">
      <h2>
        <span>Your Tasks</span>
        <span style={{ color: 'var(--text-secondary)', fontWeight: 400, fontSize: '1rem' }}>
          ({tasks.length})
        </span>
      </h2>
      {tasks.map(task => (
        <TaskItem
          key={task.id}
          task={task}
          onUpdate={onUpdate}
          onDelete={onDelete}
        />
      ))}
    </div>
  );
};

export default TaskList;

