import React, { useState, useCallback, memo } from 'react';
import { TaskCreate, Priority } from '../types';
import './TaskForm.css';

interface TaskFormProps {
  onSubmit: (task: TaskCreate) => void;
}

const TaskForm: React.FC<TaskFormProps> = memo(({ onSubmit }) => {
  const [title, setTitle] = useState('');
  const [description, setDescription] = useState('');
  const [priority, setPriority] = useState<Priority>(Priority.MEDIUM);

  const handleSubmit = useCallback((e: React.FormEvent) => {
    e.preventDefault();
    const trimmedTitle = title.trim();
    if (trimmedTitle) {
      onSubmit({
        title: trimmedTitle,
        description: description.trim(),
        priority,
        completed: false,
      });
      setTitle('');
      setDescription('');
      setPriority(Priority.MEDIUM);
    }
  }, [title, description, priority, onSubmit]);

  const handleTitleChange = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
    setTitle(e.target.value);
  }, []);

  const handleDescriptionChange = useCallback((e: React.ChangeEvent<HTMLTextAreaElement>) => {
    setDescription(e.target.value);
  }, []);

  const handlePriorityChange = useCallback((e: React.ChangeEvent<HTMLSelectElement>) => {
    setPriority(e.target.value as Priority);
  }, []);

  return (
    <form className="task-form" onSubmit={handleSubmit}>
      <h2>Create New Task</h2>
      <div className="form-group">
        <label htmlFor="title">Title *</label>
        <input
          type="text"
          id="title"
          value={title}
          onChange={handleTitleChange}
          required
          placeholder="Enter task title"
        />
      </div>
      <div className="form-group">
        <label htmlFor="description">Description</label>
        <textarea
          id="description"
          value={description}
          onChange={handleDescriptionChange}
          placeholder="Enter task description (optional)"
          rows={3}
        />
      </div>
      <div className="form-group">
        <label htmlFor="priority">Priority</label>
        <select
          id="priority"
          value={priority}
          onChange={handlePriorityChange}
        >
          <option value={Priority.LOW}>Low</option>
          <option value={Priority.MEDIUM}>Medium</option>
          <option value={Priority.HIGH}>High</option>
        </select>
      </div>
      <button type="submit" className="btn-submit">Add Task</button>
    </form>
  );
});

TaskForm.displayName = 'TaskForm';

export default TaskForm;
