CREATE TABLE Employees (
    Eid VARCHAR(5) PRIMARY KEY,
    Name VARCHAR(50),
    Age INT,
    Salary DECIMAL(10,2),
    Title VARCHAR(50),
    Joining_Date DATE
);

INSERT INTO Employees VALUES
('E1', 'Mahesh', 50, 115000.89, 'Manager', '1967-03-20'),
('E2', 'Namitha', 35, 110000.78, 'Programmer', '1981-08-02'),
('E3', 'Ashitha', 28, 35000.89, 'Programmer', '1988-09-01'),
('E4', 'Ajay', 32, 27000.36, 'Technician', '1975-02-23'),
('E5', 'Roy', 24, 34000.67, 'Programmer', '2019-03-02'),
('E6', 'Sindhu', 33, 36000.65, 'Technician', '1984-04-09');

Employees
+-----+---------+------+-----------+------------+--------------+
| Eid | Name    | Age  | Salary    | Title      | Joining_Date |
+-----+---------+------+-----------+------------+--------------+
| E1  | Mahesh  |   50 | 115000.89 | Manager    | 1967-03-20   |
| E2  | Namitha |   35 | 110000.78 | Programmer | 1981-08-02   |
| E3  | Ashitha |   28 |  35000.89 | Programmer | 1988-09-01   |
| E4  | Ajay    |   32 |  27000.36 | Technician | 1975-02-23   |
| E5  | Roy     |   24 |  34000.67 | Programmer | 2019-03-02   |
| E6  | Sindhu  |   33 |  36000.65 | Technician | 1984-04-09   |
+-----+---------+------+-----------+------------+--------------+

1.	SELECT DISTINCT title
	FROM Employees;
	
	+------------+
	| title      |
	+------------+
	| Manager    |
	| Programmer |
	| Technician |
	+------------+
	
2.	SELECT name
	FROM Employees
	WHERE salary > 35000 AND title != "Programmer";
	
	+--------+
	| name   |
	+--------+
	| Mahesh |
	| Sindhu |
	+--------+

3.	SELECT name
	FROM Employees
	WHERE salary BETWEEN 100000 AND 999999;
	
	+---------+
	| name    |
	+---------+
	| Mahesh  |
	| Namitha |
	+---------+

4. 	SELECT name
	FROM Employees
	WHERE DATEDIFF(CURDATE(), Joining_Date) / 360 > 35;
	
	+---------+
	| name    |
	+---------+
	| Mahesh  |
	| Namitha |
	| Ashitha |
	| Ajay    |
	| Sindhu  |
	+---------+
	
5.	SELECT name
	FROM Employees
	WHERE Title NOT IN ("Manager", "Programmer");
	
	+--------+
	| name   |
	+--------+
	| Ajay   |
	| Sindhu |
	+--------+

