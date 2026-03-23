CREATE TABLE dept_details(
	dept_id int PRIMARY KEY,
	title VARCHAR(20) NOT NULL,
	location VARCHAR(20) NOT NULL
);

CREATE TABLE emp_table(
	emp_id INT PRIMARY KEY,
	dept_id INT,
	job VARCHAR(20),
	salary FLOAT,
	FOREIGN KEY (dept_id) REFERENCES dept_details(dept_id)
);

CREATE TABLE emp_details(
	emp_id INT PRIMARY KEY,
	fname VARCHAR(20) NOT NULL,
	lname VARCHAR(20) NOT NULL,
	city varchar(20) NOT NULL,
	hire_date DATE NOT NULL,
	FOREIGN KEY (emp_id) REFERENCES emp_table(emp_id)
);

INSERT INTO dept_details VALUES
(1, 'HR', 'New York'),
(2, 'IT', 'Francisco'),
(3, 'Marketing', 'Chicago'),
(4, 'Finance', 'Dallas'),
(5, 'Operations', 'Seattle'),
(6, 'Sales', 'Boston');

INSERT INTO emp_table VALUES
(1, 1, 'Manager', 18500),
(2, 2, 'Developer', 22000),
(3, 5, 'Executive', 14500),
(4, 4, 'Analyst', 20000),
(5, 3, 'Programmer', 17500),
(6, 6, 'Salesprson', 12000),
(7, 1, 'Assistant', 15000),
(8, 2, 'Sys Admin', 21000),
(9, 4, 'Director', 25000),
(10, 3, 'Project leader', 18000),
(11, 5, 'Speclist', 16000),
(12, 6, 'Rep', 13000);

INSERT INTO emp_details VALUES
(1, 'John', 'Smith', 'New York', '1995-06-15'),
(2, 'Sarah', 'Lewis', 'Punnapra', '2001-03-22'),
(3, 'James', 'Clark', 'Chicago', '1997-08-11'),
(4, 'David', 'Jones', 'Dallas', '2000-12-09'),
(5, 'Eve', 'Lake', 'Seattle', '2003-11-01'),
(6, 'Alice', 'Park', 'Boston', '1999-05-19'),
(7, 'Emma', 'Dove', 'New York', '2002-04-14'),
(8, 'Laura', 'Wells', 'Punnapra', '1996-09-10'),
(9, 'Gary', 'King', 'Chicago', '2004-02-21'),
(10, 'Megan', 'Green', 'Dallas', '1998-07-25'),
(11, 'Tom', 'Gray', 'Seattle', '1994-01-30'),
(12, 'Paul', 'Gates', 'Boston', '2003-06-18');

emp_details
	+--------+-------+-------+----------+------------+
	| emp_id | fname | lname | city     | hire_date  |
	+--------+-------+-------+----------+------------+
	|      1 | John  | Smith | New York | 1995-06-15 |
	|      2 | Sarah | Lewis | Punnapra | 2001-03-22 |
	|      3 | James | Clark | Chicago  | 1997-08-11 |
	|      4 | David | Jones | Dallas   | 2000-12-09 |
	|      5 | Eve   | Lake  | Seattle  | 2003-11-01 |
	|      6 | Alice | Park  | Boston   | 1999-05-19 |
	|      7 | Emma  | Dove  | New York | 2002-04-14 |
	|      8 | Laura | Wells | Punnapra | 1996-09-10 |
	|      9 | Gary  | King  | Chicago  | 2004-02-21 |
	|     10 | Megan | Green | Dallas   | 1998-07-25 |
	|     11 | Tom   | Gray  | Seattle  | 1994-01-30 |
	|     12 | Paul  | Gates | Boston   | 2003-06-18 |
	+--------+-------+-------+----------+------------+
	
dept_details
	+---------+------------+-----------+
	| dept_id | title      | location  |
	+---------+------------+-----------+
	|       1 | HR         | New York  |
	|       2 | IT         | Francisco |
	|       3 | Marketing  | Chicago   |
	|       4 | Finance    | Dallas    |
	|       5 | Operations | Seattle   |
	|       6 | Sales      | Boston    |
	+---------+------------+-----------+
	
emp_table
	+--------+--------+----------------+--------+
	| emp_id | dept_id | job            | salary |
	+--------+--------+----------------+--------+
	|      1 |      1 | Manager        |  18500 |
	|      2 |      2 | Developer      |  22000 |
	|      3 |      5 | Executive      |  14500 |
	|      4 |      4 | Analyst        |  20000 |
	|      5 |      3 | Programmer     |  17500 |
	|      6 |      6 | Salesprson     |  12000 |
	|      7 |      1 | Assistant      |  15000 |
	|      8 |      2 | Sys Admin      |  21000 |
	|      9 |      4 | Director       |  25000 |
	|     10 |      3 | Project leader |  18000 |
	|     11 |      5 | Speclist       |  16000 |
	|     12 |      6 | Rep            |  13000 |
	+--------+--------+----------------+--------+

