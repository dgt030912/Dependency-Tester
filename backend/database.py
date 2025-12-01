from models import Task, Priority

# In-memory database (replace with real DB in production)
_db: list[Task] = [
    Task(id=1, title="Sample Task", description="This is a sample task", completed=False, priority=Priority.MEDIUM)
]

def get_db() -> list[Task]:
    return _db

def init_db():
    """Initialize database with sample data"""
    global _db
    if not _db:
        _db = [
            Task(id=1, title="Welcome Task", description="Get started with the Task Manager", completed=False, priority=Priority.HIGH)
        ]

#new line
#nl2
#nl3