# Dependency-Tester 5
Test codebase for dependency graph generator

## Project Structure

- **backend/** - FastAPI Python backend
- **frontend/** - React TypeScript frontend
- **native/** - C and C++ utility code
- **utils/** - JavaScript utility functions
- **scripts/** - Build and utility scripts

## Native C/C++ Code

This project includes native C and C++ utilities in the `native/` directory. See [native/README.md](native/README.md) for build instructions and usage.

The native code includes:
- C utility functions (factorial, fibonacci, prime checking, etc.)
- C++ TaskProcessor class for task management
- Python bindings via `backend/native_bindings.py`

## Quick Start

### Backend
```bash
cd backend
pip install -r requirements.txt
gunicorn main:app -w 4 -k uvicorn.workers.UvicornWorker -b 0.0.0.0:8000
```

### Frontend
```bash
cd frontend
npm install
npm start
```

### Native Code
```bash
cd native
make all
make test
```