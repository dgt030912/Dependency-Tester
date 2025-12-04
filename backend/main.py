from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from typing import List
from models import Task, TaskCreate, TaskUpdate
from database import get_db, init_db
import uvicorn

app = FastAPI(title="Task Manager API", version="1.0.0")

# CORS middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Initialize database on startup
@app.on_event("startup")
async def startup_event():
    init_db()

@app.get("/")
async def root():
    return {"message": "Task Manager API"}

@app.get("/api/tasks", response_model=List[Task])
async def get_tasks():
    db = get_db()
    return db

@app.get("/api/tasks/{task_id}", response_model=Task)
async def get_task(task_id: int):
    db = get_db()
    task = next((t for t in db if t.id == task_id), None)
    if not task:
        raise HTTPException(status_code=404, detail="Task not found")
    return task

@app.post("/api/tasks", response_model=Task)
async def create_task(task: TaskCreate):
    db = get_db()
    new_id = max([t.id for t in db], default=0) + 1
    new_task = Task(
        id=new_id,
        title=task.title,
        description=task.description,
        completed=task.completed,
        priority=task.priority
    )
    db.append(new_task)
    return new_task

@app.put("/api/tasks/{task_id}", response_model=Task)
async def update_task(task_id: int, task_update: TaskUpdate):
    db = get_db()
    task = next((t for t in db if t.id == task_id), None)
    if not task:
        raise HTTPException(status_code=404, detail="Task not found")
    
    if task_update.title is not None:
        task.title = task_update.title
    if task_update.description is not None:
        task.description = task_update.description
    if task_update.completed is not None:
        task.completed = task_update.completed
    if task_update.priority is not None:
        task.priority = task_update.priority
    
    return task

@app.delete("/api/tasks/{task_id}")
async def delete_task(task_id: int):
    db = get_db()
    task_index = next((i for i, t in enumerate(db) if t.id == task_id), None)
    if task_index is None:
        raise HTTPException(status_code=404, detail="Task not found")
    db.pop(task_index)
    return {"message": "Task deleted successfully"}

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)

#new line
#new line 2