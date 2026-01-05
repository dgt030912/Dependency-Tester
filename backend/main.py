from fastapi import FastAPI, HTTPException, status, Path, Query
from fastapi.middleware.cors import CORSMiddleware
from typing import List, Optional
from contextlib import asynccontextmanager
import logging
from models import Task, TaskCreate, TaskUpdate
from database import init_db, close_db, get_all_tasks, get_task_by_id, create_task, update_task, delete_task, get_pool_stats

# Configure logging (memory-efficient - INFO level, no DEBUG)
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


# Lifespan context manager (replaces deprecated on_event)
@asynccontextmanager
async def lifespan(app: FastAPI):
    # Startup
    logger.info("Initializing database...")
    await init_db()
    logger.info("Database initialized successfully")
    yield
    # Shutdown - ensure cleanup
    logger.info("Closing database connections...")
    await close_db()
    logger.info("Database connections closed")


app = FastAPI(
    title="Task Manager API",
    version="1.0.0",
    description="A FastAPI-based task management system with MongoDB",
    lifespan=lifespan
)

# CORS middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/", tags=["Health"])
async def root():
    """Health check endpoint"""
    return {"message": "Task Manager API", "status": "running"}


@app.get("/api/health/pool", tags=["Health"])
async def get_pool_health():
    """Get connection pool statistics and health information"""
    stats = await get_pool_stats()
    return {"pool_stats": stats, "status": "healthy" if "error" not in stats else "degraded"}


@app.get(
    "/api/tasks",
    response_model=List[Task],
    tags=["Tasks"],
    summary="Get all tasks",
    description="Returns a list of tasks with pagination support to minimize memory usage"
)
async def get_tasks(
    limit: Optional[int] = Query(None, ge=1, le=500, description="Maximum number of tasks to return (default: 100, max: 500)"),
    skip: int = Query(0, ge=0, description="Number of tasks to skip (for pagination)")
):
    """
    Get tasks with pagination support
    
    Memory-optimized: Uses pagination to limit the number of tasks loaded into memory.
    Default limit is 100 tasks to minimize memory usage.
    """
    try:
        # Use pagination to limit memory usage
        tasks_data = await get_all_tasks(limit=limit, skip=skip)
        # Direct list comprehension - avoid intermediate variables
        tasks = [Task(**task) for task in tasks_data]
        logger.info(f"Retrieved {len(tasks)} tasks (limit={limit}, skip={skip})")
        return tasks
    except Exception as e:
        logger.error(f"Error fetching tasks: {e}", exc_info=True)
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail="Failed to fetch tasks"
        )


@app.get(
    "/api/tasks/{task_id}",
    response_model=Task,
    tags=["Tasks"],
    summary="Get task by ID",
    description="Returns a task by its unique identifier"
)
async def get_task(task_id: int = Path(..., gt=0, description="The unique identifier of the task")):
    """Get a task by ID (memory-efficient - single document)"""
    task_data = await get_task_by_id(task_id)
    if not task_data:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail=f"Task with ID {task_id} not found"
        )
    return Task(**task_data)


@app.post(
    "/api/tasks",
    response_model=Task,
    status_code=status.HTTP_201_CREATED,
    tags=["Tasks"],
    summary="Create a new task",
    description="Creates a new task in the system"
)
async def create_task_endpoint(task: TaskCreate):
    """Create a new task"""
    try:
        task_data = task.model_dump()
        created_task = await create_task(task_data)
        if not created_task:
            raise HTTPException(
                status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                detail="Failed to create task"
            )
        logger.info(f"Created task with ID {created_task['id']}")
        return Task(**created_task)
    except ValueError as e:
        raise HTTPException(
            status_code=status.HTTP_422_UNPROCESSABLE_ENTITY,
            detail=str(e)
        )
    except Exception as e:
        logger.error(f"Error creating task: {e}", exc_info=True)
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail="Failed to create task"
        )


@app.put(
    "/api/tasks/{task_id}",
    response_model=Task,
    tags=["Tasks"],
    summary="Update an existing task",
    description="Updates an existing task. All fields are optional - only provided fields will be updated."
)
async def update_task_endpoint(
    task_id: int = Path(..., gt=0, description="The unique identifier of the task to update"),
    task_update: TaskUpdate = ...
):
    """Update an existing task (memory-efficient - single query)"""
    try:
        update_data = task_update.model_dump(exclude_unset=True)
        updated_task = await update_task(task_id, update_data)
        if not updated_task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"Task with ID {task_id} not found"
            )
        logger.info(f"Updated task with ID {task_id}")
        return Task(**updated_task)
    except HTTPException:
        raise
    except ValueError as e:
        raise HTTPException(
            status_code=status.HTTP_422_UNPROCESSABLE_ENTITY,
            detail=str(e)
        )
    except Exception as e:
        logger.error(f"Error updating task {task_id}: {e}", exc_info=True)
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail="Failed to update task"
        )


@app.delete(
    "/api/tasks/{task_id}",
    status_code=status.HTTP_200_OK,
    tags=["Tasks"],
    summary="Delete a task",
    description="Deletes a task by its unique identifier"
)
async def delete_task_endpoint(task_id: int = Path(..., gt=0, description="The unique identifier of the task to delete")):
    """Delete a task (memory-efficient - no data returned)"""
    deleted = await delete_task(task_id)
    if not deleted:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail=f"Task with ID {task_id} not found"
        )
    logger.info(f"Deleted task with ID {task_id}")
    return {"message": "Task deleted successfully", "task_id": task_id}


# Run with: gunicorn main:app -w 4 -k uvicorn.workers.UvicornWorker -b 0.0.0.0:8000
# Or for development: gunicorn main:app -w 1 -k uvicorn.workers.UvicornWorker -b 0.0.0.0:8000 --reload
