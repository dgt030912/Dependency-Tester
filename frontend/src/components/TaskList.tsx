import React, { memo } from 'react';
import TaskItem from './TaskItem';
import { Task } from '../types';
import './TaskList.css';

interface TaskListProps {
  tasks: Task[];
  onUpdate: (id: number, updates: Partial<Task>) => void;
  onDelete: (id: number) => void;
}

const TaskList: React.FC<TaskListProps> = memo(({ tasks, onUpdate, onDelete }) => {
  if (tasks.length === 0) {
    return <div className="empty-state">No tasks yet. Create one to get started!</div>;
  }

  return (
    <div className="task-list">
      <h2>Your Tasks ({tasks.length})</h2>
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
});

TaskList.displayName = 'TaskList';

export default TaskList;
