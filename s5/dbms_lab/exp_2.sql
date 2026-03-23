CREATE TABLE employee(
	name VARCHAR(20),
	age INT,
	salary FLOAT,
	title VARCHAR(20)
);

INSERT INTO employee VALUES 
	("Mahesh", 50, 95000, "Manager"),
	("Nimitha", 35, 50000, "Programmer"),
	("Ashitha", 28, 35000, "Programmer"),
	("Ajay", 32, 27000, "Technician"),
	("Roy", 24, 34000, "Programmer");
	
1.	SELECT  * FROM employee;

	+---------+------+--------+------------+
	| name    | age  | salary | title      |
	+---------+------+--------+------------+
	| Mahesh  |   50 |  95000 | Manager    |
	| Nimitha |   35 |  50000 | Programmer |
	| Ashitha |   28 |  35000 | Programmer |
	| Ajay    |   32 |  27000 | Technician |
	| Roy     |   24 |  34000 | Programmer |
	+---------+------+--------+------------+
	
2. 	SELECT *
	FROM employee
	WHERE salary > 35000;
	
	+---------+------+--------+------------+
	| name    | age  | salary | title      |
	+---------+------+--------+------------+
	| Mahesh  |   50 |  95000 | Manager    |
	| Nimitha |   35 |  50000 | Programmer |
	+---------+------+--------+------------+

3.	SELECT name
	FROM employee
	WHERE age < 35;
	+---------+
	| name    |
	+---------+
	| Ashitha |
	| Ajay    |
	| Roy     |
	+---------+

4.	SELECT name, salary
	FROM employee
	WHERE title = "Programmer";
	
	+---------+--------+
	| name    | salary |
	+---------+--------+
	| Nimitha |  50000 |
	| Ashitha |  35000 |
	| Roy     |  34000 |
	+---------+--------+

5. 	SELECT name
	FROM employee
	WHERE name LIKE "%ith%";
	
	+---------+
	| name    |
	+---------+
	| Nimitha |
	| Ashitha |
	+---------+
	
6. 	SELECT name
	FROM employee
	WHERE name LIKE "A%";
	
	+---------+
	| name    |
	+---------+
	| Ashitha |
	| Ajay    |
	+---------+
7.	SELECT *
	FROM employee
	WHERE age > 35;
	
	+--------+------+--------+---------+
	| name   | age  | salary | title   |
	+--------+------+--------+---------+
	| Mahesh |   50 |  95000 | Manager |
	+--------+------+--------+---------+
	
8. 	SELECT *
	FROM employee
	WHERE title = "Technician";
	
	+------+------+--------+------------+
	| name | age  | salary | title      |
	+------+------+--------+------------+
	| Ajay |   32 |  27000 | Technician |
	+------+------+--------+------------+

9.	SELECT AVG(salary)
	FROM employee;
	
	+-------------+
	| AVG(salary) |
	+-------------+
	|       48200 |
	+-------------+

10.	SELECT name
	FROM employee
	ORDER BY name;

	+---------+
	| name    |
	+---------+
	| Ajay    |
	| Ashitha |
	| Mahesh  |
	| Nimitha |
	| Roy     |
	+---------+

11.	SELECT * 
	FROM employee
	ORDER BY age;
	
	+---------+------+--------+------------+
	| name    | age  | salary | title      |
	+---------+------+--------+------------+
	| Roy     |   24 |  34000 | Programmer |
	| Ashitha |   28 |  35000 | Programmer |
	| Ajay    |   32 |  27000 | Technician |
	| Nimitha |   35 |  50000 | Programmer |
	| Mahesh  |   50 |  95000 | Manager    |
	+---------+------+--------+------------+
	
12.	SELECT MAX(salary), MIN(salary)
	FROM employee;
	
	+-------------+-------------+
	| MAX(salary) | MIN(salary) |
	+-------------+-------------+
	|       95000 |       27000 |
	+-------------+-------------+

13.	SELECT COUNT(*)
	FROM employee
	WHERE salary > 30000;

	+----------+
	| COUNT(*) |
	+----------+
	|        4 |
	+----------+
	
14.	SELECT name
	FROM employee
	WHERE name LIKE "__h%" AND age BETWEEN 20 AND 50;
	
	+---------+
	| name    |
	+---------+
	| Mahesh  |
	| Ashitha |
	+---------+

15.	SELECT title, COUNT(*)
	FROM employee
	GROUP BY title;

	+------------+----------+
	| title      | COUNT(*) |
	+------------+----------+
	| Manager    |        1 |
	| Programmer |        3 |
	| Technician |        1 |
	+------------+----------+

