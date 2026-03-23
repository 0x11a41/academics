1.	SELECT 345 * 12;
	+----------+
	| 345 * 12 |
	+----------+
	|     4140 |
	+----------+
	
2.	SELECT CURDATE(), DATE_ADD(CURDATE(),
	INTERVAL 1 DAY) AS next_date,
	LAST_DAY(CURDATE()) AS last_day;
	+------------+------------+------------+
	| CURDATE()  | next_date  | last_day   |
	+------------+------------+------------+
	| 2025-09-10 | 2025-09-11 | 2025-09-30 |
	+------------+------------+------------+
	
3.	CREATE TABLE student(
    roll_no INT PRIMARY KEY,
    fname VARCHAR(20),
    lname VARCHAR(20),
    mark FLOAT,
    dob DATE
	);
	
	INSERT INTO student VALUES
	(1, 'John', 'Doe', 85.5, '2000-01-15'),
	(2, 'Jane', 'Smith', 92.0, '1999-05-30'),
	(3, 'Alice', 'Johnson', 78.3, '2001-07-22'),
	(4, 'Bob', 'Brown', 88.7, '2000-12-10'),
	(5, 'Eve', 'Davis', 91.2, '1998-03-18')
	+---------+-------+---------+------+------------+
	| roll_no | fname | lname   | mark | dob        |
	+---------+-------+---------+------+------------+
	|       1 | John  | Doe     | 85.5 | 2000-01-15 |
	|       2 | Jane  | Smith   |   92 | 1999-05-30 |
	|       3 | Alice | Johnson | 78.3 | 2001-07-22 |
	|       4 | Bob   | Brown   | 88.7 | 2000-12-10 |
	|       5 | Eve   | Davis   | 91.2 | 1998-03-18 |
	+---------+-------+---------+------+------------+
	
	SELECT CONCAT (fname, " ", lname) AS name,
	LENGTH(CONCAT(fname, " ", lname)) AS length
	FROM student;
	+---------------+--------+
	| name          | length |
	+---------------+--------+
	| John Doe      |      8 |
	| Jane Smith    |     10 |
	| Alice Johnson |     13 |
	| Bob Brown     |      9 |
	| Eve Davis     |      9 |
	+---------------+--------+

4.	SELECT CONCAT(fname, " ", lname) AS full_name,
	TIMESTAMPDIFF(YEAR, DOB, CURDATE()) AS age
	FROM student;
	+---------------+------+
	| full_name     | age  |
	+-----------i----+------+
	| John Doe      |   25 |
	| Jane Smith    |   26 |
	| Alice Johnson |   24 |
	| Bob Brown     |   24 |
	| Eve Davis     |   27 |
	+---------------+------+

5.	SELECT CONCAT(fname, " ", lname) AS name,
	TIMESTAMPDIFF(YEAR, dob, CURDATE()) AS age
	FROM student;
	+---------------+------+
	| name          | age  |
	+---------------+------+
	| John Doe      |   25 |
	| Jane Smith    |   26 |
	| Alice Johnson |   24 |
	| Bob Brown     |   24 |
	| Eve Davis     |   27 |
	+---------------+------+

6.	SELECT COUNT(*) AS no_of_students,
	SUM(mark), MIN(mark), AVG(mark), MAX(mark)
	FROM student;
	+----------------+-------------------+-----------+-------------------+-----------+
	| no_of_students | SUM(mark)         | MIN(mark) | AVG(mark)         | MAX(mark) |
	+----------------+-------------------+-----------+-------------------+-----------+
	|              5 | 435.6999969482422 |      78.3 | 87.13999938964844 |        92 |
	+----------------+-------------------+-----------+-------------------+-----------+


