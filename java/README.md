# Java Task Manager Client

Java implementation with dependencies on multiple parts of the codebase.

## Dependencies

### Internal Java Dependencies
- **Task** (model) ← used by all service/controller classes
- **Priority** (model) ← used by Task and all services
- **TaskService** ← uses Task, Priority, NativeUtils, TaskValidator
- **TaskController** ← uses TaskService, TaskAPIClient, Task, Priority
- **TaskAPIClient** ← uses Task, Priority
- **NativeUtils** ← uses native C/C++ code
- **TaskValidator** ← used by TaskService

### External Dependencies
- **Python Backend** (`backend/main.py`) - TaskAPIClient communicates with FastAPI endpoints
- **Python Models** (`backend/models.py`) - TaskAPIClient matches Python Task structure
- **C Native Code** (`native/utils.h`, `native/utils.c`) - NativeUtils provides JNI bindings
- **C++ Native Code** (`native/task_processor.cpp`) - Referenced in NativeUtils
- **TypeScript Frontend** (`frontend/src/types.ts`) - Task model matches TypeScript interface

## Project Structure

```
java/
├── src/main/java/com/taskmanager/
│   ├── model/
│   │   ├── Task.java          # Task model (references Python/TS models)
│   │   └── Priority.java     # Priority enum (references Python/TS enums)
│   ├── service/
│   │   ├── TaskService.java   # Business logic (uses Task, NativeUtils)
│   │   └── TaskStatistics.java # Statistics class
│   ├── util/
│   │   ├── NativeUtils.java   # JNI wrapper for C/C++ (references native/)
│   │   └── TaskValidator.java # Validation utilities
│   ├── api/
│   │   └── TaskAPIClient.java # HTTP client for Python API (references backend/)
│   ├── controller/
│   │   └── TaskController.java # Controller (uses TaskService, TaskAPIClient)
│   └── Main.java              # Entry point (uses TaskController)
├── pom.xml                    # Maven configuration
└── README.md                  # This file
```

## Building

### Prerequisites
- Java 17 or higher
- Maven 3.6+

### Build Commands

```bash
cd java
mvn clean compile
mvn package
```

### Run

```bash
mvn exec:java
```

Or:

```bash
java -cp target/classes:target/dependency/* com.taskmanager.Main
```

## Dependency Graph

```
Main
  └── TaskController
       ├── TaskService
       │    ├── Task (model)
       │    ├── Priority (model)
       │    ├── NativeUtils → native/utils.h, native/utils.c
       │    └── TaskValidator
       └── TaskAPIClient
            ├── Task (model)
            ├── Priority (model)
            └── HTTP calls → backend/main.py
```

## Integration Points

1. **Python Backend**: `TaskAPIClient` makes HTTP requests to `http://localhost:8000/api/tasks`
2. **C/C++ Native Code**: `NativeUtils` uses JNI to call functions from `native/utils.h`
3. **TypeScript Frontend**: Task model structure matches `frontend/src/types.ts`

## Notes

- The native library loading in `NativeUtils` requires JNI bindings to be compiled
- The API client requires the Python backend to be running on port 8000
- All models are designed to match the Python backend and TypeScript frontend structures