1. 	SELECT emp_id, fname, lname
	FROM emp_details
	WHERE LENGTH(fname) = LENGTH(lname)
	AND
	fname = CONCAT(UPPER(LEFT(fname, 1)), LOWER(SUBSTR(fname, 2)))
	AND
	lname = CONCAT(UPPER(LEFT(lname, 1)), LOWER(SUBSTR(lname, 2)));
	
	+--------+-------+-------+
	| emp_id | fname | lname |
	+--------+-------+-------+
	|      2 | sarah | Lewis |
	|      3 | James | Clark |
	|      4 | David | Jones |
	|      7 | Emma  | Dove  |
	|      8 | Laura | Wells |
	|      9 | Gary  | King  |
	|     10 | Megan | Green |
	+--------+-------+-------+
	
2.	SELECT CONCAT(UPPER(LEFT(city, 1)), LOWER(SUBSTR(city, 2))) AS city
	FROM emp_details;
	
	+----------+
	| city     |
	+----------+
	| New york |
	| Punnapra |
	| Chicago  |
	| Dallas   |
	| Seattle  |
	| Boston   |
	| New york |
	| Punnapra |
	| Chicago  |
	| Dallas   |
	| Seattle  |
	| Boston   |
	+----------+
	
3. 	SELECT emp_id, fname, lname
	FROM emp_details
	WHERE emp_id IN(3,4,5,1)
	ORDER BY fname, lname;
	
	+--------+-------+-------+
	| emp_id | fname | lname |
	+--------+-------+-------+
	|      4 | David | Jones |
	|      5 | Eve   | Lake  |
	|      3 | James | Clark |
	|      1 | John  | Smith |
	+--------+-------+-------+
	
4. 	SELECT fname, lname, dept_id
	FROM emp_details
	NATURAL JOIN emp_table
	WHERE dept_id = 3
	AND
	job IN ("Programmer", "Project leader");

	+-------+-------+---------+
	| fname | lname | dept_id |
	+-------+-------+---------+
	| Eve   | Lake  |       3 |
	| Megan | Green |       3 |
	+-------+-------+---------+

5. 	SELECT fname, lname, dept_id, salary
	FROM emp_details
	NATURAL JOIN emp_table
	WHERE salary BETWEEN 7000 AND 15000;
	+-------+-------+---------+--------+
	| fname | lname | dept_id | salary |
	+-------+-------+---------+--------+
	| Alice | Park  |       6 |  13800 |
	| Paul  | Gates |       6 |  14950 |
	+-------+-------+---------+--------+
	
6.	UPDATE emp_table
	SET salary = salary * 1.15
	WHERE dept_id IN (4, 3);

	+--------+---------+----------------+--------+
	| emp_id | dept_id | job            | salary |
	+--------+---------+----------------+--------+
	|      1 |       1 | Manager        |  18500 |
	|      2 |       2 | Developer      |  22000 |
	|      3 |       5 | Executive      |  14500 |
	|      4 |       4 | Analyst        |  23000 |
	|      5 |       3 | Programmer     |  20125 |
	|      6 |       6 | Salesprson     |  12000 |
	|      7 |       1 | Assistant      |  15000 |
	|      8 |       2 | Sys Admin      |  21000 |
	|      9 |       4 | Director       |  28750 |
	|     10 |       3 | Project leader |  20700 |
	|     11 |       5 | Speclist       |  16000 |
	|     12 |       6 | Rep            |  13000 |
	+--------+---------+----------------+--------+


7.	SELECT COUNT(*) AS number_of_rows
	FROM emp_table;
	
	+----------------+
	| number_of_rows |
	+----------------+
	|             12 |
	+----------------+
	
8. 	SELECT CURDATE() AS today, LAST_DAY(CURDATE()) as end_of_month;

	+------------+--------------+
	| today      | end_of_month |
	+------------+--------------+
	| 2025-08-06 | 2025-08-31   |
	+------------+--------------+
	
9. 	SELECT emp_id, emp_id * emp_id AS square
	FROM emp_table;

	+--------+--------+
	| emp_id | square |
	+--------+--------+
	|     10 |    100 |
	+--------+--------+
	
10.	SELECT CONCAT("Mr/Mrs ", fname, " ", lname, " is working at ", title, " department of abc company, located at ", location) AS emp_info
	FROM emp_table
	NATURAL JOIN emp_details
	NATURAL JOIN dept_details
	WHERE title = "Sales";
	
	+------------------------------------------------------------------------------------+
	| emp_info                                                                           |
	+------------------------------------------------------------------------------------+
	| Mr/Mrs Alice Park is working at Sales department of abc company, located at Boston |
	| Mr/Mrs Paul Gates is working at Sales department of abc company, located at Boston |
	+------------------------------------------------------------------------------------+

