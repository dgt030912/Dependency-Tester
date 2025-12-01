#!/usr/bin/env node

/**
 * Build script for the Task Manager application
 * This JavaScript file handles the build process
 */

const fs = require('fs');
const path = require('path');

console.log('🚀 Starting build process...');

// Check if directories exist
const directories = [
  'backend',
  'frontend',
  'frontend/src',
  'frontend/public'
];

directories.forEach(dir => {
  if (!fs.existsSync(dir)) {
    console.error(`❌ Directory ${dir} does not exist!`);
    process.exit(1);
  }
});

// Check for required files
const requiredFiles = [
  'backend/main.py',
  'backend/requirements.txt',
  'frontend/package.json',
  'frontend/tsconfig.json'
];

requiredFiles.forEach(file => {
  if (!fs.existsSync(file)) {
    console.error(`❌ Required file ${file} does not exist!`);
    process.exit(1);
  }
});

console.log('✅ All required files and directories found');
console.log('📦 Build validation complete!');
console.log('\nTo start the application:');
console.log('  1. Backend: cd backend && pip install -r requirements.txt && python main.py');
console.log('  2. Frontend: cd frontend && npm install && npm start');

