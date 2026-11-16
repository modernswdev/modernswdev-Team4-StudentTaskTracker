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
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(100) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);
INSERT INTO users (username, password)
VALUES ('student', 'test123');

SELECT * FROM tasks;
SELECT * FROM student_task_tracker.tasks;
SELECT * FROM users;
SELECT * FROM student_task_tracker.users;