11.	SELECT *
	FROM emp_details
	WHERE DATEDIFF(CURDATE(), hire_date) > 365;
	
	+--------+-------+-------+----------+------------+
	| emp_id | fname | lname | city     | hire_date  |
	+--------+-------+-------+----------+------------+
	|      1 | John  | Smith | New York | 1995-06-15 |
	|      2 | Sarah | Lewis | Punnapra | 2001-03-22 |
	|      3 | James | Clark | Chicago  | 1997-08-11 |
	|      4 | David | Jones | Dallas   | 2000-12-09 |
	|      5 | Eve   | Lake  | Seattle  | 2003-11-01 |
	|      6 | Alice | Park  | Boston   | 1999-05-19 |
	|      7 | Emma  | Dove  | New York | 2002-04-14 |
	|      8 | Laura | Wells | Punnapra | 1996-09-10 |
	|      9 | Gary  | King  | Chicago  | 2004-02-21 |
	|     10 | Megan | Green | Dallas   | 1998-07-25 |
	|     11 | Tom   | Gray  | Seattle  | 1994-01-30 |
	|     12 | Paul  | Gates | Boston   | 2003-06-18 |
	+--------+-------+-------+----------+------------+

12. SELECT DATE_ADD(CURDATE(), INTERVAL (7 - WEEKDAY(CURDATE()) + 3) % 7 DAY) AS next_friday;
	
	+-------------+
	| next_friday |
	+-------------+
	| 2025-08-07  |
	+-------------+

13.	UPDATE dept_details
	SET title = UPPER(title);
	
	+---------+------------+-----------+
	| dept_id | title      | location  |
	+---------+------------+-----------+
	|       1 | HR         | New York  |
	|       2 | IT         | Francisco |
	|       3 | MARKETING  | Chicago   |
	|       4 | FINANCE    | Dallas    |
	|       5 | OPERATIONS | Seattle   |
	|       6 | SALES      | Boston    |
	+---------+------------+-----------+
14.	SELECT emp_id, DATE_FORMAT(hire_date, "%m/%d/%y") AS hire_date
	FROM emp_details;
	
	+--------+-----------+
	| emp_id | hire_date |
	+--------+-----------+
	|      1 | 06/15/95  |
	|      2 | 03/22/01  |
	|      3 | 08/11/97  |
	|      4 | 12/09/00  |
	|      5 | 11/01/03  |
	|      6 | 05/19/99  |
	|      7 | 04/14/02  |
	|      8 | 09/10/96  |
	|      9 | 02/21/04  |
	|     10 | 07/25/98  |
	|     11 | 01/30/94  |
	|     12 | 06/18/03  |
	+--------+-----------+
	
15. SELECT dept_id, AVG(salary)
	FROM emp_table
	GROUP BY dept_id;

	+---------+-------------+
	| dept_id | AVG(salary) |
	+---------+-------------+
	|       1 |       16750 |
	|       2 |       21500 |
	|       3 |     20412.5 |
	|       4 |       25875 |
	|       5 |       15250 |
	|       6 |       12500 |
	+---------+-------------+
	
16. SELECT *
	FROM emp_details
	WHERE emp_id % 2 != 0;

	+--------+-------+-------+----------+------------+
	| emp_id | fname | lname | city     | hire_date  |
	+--------+-------+-------+----------+------------+
	|      1 | John  | Smith | New York | 1995-06-15 |
	|      3 | James | Clark | Chicago  | 1997-08-11 |
	|      5 | Eve   | Lake  | Seattle  | 2003-11-01 |
	|      7 | Emma  | Dove  | New York | 2002-04-14 |
	|      9 | Gary  | King  | Chicago  | 2004-02-21 |
	|     11 | Tom   | Gray  | Seattle  | 1994-01-30 |
	+--------+-------+-------+----------+------------+

17.	SELECT dept_id, MAX(salary) AS max_salary, MIN(salary) AS min_salary
	FROM emp_table
	GROUP BY dept_id
	HAVING min_salary < 15000;

	+---------+------------+------------+
	| dept_id | max_salary | min_salary |
	+---------+------------+------------+
	|       5 |      16000 |       4500 |
	|       6 |      13000 |       2000 |
	+---------+------------+------------+
	
18.	SELECT TIMESTAMPDIFF(month, "1996-01-15", "1997-09-16") AS monthdiff;

	+-----------+
	| monthdiff |
	+-----------+
	|        20 |
	+-----------+
	
19. SELECT DISTINCT job
	FROM emp_table;

	+----------------+
	| job            |
	+----------------+
	| Manager        |
	| Developer      |
	| Executive      |
	| Analyst        |
	| Programmer     |
	| Salesprson     |
	| Assistant      |
	| Sys Admin      |
	| Director       |
	| Project leader |
	| Speclist       |
	| Rep            |
	+----------------+
	
