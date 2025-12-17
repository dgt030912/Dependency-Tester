"""
AWS Configuration Helper
Loads AWS credentials from environment variables or .env file
"""
import os
from typing import Optional
from pathlib import Path

# Try to load .env file if it exists
try:
    from dotenv import load_dotenv
    env_path = Path(__file__).parent.parent / '.env'
    if env_path.exists():
        load_dotenv(env_path)
except ImportError:
    # python-dotenv not installed, skip .env loading
    pass

def get_aws_access_key() -> Optional[str]:
    """Get AWS Access Key ID from environment"""
    return os.getenv('AWS_ACCESS_KEY_ID')

def get_aws_secret_key() -> Optional[str]:
    """Get AWS Secret Access Key from environment"""
    return os.getenv('AWS_SECRET_ACCESS_KEY')

def get_aws_region() -> str:
    """Get AWS Region from environment, defaults to us-east-1"""
    return os.getenv('AWS_REGION', 'us-east-1')

def get_aws_config() -> dict:
    """Get complete AWS configuration dictionary"""
    access_key = get_aws_access_key()
    secret_key = get_aws_secret_key()
    region = get_aws_region()
    
    if not access_key or not secret_key:
        raise ValueError(
            "AWS credentials not found. Please set AWS_ACCESS_KEY_ID and "
            "AWS_SECRET_ACCESS_KEY environment variables or create a .env file."
        )
    
    return {
        'aws_access_key_id': access_key,
        'aws_secret_access_key': secret_key,
        'region_name': region
    }

