package com.taskmanager.api;

import com.taskmanager.model.Task;
import com.taskmanager.model.Priority;
import com.google.gson.Gson;
import com.google.gson.JsonObject;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

/**
 * TaskAPIClient - HTTP client for Python FastAPI backend
 * References: backend/main.py (Python FastAPI endpoints)
 *            backend/models.py (Python Task model structure)
 * 
 * This client communicates with the Python backend API
 */
public class TaskAPIClient {
    private static final String BASE_URL = "http://localhost:8000/api";
    private final Gson gson;

    public TaskAPIClient() {
        this.gson = new Gson();
    }

    /**
     * Fetch all tasks from Python backend
     * References: GET /api/tasks in backend/main.py
     */
    public List<Task> getAllTasks() {
        try {
            URL url = new URL(BASE_URL + "/tasks");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.setRequestProperty("Accept", "application/json");

            int responseCode = conn.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream(), StandardCharsets.UTF_8));
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = in.readLine()) != null) {
                    response.append(line);
                }
                in.close();

                // Parse JSON response matching Python Task model structure
                Task[] tasks = gson.fromJson(response.toString(), Task[].class);
                return List.of(tasks);
            }
        } catch (Exception e) {
            System.err.println("Error fetching tasks from API: " + e.getMessage());
        }
        return new ArrayList<>();
    }

    /**
     * Get task by ID from Python backend
     * References: GET /api/tasks/{task_id} in backend/main.py
     */
    public Task getTaskById(int id) {
        try {
            URL url = new URL(BASE_URL + "/tasks/" + id);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.setRequestProperty("Accept", "application/json");

            int responseCode = conn.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream(), StandardCharsets.UTF_8));
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = in.readLine()) != null) {
                    response.append(line);
                }
                in.close();

                return gson.fromJson(response.toString(), Task.class);
            }
        } catch (Exception e) {
            System.err.println("Error fetching task from API: " + e.getMessage());
        }
        return null;
    }

    /**
     * Create task via Python backend
     * References: POST /api/tasks in backend/main.py
     */
    public Task createTask(String title, String description, Priority priority) {
        try {
            URL url = new URL(BASE_URL + "/tasks");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");
            conn.setRequestProperty("Accept", "application/json");
            conn.setDoOutput(true);

            // Create JSON matching Python TaskCreate model
            JsonObject taskJson = new JsonObject();
            taskJson.addProperty("title", title);
            taskJson.addProperty("description", description != null ? description : "");
            taskJson.addProperty("completed", false);
            taskJson.addProperty("priority", priority.getValue());

            try (OutputStream os = conn.getOutputStream()) {
                byte[] input = taskJson.toString().getBytes(StandardCharsets.UTF_8);
                os.write(input, 0, input.length);
            }

            int responseCode = conn.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK || responseCode == HttpURLConnection.HTTP_CREATED) {
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream(), StandardCharsets.UTF_8));
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = in.readLine()) != null) {
                    response.append(line);
                }
                in.close();

                return gson.fromJson(response.toString(), Task.class);
            }
        } catch (Exception e) {
            System.err.println("Error creating task via API: " + e.getMessage());
        }
        return null;
    }

    /**
     * Update task via Python backend
     * References: PUT /api/tasks/{task_id} in backend/main.py
     */
    public Task updateTask(int id, String title, String description, Boolean completed, Priority priority) {
        try {
            URL url = new URL(BASE_URL + "/tasks/" + id);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("PUT");
            conn.setRequestProperty("Content-Type", "application/json");
            conn.setRequestProperty("Accept", "application/json");
            conn.setDoOutput(true);

            // Create JSON matching Python TaskUpdate model
            JsonObject taskJson = new JsonObject();
            if (title != null) taskJson.addProperty("title", title);
            if (description != null) taskJson.addProperty("description", description);
            if (completed != null) taskJson.addProperty("completed", completed);
            if (priority != null) taskJson.addProperty("priority", priority.getValue());

            try (OutputStream os = conn.getOutputStream()) {
                byte[] input = taskJson.toString().getBytes(StandardCharsets.UTF_8);
                os.write(input, 0, input.length);
            }

            int responseCode = conn.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream(), StandardCharsets.UTF_8));
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = in.readLine()) != null) {
                    response.append(line);
                }
                in.close();

                return gson.fromJson(response.toString(), Task.class);
            }
        } catch (Exception e) {
            System.err.println("Error updating task via API: " + e.getMessage());
        }
        return null;
    }

    /**
     * Delete task via Python backend
     * References: DELETE /api/tasks/{task_id} in backend/main.py
     */
    public boolean deleteTask(int id) {
        try {
            URL url = new URL(BASE_URL + "/tasks/" + id);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("DELETE");

            int responseCode = conn.getResponseCode();
            return responseCode == HttpURLConnection.HTTP_OK;
        } catch (Exception e) {
            System.err.println("Error deleting task via API: " + e.getMessage());
        }
        return false;
    }
}

