export enum Priority {
  LOW = 'low',
  MEDIUM = 'medium',
  HIGH = 'high'
}

export interface Task {
  id: number;
  title: string;
  description: string;
  completed: boolean;
  priority: Priority;
}

export interface TaskCreate {
  title: string;
  description?: string;
  completed?: boolean;
  priority?: Priority;
}

