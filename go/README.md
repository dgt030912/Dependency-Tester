# Go Task Manager Client

Go implementation with dependencies on multiple parts of the codebase.

## Dependencies

### Internal Go Dependencies
- **model** package (Task, Priority) ← used by all service/controller/api packages
- **service** package (TaskService) ← uses model, util packages
- **controller** package (TaskController) ← uses service, api, model packages
- **api** package (TaskAPIClient) ← uses model package
- **util** package (NativeUtils, TaskValidator) ← uses native C/C++ code

### External Dependencies
- **Python Backend** (`backend/main.py`) - TaskAPIClient communicates with FastAPI endpoints
- **Python Models** (`backend/models.py`) - TaskAPIClient matches Python Task structure
- **C Native Code** (`native/utils.h`, `native/utils.c`) - NativeUtils provides CGO bindings
- **C++ Native Code** (`native/task_processor.cpp`) - Referenced in NativeUtils
- **TypeScript Frontend** (`frontend/src/types.ts`) - Task model matches TypeScript interface
- **Java Models** (`java/src/main/java/com/taskmanager/model/`) - Task model matches Java structure

## Project Structure

```
go/
├── go.mod                                    # Go module definition
├── main.go                                   # Entry point
├── README.md                                 # This file
└── pkg/
    ├── model/
    │   ├── task.go                          # Task model (references Python/Java/TS models)
    │   └── priority.go                      # Priority enum (references Python/Java/TS enums)
    ├── service/
    │   ├── task_service.go                  # Business logic (uses model, util)
    │   └── statistics.go                    # Statistics struct
    ├── util/
    │   ├── native_utils.go                  # CGO wrapper for C/C++ (references native/)
    │   └── validator.go                     # Validation utilities
    ├── api/
    │   └── client.go                        # HTTP client for Python API (references backend/)
    └── controller/
        └── task_controller.go               # Controller (uses service, api)
```

## Building

### Prerequisites
- Go 1.21 or higher
- C compiler (for CGO support)

### Build Commands

```bash
cd go
go mod download    # Download dependencies
go build           # Build the application
go run main.go     # Run the application
```

### Run

```bash
go run main.go
```

Or build and run:

```bash
go build
./go-client  # or go-client.exe on Windows
```

## Dependency Graph

```
main.go
  └── controller.TaskController
       ├── service.TaskService
       │    ├── model.Task
       │    ├── model.Priority
       │    ├── util.NativeUtils → native/utils.h, native/utils.c (via CGO)
       │    └── util.TaskValidator
       └── api.TaskAPIClient
            ├── model.Task
            └── HTTP calls → backend/main.py
```

## Integration Points

1. **Python Backend**: `api.TaskAPIClient` makes HTTP requests to `http://localhost:8000/api/tasks`
2. **C/C++ Native Code**: `util.NativeUtils` uses CGO to call functions from `native/utils.h`
3. **TypeScript Frontend**: Task model structure matches `frontend/src/types.ts`
4. **Java Code**: Task model structure matches `java/src/main/java/com/taskmanager/model/`

## CGO Integration

The `util.NativeUtils` package uses CGO to integrate with native C code:

```go
/*
#cgo CFLAGS: -I../../native
#cgo LDFLAGS: -L../../native/build -lutils
#include "../../native/utils.h"
*/
import "C"
```

This allows Go code to directly call C functions from `native/utils.c`.

## Notes

- The CGO integration requires the native library to be built first: `cd ../native && make`
- The API client requires the Python backend to be running on port 8000
- All models are designed to match the Python backend, TypeScript frontend, and Java client structures
- Go modules are used for dependency management (no external dependencies required beyond standard library)

## Cross-Language Compatibility

The Go implementation shares the same data structures as:
- **Python**: `backend/models.py`
- **TypeScript**: `frontend/src/types.ts`
- **Java**: `java/src/main/java/com/taskmanager/model/`

This ensures seamless integration across all parts of the codebase.

