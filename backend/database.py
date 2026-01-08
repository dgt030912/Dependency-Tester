from motor.motor_asyncio import AsyncIOMotorClient
from pymongo.errors import ConnectionFailure
from pymongo import ReturnDocument
from typing import Optional
import os
from dotenv import load_dotenv

load_dotenv()

# Config
MONGO_URL = os.getenv("MONGO_URL", "mongodb://localhost:27017")
DATABASE_NAME = os.getenv("MONGO_DATABASE", "taskmanager")
COLLECTION_NAME = "tasks"

# Global cache
_client: Optional[AsyncIOMotorClient] = None


async def get_collection():
    """Get tasks collection (cached)"""
    global _client
    if _client is None:
        _client = AsyncIOMotorClient(
            MONGO_URL,
            maxPoolSize=int(os.getenv("MONGO_MAX_POOL_SIZE", "100")),
            minPoolSize=int(os.getenv("MONGO_MIN_POOL_SIZE", "10")),
            retryWrites=True,
            retryReads=True,
        )
        try:
            await _client.admin.command('ping')
        except ConnectionFailure as e:
            raise ConnectionFailure(f"Failed to connect: {e}")
    return _client[DATABASE_NAME][COLLECTION_NAME]


async def init_db():
    """Initialize database with indexes and sample data"""
    coll = await get_collection()
    try:
        await coll.create_index("id", unique=True)
        await coll.create_index("completed")
        await coll.create_index("priority")
    except Exception:
        pass
    
    if await coll.count_documents({}) == 0:
        from models import Priority
        await coll.insert_one({
            "id": 1,
            "title": "Welcome Task",
            "description": "Get started with the Task Manager",
            "completed": False,
            "priority": Priority.HIGH.value
        })


async def close_db():
    """Close MongoDB connection"""
    global _client
    if _client:
        _client.close()
        _client = None


async def get_pool_stats():
    """Get connection pool statistics"""
    if not _client:
        return {"error": "Not initialized"}
    try:
        info = await _client.server_info()
        return {"server_version": info.get("version"), "status": "healthy"}
    except Exception as e:
        return {"error": str(e)}


async def get_all_tasks(limit: Optional[int] = None, skip: int = 0):
    """Get tasks with pagination"""
    coll = await get_collection()
    limit = limit or int(os.getenv("TASKS_DEFAULT_LIMIT", "1000"))
    cursor = coll.find({}, {"_id": 0}).skip(skip).limit(limit)
    return await cursor.to_list(length=limit)


async def get_task_by_id(task_id: int):
    """Get a task by ID"""
    return await (await get_collection()).find_one({"id": task_id}, {"_id": 0})


async def create_task(task_data: dict):
    """Create a new task"""
    coll = await get_collection()
    max_task = await coll.find_one(sort=[("id", -1)], projection={"id": 1, "_id": 0})
    task_data["id"] = (max_task["id"] + 1) if max_task else 1
    await coll.insert_one(task_data)
    return await coll.find_one({"id": task_data["id"]}, {"_id": 0})


async def update_task(task_id: int, update_data: dict):
    """Update a task"""
    update_data = {k: v for k, v in update_data.items() if v is not None}
    if not update_data:
        return await get_task_by_id(task_id)
    return await (await get_collection()).find_one_and_update(
        {"id": task_id},
        {"$set": update_data},
        return_document=ReturnDocument.AFTER,
        projection={"_id": 0}
    )


async def delete_task(task_id: int):
    """Delete a task"""
    result = await (await get_collection()).delete_one({"id": task_id})
    return result.deleted_count > 0
