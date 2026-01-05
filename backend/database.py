from motor.motor_asyncio import AsyncIOMotorClient, AsyncIOMotorDatabase, AsyncIOMotorCollection
from pymongo.errors import ConnectionFailure
from typing import Optional
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# MongoDB connection settings
MONGO_URL = os.getenv("MONGO_URL", "mongodb://localhost:27017")
DATABASE_NAME = os.getenv("MONGO_DATABASE", "taskmanager")
COLLECTION_NAME = "tasks"

# Enhanced connection pool settings
MAX_POOL_SIZE = int(os.getenv("MONGO_MAX_POOL_SIZE", "100"))
MIN_POOL_SIZE = int(os.getenv("MONGO_MIN_POOL_SIZE", "10"))
MAX_IDLE_TIME_MS = int(os.getenv("MONGO_MAX_IDLE_TIME_MS", "60000"))
CONNECT_TIMEOUT_MS = int(os.getenv("MONGO_CONNECT_TIMEOUT_MS", "20000"))
SOCKET_TIMEOUT_MS = int(os.getenv("MONGO_SOCKET_TIMEOUT_MS", "20000"))
SERVER_SELECTION_TIMEOUT_MS = int(os.getenv("MONGO_SERVER_SELECTION_TIMEOUT_MS", "5000"))
WAIT_QUEUE_TIMEOUT_MS = int(os.getenv("MONGO_WAIT_QUEUE_TIMEOUT_MS", "10000"))

# Global MongoDB client and database (cached - single instance)
_client: Optional[AsyncIOMotorClient] = None
_database: Optional[AsyncIOMotorDatabase] = None
_collection: Optional[AsyncIOMotorCollection] = None


async def get_client() -> AsyncIOMotorClient:
    """Get or create MongoDB client with enhanced connection pooling"""
    global _client
    if _client is None:
        # Enhanced connection pool configuration
        _client = AsyncIOMotorClient(
            MONGO_URL,
            # Connection pool settings
            maxPoolSize=MAX_POOL_SIZE,  # Maximum number of connections in the pool
            minPoolSize=MIN_POOL_SIZE,  # Minimum number of connections to maintain
            maxIdleTimeMS=MAX_IDLE_TIME_MS,  # Close connections idle for this long
            # Connection timeout settings
            connectTimeoutMS=CONNECT_TIMEOUT_MS,  # Timeout for initial connection
            socketTimeoutMS=SOCKET_TIMEOUT_MS,  # Timeout for socket operations
            serverSelectionTimeoutMS=SERVER_SELECTION_TIMEOUT_MS,  # Timeout for server selection
            waitQueueTimeoutMS=WAIT_QUEUE_TIMEOUT_MS,  # Timeout waiting for connection from pool
            # Additional pool optimizations
            retryWrites=True,  # Retry write operations on network errors
            retryReads=True,  # Retry read operations on network errors
            # Heartbeat settings for connection health
            heartbeatFrequencyMS=10000,  # Check server health every 10 seconds
        )
        try:
            # Verify connection and pool initialization
            await _client.admin.command('ping')
        except ConnectionFailure as e:
            raise ConnectionFailure(f"Failed to connect to MongoDB: {e}")
    return _client


async def get_database() -> AsyncIOMotorDatabase:
    """Get database instance (cached)"""
    global _database
    if _database is None:
        client = await get_client()
        _database = client[DATABASE_NAME]
    return _database


async def get_collection() -> AsyncIOMotorCollection:
    """Get tasks collection (cached)"""
    global _collection
    if _collection is None:
        db = await get_database()
        _collection = db[COLLECTION_NAME]
    return _collection


async def get_pool_stats():
    """Get connection pool statistics"""
    client = await get_client()
    try:
        # Get server status which includes connection pool info
        server_info = await client.server_info()
        return {
            "server_version": server_info.get("version"),
            "max_pool_size": MAX_POOL_SIZE,
            "min_pool_size": MIN_POOL_SIZE,
            "max_idle_time_ms": MAX_IDLE_TIME_MS,
        }
    except Exception as e:
        return {"error": str(e)}


async def init_db():
    """Initialize database with indexes and sample data"""
    collection = await get_collection()
    
    # Create indexes (idempotent - safe to call multiple times)
    try:
        await collection.create_index("id", unique=True)
        await collection.create_index("completed")
        await collection.create_index("priority")
    except Exception:
        # Indexes might already exist, ignore
        pass
    
    # Check if collection is empty, if so add sample data
    count = await collection.count_documents({})
    if count == 0:
        from models import Priority
        sample_task = {
            "id": 1,
            "title": "Welcome Task",
            "description": "Get started with the Task Manager",
            "completed": False,
            "priority": Priority.HIGH.value
        }
        await collection.insert_one(sample_task)


async def close_db():
    """Close MongoDB connection and clear references"""
    global _client, _database, _collection
    if _client:
        _client.close()
        _client = None
        _database = None
        _collection = None


# Database operation functions
async def get_all_tasks(limit: Optional[int] = None, skip: int = 0):
    """
    Get tasks from MongoDB with pagination support
    
    Args:
        limit: Maximum number of tasks to return (default: 1000)
        skip: Number of tasks to skip (for pagination)
    """
    collection = await get_collection()
    # Use projection to exclude _id from the query
    query_limit = limit if limit is not None else int(os.getenv("TASKS_DEFAULT_LIMIT", "1000"))
    
    cursor = collection.find({}, {"_id": 0}).skip(skip).limit(query_limit)
    tasks = await cursor.to_list(length=query_limit)
    return tasks


async def get_task_by_id(task_id: int):
    """Get a task by ID (optimized with projection)"""
    collection = await get_collection()
    # Use projection to exclude _id from the query
    task = await collection.find_one({"id": task_id}, {"_id": 0})
    return task


async def create_task(task_data: dict):
    """Create a new task (uses projection)"""
    collection = await get_collection()
    
    # Get the next ID (use projection to only fetch id field)
    max_task = await collection.find_one(
        sort=[("id", -1)],
        projection={"id": 1, "_id": 0}
    )
    new_id = (max_task["id"] + 1) if max_task else 1
    
    task_data["id"] = new_id
    result = await collection.insert_one(task_data)
    
    # Return the created task with projection to exclude _id
    created_task = await collection.find_one(
        {"_id": result.inserted_id},
        {"_id": 0}
    )
    return created_task


async def update_task(task_id: int, update_data: dict):
    """Update a task (single query with returnDocument)"""
    collection = await get_collection()
    
    # Remove None values from update_data
    update_data = {k: v for k, v in update_data.items() if v is not None}
    
    if not update_data:
        # No updates to apply, just return the current task
        return await get_task_by_id(task_id)
    
    # Use find_one_and_update to get updated document in single query
    from pymongo import ReturnDocument
    updated_task = await collection.find_one_and_update(
        {"id": task_id},
        {"$set": update_data},
        return_document=ReturnDocument.AFTER,
        projection={"_id": 0}
    )
    
    return updated_task


async def delete_task(task_id: int):
    """Delete a task"""
    collection = await get_collection()
    result = await collection.delete_one({"id": task_id})
    return result.deleted_count > 0