20.	SELECT CONCAT(fname, " ", lname, " was hired on ", DAY(hire_date), "th of ", MONTHNAME(hire_date), " ", YEAR(hire_date)) AS hiring_info
	FROM emp_details;
	
	+-------------------------------------------------+
	| hiring_info                                     |
	+-------------------------------------------------+
	| John Smith was hired on 15th of June 1995       |
	| Sarah Lewis was hired on 22th of March 2001     |
	| James Clark was hired on 11th of August 1997    |
	| David Jones was hired on 9th of December 2000   |
	| Eve Lake was hired on 1th of November 2003      |
	| Alice Park was hired on 19th of May 1999        |
	| Emma Dove was hired on 14th of April 2002       |
	| Laura Wells was hired on 10th of September 1996 |
	| Gary King was hired on 21th of February 2004    |
	| Megan Green was hired on 25th of July 1998      |
	| Tom Gray was hired on 30th of January 1994      |
	| Paul Gates was hired on 18th of June 2003       |
	+-------------------------------------------------+
	

21, 22.	ALTER TABLE emp_details
	ADD COLUMN dob DATE;
	
	START TRANSACTION;
	
	SAVEPOINT sp;
	
	UPDATE emp_details
	SET dob = CASE emp_id
		WHEN 1 THEN '1980-01-15'
		WHEN 2 THEN '1985-05-10'
		WHEN 3 THEN '1979-03-23'
		WHEN 4 THEN '1988-11-19'
		WHEN 5 THEN '1990-06-05'
		WHEN 6 THEN '1992-09-17'
		WHEN 7 THEN '1986-04-03'
		WHEN 8 THEN '1983-02-14'
		WHEN 9 THEN '1991-12-28'
		WHEN 10 THEN '1984-08-09'
		WHEN 11 THEN '1977-07-01'
		WHEN 12 THEN '1989-10-26'
	END
	WHERE emp_id IN (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
	
	SELECT CONCAT(fname, " ", lname) AS name, TIMESTAMPDIFF(YEAR, dob, CURDATE()) AS age 
	FROM emp_details;
	
	+-------------+------+
	| name        | age  |
	+-------------+------+
	| John Smith  |   45 |
	| Sarah Lewis |   40 |
	| James Clark |   46 |
	| David Jones |   36 |
	| Eve Lake    |   35 |
	| Alice Park  |   32 |
	| Emma Dove   |   39 |
	| Laura Wells |   42 |
	| Gary King   |   33 |
	| Megan Green |   41 |
	| Tom Gray    |   48 |
	| Paul Gates  |   35 |
	+-------------+------+

23.	SELECT title, COUNT(*) AS no_of_employees
	FROM emp_table NATURAL JOIN dept_details
	GROUP BY dept_id;
	
	+------------+-----------------+
	| title      | no_of_employees |
	+------------+-----------------+
	| HR         |               2 |
	| IT         |               2 |
	| Marketing  |               2 |
	| Finance    |               2 |
	| Operations |               2 |
	| Sales      |               2 |
	+------------+-----------------+

24.	SELECT COUNT(*) AS no_of_employees
	FROM emp_details;

	+-----------------+
	| no_of_employees |
	+-----------------+
	|              12 |
	+-----------------+
	
25. ROLLBACK TO sp;

	select * from emp_details;
	+--------+-------+-------+----------+------------+------+
	| emp_id | fname | lname | city     | hire_date  | dob  |
	+--------+-------+-------+----------+------------+------+
	|      1 | John  | Smith | New York | 1995-06-15 | NULL |
	|      2 | Sarah | Lewis | Punnapra | 2001-03-22 | NULL |
	|      3 | James | Clark | Chicago  | 1997-08-11 | NULL |
	|      4 | David | Jones | Dallas   | 2000-12-09 | NULL |
	|      5 | Eve   | Lake  | Seattle  | 2003-11-01 | NULL |
	|      6 | Alice | Park  | Boston   | 1999-05-19 | NULL |
	|      7 | Emma  | Dove  | New York | 2002-04-14 | NULL |
	|      8 | Laura | Wells | Punnapra | 1996-09-10 | NULL |
	|      9 | Gary  | King  | Chicago  | 2004-02-21 | NULL |
	|     10 | Megan | Green | Dallas   | 1998-07-25 | NULL |
	|     11 | Tom   | Gray  | Seattle  | 1994-01-30 | NULL |
	|     12 | Paul  | Gates | Boston   | 2003-06-18 | NULL |
	+--------+-------+-------+----------+------------+------+

26.	DROP TABLE emp_details;
	DROP TABLE emp_table;	
	TRUNCATE TABLE dept_details;




