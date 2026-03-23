CREATE USER hari@localhost IDENTIFIED BY '#9Ulygocqv';
GRANT ALL PRIVILEGES ON *.* TO hari@localhost;
ALTER USER hari@localhost IDENTIFIED BY "Hari@123";
	
CREATE DATABASE college;
USE college;

Create table Student(
    Roll_no INT Primary Key,
    Fname Varchar(25),
    Lname Varchar(25),
    Mark Float,
    DOB Date,
    Did INT
);

Create table Department(
    Did INT Primary Key,
    Dname Varchar(25)
);

INSERT INTO Student VALUES
(101, 'Alice', 'Thomas', 85.5, '2003-04-15', 1),
(102, 'Bob', 'Mathew', 78.0, '2002-12-22', 2),
(103, 'Carol', 'Joseph', 92.3, '2003-08-10', 1),
(104, 'David', 'George', 66.7, '2002-11-05', 3),
(105, 'Eva', 'Francis', 74.5, '2003-01-30', 4),
(106, 'Frank', 'Davis', 80.0, '2002-06-18', 2),
(107, 'Grace', 'Antony', 88.9, '2003-03-25', 5),
(108, 'Hannah', 'Benny', 91.2, '2002-09-13', 1);

INSERT INTO Department VALUES
(1, 'Computer Science'),
(2, 'Electronics'),
(3, 'Mechanical'),
(4, 'Civil'),
(5, 'Electrical');

1.	CREATE VIEW student_view AS
	SELECT CONCAT(Fname, " ", Lname) AS FullName,
	TIMESTAMPDIFF(YEAR, DOB, CURDATE()) AS age,
	Dname FROM Student NATURAL JOIN Department;
	+--------------+------+------------------+
	| FullName     | age  | Dname            |
	+--------------+------+------------------+
	| Alice Thomas |   22 | Computer Science |
	| Bob Mathew   |   22 | Electronics      |
	| Carol Joseph |   22 | Computer Science |
	| David George |   22 | Mechanical       |
	| Eva Francis  |   22 | Civil            |
	| Frank Davis  |   23 | Electronics      |
	| Grace Antony |   22 | Electrical       |
	| Hannah Benny |   22 | Computer Science |
	+--------------+------+------------------+

	
2.	DROP VIEW student_view;

-- login to root user

3. 	REVOKE ALL PRIVILEGES ON *.* FROM hari@localhost;

	DROP USER hari@localhost;
	
	
