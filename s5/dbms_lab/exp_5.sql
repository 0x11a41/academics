CREATE TABLE employee (
	emp_id VARCHAR(2) PRIMARY KEY,
	name VARCHAR(20),
	age INT,
	salary DECIMAL(10,2),
	title VARCHAR(12),
	joining_date DATE
);

INSERT INTO employee
VALUES("E1", "Mahesh", 50, 115000.89, "Manager", "1967-03-20"),
	("E2", "Nimitha", 35, 110000.78, "Programmer", "1981-08-02"),
	("E3", "Ashitha", 28, 35000.89, "Programmer", "1988-04-09"),
	("E4", "Ajay", 32, 27000.56, "Programmer", "1975-02-23"),
	("E5", "Roy", 24, 24000.67, "Programmer", "1990-05-05"),
	("E6", "Sindhu", 33, 36000.45, "Technician", "1984-04-09");
	
	employee
	+--------+---------+------+-----------+------------+--------------+
	| emp_id | name    | age  | salary    | title      | joining_date |
	+--------+---------+------+-----------+------------+--------------+
	| E1     | Mahesh  |   50 | 115000.89 | Manager    | 1967-03-20   |
	| E2     | Nimitha |   35 | 110000.78 | Programmer | 1981-08-02   |
	| E3     | Ashitha |   28 |  35000.89 | Programmer | 1988-04-09   |
	| E4     | Ajay    |   32 |  27000.56 | Programmer | 1975-02-23   |
	| E5     | Roy     |   24 |  24000.67 | Programmer | 1990-05-05   |
	| E6     | Sindhu  |   33 |  36000.45 | Technician | 1984-04-09   |
	+--------+---------+------+-----------+------------+--------------+


1)	CREATE TABLE employ_details AS
	SELECT emp_id, name, age, title, joining_date
	FROM employee;
	
	employ_details;
	+--------+---------+------+------------+--------------+
	| emp_id | name    | age  | title      | joining_date |
	+--------+---------+------+------------+--------------+
	| E1     | Mahesh  |   50 | Manager    | 1967-03-20   |
	| E2     | Nimitha |   35 | Programmer | 1981-08-02   |
	| E3     | Ashitha |   28 | Programmer | 1988-04-09   |
	| E4     | Ajay    |   32 | Programmer | 1975-02-23   |
	| E5     | Roy     |   24 | Programmer | 1990-05-05   |
	| E6     | Sindhu  |   33 | Technician | 1984-04-09   |
	+--------+---------+------+------------+--------------+
	
2)	CREATE TABLE emp_dept AS
	SELECT emp_id, joining_date
	FROM employee;
	
	ALTER TABLE emp_dept
	ADD COLUMN department_id VARCHAR(2);
	
	UPDATE emp_dept
	SET department_id = "D1"
	WHERE emp_id IN ("E3", "E4", "E5");
	
	UPDATE emp_dept
	SET department_id = "D2"
	WHERE emp_id IN ("E2", "E6");
	
	UPDATE emp_dept
	SET department_id = "D4"
	WHERE emp_id = "E1";
	
	emp_dept
	+--------+--------------+---------------+
	| emp_id | joining_date | department_id |
	+--------+--------------+---------------+
	| E1     | 1967-03-20   | D4            |
	| E2     | 1981-08-02   | D2            |
	| E3     | 1988-04-09   | D1            |
	| E4     | 1975-02-23   | D1            |
	| E5     | 1990-05-05   | D1            |
	| E6     | 1984-04-09   | D2            |
	+--------+--------------+---------------+
	
3)	CREATE TABLE emp_title AS
	SELECT emp_id, title
	FROM employee;
	
	emp_title
	+--------+------------+
	| emp_id | title      |
	+--------+------------+
	| E1     | Manager    |
	| E2     | Programmer |
	| E3     | Programmer |
	| E4     | Programmer |
	| E5     | Programmer |
	| E6     | Technician |
	+--------+------------+
	
4) 	CREATE TABLE emp_salary AS
	SELECT emp_id, salary
	FROM employee;
	
	emp_salary
	+--------+-----------+
	| emp_id | salary    |
	+--------+-----------+
	| E1     | 115000.89 |
	| E2     | 110000.78 |
	| E3     |  35000.89 |
	| E4     |  27000.56 |
	| E5     |  24000.67 |
	| E6     |  36000.45 |
	+--------+-----------+
	
5) 	CREATE TABLE department AS
	SELECT DISTINCT department_id
	FROM emp_dept;
	
	ALTER TABLE department
	ADD COLUMN name VARCHAR(20);
	
	UPDATE department
	SET name = "Production"
	WHERE department_id = "D1";
	
	UPDATE department
	SET name = "R&D"
	WHERE department_id = "D2";
	
	UPDATE department
	SET name = "Marketing"
	WHERE department_id = "D4";

	department
	+---------------+------------+
	| department_id | name       |
	+---------------+------------+
	| D4            | Marketing  |
	| D2            | R&D        |
	| D1            | Production |
	+---------------+------------+
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
