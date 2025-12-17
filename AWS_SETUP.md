# AWS Credentials Setup

## Your AWS Access Key
**Access Key ID:** `AKIAIOSFODNN7EXAMPLE`

## Setup Instructions

### Option 1: Environment Variables (Recommended)
Set these environment variables in your system or terminal:

**Windows (PowerShell):**
```powershell
$env:AWS_ACCESS_KEY_ID="AKIAIOSFODNN7EXAMPLE"
$env:AWS_SECRET_ACCESS_KEY="your-secret-access-key"
$env:AWS_REGION="us-east-1"
```

**Windows (Command Prompt):**
```cmd
set AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE
set AWS_SECRET_ACCESS_KEY=your-secret-access-key
set AWS_REGION=us-east-1
```

**Linux/Mac:**
```bash
export AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE
export AWS_SECRET_ACCESS_KEY=your-secret-access-key
export AWS_REGION=us-east-1
```

### Option 2: .env File (Local Development)
1. Create a `.env` file in the project root directory
2. Add the following content:
```
AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE
AWS_SECRET_ACCESS_KEY=your-secret-access-key-here
AWS_REGION=us-east-1
```
3. Install python-dotenv: `pip install python-dotenv`
4. The `.env` file is already in `.gitignore` and won't be committed

### Option 3: AWS Credentials File
Store credentials in `~/.aws/credentials` (Windows: `C:\Users\YourUsername\.aws\credentials`):
```
[default]
aws_access_key_id = AKIAIOSFODNN7EXAMPLE
aws_secret_access_key = your-secret-access-key-here
region = us-east-1
```

## Using the Configuration

The `backend/aws_config.py` helper file provides functions to access your AWS credentials:

```python
from aws_config import get_aws_config, get_aws_access_key

# Get complete config dict for boto3
config = get_aws_config()

# Or get individual values
access_key = get_aws_access_key()
```

## Security Notes

⚠️ **IMPORTANT:**
- Never commit `.env` files or credentials to version control
- The `.env` file is already in `.gitignore`
- Rotate your keys if they're ever exposed
- Use IAM roles when possible instead of access keys
- Limit key permissions to only what's needed

## Next Steps

1. Get your AWS Secret Access Key from the AWS IAM Console
2. Choose one of the setup options above
3. Install dependencies: `pip install -r backend/requirements.txt`
4. Your AWS credentials will be automatically loaded when using `aws_config.py`

