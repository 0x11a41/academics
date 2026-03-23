CREATE TABLE student (
	roll_no INT,
	name VARCHAR(20),
	age INT,
	aadhar VARCHAR(12),
	mark INT,
	dno INT
);

CREATE TABLE dept (
	dno INT,
	dname VARCHAR(10)
);

1) ALTER TABLE student MODIFY roll_no INT PRIMARY KEY;
   ALTER TABLE dept MODIFY dno INT PRIMARY KEY;
	
2) ALTER TABLE student MODIFY aadhar VARCHAR(20) UNIQUE;
	
3) ALTER TABLE student MODIFY name VARCHAR(20) NOT NULL;
	
4) ALTER TABLE student MODIFY age INT CHECK(age > 0);

5) ALTER TABLE student MODIFY mark FLOAT;

6) ALTER TABLE student ADD COLUMN grade VARCHAR(2) NOT NULL;

7) ALTER TABLE student ADD FOREIGN KEY(dno) REFERENCES dept(dno);

8) ALTER TABLE student DROP PRIMARY KEY;
   ALTER TABLE student MODIFY aadhar VARCHAR(20) PRIMARY KEY;

9) ALTER TABLE student DROP COLUMN grade;

	DESC student;
	+---------+-------------+------+-----+---------+-------+
	| Field   | Type        | Null | Key | Default | Extra |
	+---------+-------------+------+-----+---------+-------+
	| roll_no | int         | NO   |     | NULL    |       |
	| name    | varchar(20) | NO   |     | NULL    |       |
	| age     | int         | YES  |     | NULL    |       |
	| aadhar  | varchar(20) | NO   | PRI | NULL    |       |
	| mark    | float       | YES  |     | NULL    |       |
	| dno     | int         | YES  | MUL | NULL    |       |
	+---------+-------------+------+-----+---------+-------+

	DESC dept;
	+-------+-------------+------+-----+---------+-------+
	| Field | Type        | Null | Key | Default | Extra |
	+-------+-------------+------+-----+---------+-------+
	| dno   | int         | NO   | PRI | NULL    |       |
	| dname | varchar(10) | YES  |     | NULL    |       |
	+-------+-------------+------+-----+---------+-------+



