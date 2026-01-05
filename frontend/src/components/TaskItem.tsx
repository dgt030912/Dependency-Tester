import React, { useState, useCallback, useMemo, memo } from 'react';
import { Task, Priority } from '../types';
import './TaskItem.css';

interface TaskItemProps {
  task: Task;
  onUpdate: (id: number, updates: Partial<Task>) => void;
  onDelete: (id: number) => void;
}

const TaskItem: React.FC<TaskItemProps> = memo(({ task, onUpdate, onDelete }) => {
  const [isEditing, setIsEditing] = useState(false);
  const [editTitle, setEditTitle] = useState(task.title);
  const [editDescription, setEditDescription] = useState(task.description);

  // Memoize priority class computation
  const priorityClass = useMemo(() => `priority-${task.priority}`, [task.priority]);
  
  // Memoize combined className
  const itemClassName = useMemo(
    () => `task-item ${task.completed ? 'completed' : ''} ${priorityClass}`,
    [task.completed, priorityClass]
  );

  const handleToggleComplete = useCallback(() => {
    onUpdate(task.id, { completed: !task.completed });
  }, [task.id, task.completed, onUpdate]);

  const handleSave = useCallback(() => {
    onUpdate(task.id, {
      title: editTitle,
      description: editDescription,
    });
    setIsEditing(false);
  }, [task.id, editTitle, editDescription, onUpdate]);

  const handleCancel = useCallback(() => {
    setEditTitle(task.title);
    setEditDescription(task.description);
    setIsEditing(false);
  }, [task.title, task.description]);

  const handleEditClick = useCallback(() => {
    setIsEditing(true);
  }, []);

  const handleDeleteClick = useCallback(() => {
    onDelete(task.id);
  }, [task.id, onDelete]);

  const handleTitleChange = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
    setEditTitle(e.target.value);
  }, []);

  const handleDescriptionChange = useCallback((e: React.ChangeEvent<HTMLTextAreaElement>) => {
    setEditDescription(e.target.value);
  }, []);

  // Update local state when task prop changes (e.g., after external update)
  React.useEffect(() => {
    if (!isEditing) {
      setEditTitle(task.title);
      setEditDescription(task.description);
    }
  }, [task.title, task.description, isEditing]);

  return (
    <div className={itemClassName}>
      {isEditing ? (
        <div className="task-edit">
          <input
            type="text"
            value={editTitle}
            onChange={handleTitleChange}
            className="edit-input"
          />
          <textarea
            value={editDescription}
            onChange={handleDescriptionChange}
            className="edit-textarea"
          />
          <div className="edit-actions">
            <button onClick={handleSave} className="btn-save">Save</button>
            <button onClick={handleCancel} className="btn-cancel">Cancel</button>
          </div>
        </div>
      ) : (
        <>
          <div className="task-content">
            <input
              type="checkbox"
              checked={task.completed}
              onChange={handleToggleComplete}
              className="task-checkbox"
            />
            <div className="task-info">
              <h3 className="task-title">{task.title}</h3>
              {task.description && (
                <p className="task-description">{task.description}</p>
              )}
              <span className="task-priority">{task.priority}</span>
            </div>
          </div>
          <div className="task-actions">
            <button onClick={handleEditClick} className="btn-edit">Edit</button>
            <button onClick={handleDeleteClick} className="btn-delete">Delete</button>
          </div>
        </>
      )}
    </div>
  );
});

TaskItem.displayName = 'TaskItem';

export default TaskItem;
