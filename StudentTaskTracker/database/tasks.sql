CREATE DATABASE IF NOT EXISTS student_task_tracker;

USE student_task_tracker;

CREATE TABLE IF NOT EXISTS tasks (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    course VARCHAR(100),
    dueDate DATE,
    priority VARCHAR(50),
    status VARCHAR(50) DEFAULT 'To Do',
    description TEXT
);

INSERT INTO tasks (title, course, dueDate, priority, status, description)
VALUES (
    'Finish Sprint 2',
    'Modern Software Development',
    '2026-10-28',
    'High',
    'In Progress',
    'Complete database connection and task data'
);

SELECT * FROM tasks;