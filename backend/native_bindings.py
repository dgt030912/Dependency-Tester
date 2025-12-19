"""
Python bindings for native C/C++ utilities
Uses ctypes for C functions
"""
import ctypes
import os
from pathlib import Path
from typing import Optional

# Try to load the shared library
_lib_path = Path(__file__).parent.parent / 'native' / 'build' / 'libutils.so'
_lib = None

if _lib_path.exists():
    try:
        _lib = ctypes.CDLL(str(_lib_path))
        
        # Define function signatures
        _lib.factorial.argtypes = [ctypes.c_int]
        _lib.factorial.restype = ctypes.c_longlong
        
        _lib.fibonacci.argtypes = [ctypes.c_int]
        _lib.fibonacci.restype = ctypes.c_longlong
        
        _lib.is_prime.argtypes = [ctypes.c_int]
        _lib.is_prime.restype = ctypes.c_int
        
        _lib.reverse_string.argtypes = [ctypes.c_char_p]
        _lib.reverse_string.restype = ctypes.c_char_p
        
        _lib.array_sum.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
        _lib.array_sum.restype = ctypes.c_longlong
    except OSError:
        _lib = None


def factorial(n: int) -> Optional[int]:
    """Calculate factorial using native C function"""
    if _lib is None:
        return None
    try:
        return _lib.factorial(n)
    except:
        return None


def fibonacci(n: int) -> Optional[int]:
    """Calculate Fibonacci number using native C function"""
    if _lib is None:
        return None
    try:
        return _lib.fibonacci(n)
    except:
        return None


def is_prime(n: int) -> Optional[bool]:
    """Check if number is prime using native C function"""
    if _lib is None:
        return None
    try:
        result = _lib.is_prime(n)
        return bool(result)
    except:
        return None


def reverse_string(s: str) -> Optional[str]:
    """Reverse a string using native C function"""
    if _lib is None:
        return None
    try:
        # Create a mutable byte array
        b = s.encode('utf-8')
        result = _lib.reverse_string(ctypes.create_string_buffer(b))
        return result.decode('utf-8')
    except:
        return None


def array_sum(arr: list) -> Optional[int]:
    """Calculate sum of array using native C function"""
    if _lib is None:
        return None
    try:
        # Convert Python list to C array
        c_arr = (ctypes.c_int * len(arr))(*arr)
        return _lib.array_sum(c_arr, len(arr))
    except:
        return None


def is_available() -> bool:
    """Check if native library is available"""
    return _lib is not None

