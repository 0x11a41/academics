CREATE table student(
 SID INT PRIMARY KEY,
 SNAME VARCHAR(100),
 SEMESTER INT
 );
 
 CREATE TABLE book(
 BID INT PRIMARY KEY,
 BNAME VARCHAR(100),
 AUTHOR VARCHAR(100)
 );
 
 CREATE TABLE issuebook(
  IssueID INT PRIMARY KEY,
  BID INT,
  SID INT,
  issueDate DATE,
  FOREIGN KEY (SID) REFERENCES student(SID),
  FOREIGN KEY (BID) REFERENCES book(BID));
 
 INSERT INTO student VALUES 
 (1,'Alice',4),
 (2,'Bob',3),
 (3,'Floxy',2),
 (4,'John',4);
+-----+-------+----------+
| SID | SNAME | SEMESTER |
+-----+-------+----------+
|   1 | Alice |        4 |
|   2 | Bob   |        3 |
|   3 | Floxy |        2 |
|   4 | John  |        4 |
+-----+-------+----------+


 INSERT INTO book VALUES
 (101,'FAST FEAST','Jamie Oliver'),
 (102,'Mind Power ','Kiran Bedi'),
 (103,'Date World','A.Sharma'),
 (104,'Speed Maths','Kiran Bedi');
+-----+-------------+--------------+
| BID | BNAME       | AUTHOR       |
+-----+-------------+--------------+
| 101 | FAST FEAST  | Jamie Oliver |
| 102 | Mind Power  | Kiran Bedi   |
| 103 | Date World  | A.Sharma     |
| 104 | Speed Maths | Kiran Bedi   |
+-----+-------------+--------------+


 INSERT INTO issuebook VALUES
 (201,101,1,'2005-06-10'),
 (202,102,2,'2005-06-12'),
 (203,103,3,'2005-06-15');
+---------+------+------+------------+
| IssueID | BID  | SID  | issueDate  |
+---------+------+------+------------+
|     201 |  101 |    1 | 2005-06-10 |
|     202 |  102 |    2 | 2005-06-12 |
|     203 |  103 |    3 | 2005-06-15 |
+---------+------+------+------------+


 
1. SELECT S.*
   FROM student S
   JOIN issuebook I ON S.SID = I.SID
   JOIN book B ON I.BID = B.BID
   WHERE B.BNAME = 'FAST FEAST';

+-----+-------+----------+
| SID | SNAME | SEMESTER |
+-----+-------+----------+
|   1 | Alice |        4 |
+-----+-------+----------+


2. SELECT B.BNAME
   FROM book B
   JOIN issuebook I ON B.BID = I.BID
   WHERE I.issueDate < '2005-06-15';
+-------------+
| BNAME       |
+-------------+
| FAST FEAST  |
| Mind Power  |
+-------------+


3.SELECT S.* 
  FROM student S
  LEFT JOIN issuebook I ON S.SID = I.SID
  WHERE S.SEMESTER = 4
  AND I.SID IS NULL;
+-----+-------+----------+
| SID | SNAME | SEMESTER |
+-----+-------+----------+
|   4 | John  |        4 |
+-----+-------+----------+



4.SELECT B.BNAME
  FROM book B
  JOIN issuebook I ON B.BID = I.BID
  WHERE I.issueDate = '2005-06-12';
+-------------+
| BNAME       |
+-------------+
| Mind Power  |
+-------------+


5.SELECT B.BNAME
  FROM book B
  JOIN issuebook I ON B.BID = I.BID
  WHERE I.issueDate = (SELECT MAX(issueDate) FROM issuebook);
+------------+
| BNAME      |
+------------+
| Date World |
+------------+


6.SELECT DISTINCT S.SNAME
  FROM student S
  JOIN issuebook I ON S.SID = I.SID
  WHERE MONTH(I.issueDate) = 6;
+-------+
| SNAME |
+-------+
| Alice |
| Bob   |
| Floxy |
+-------+


7.SELECT DISTINCT S.SNAME
  FROM student S
  JOIN issuebook I ON S.SID = I.SID
  JOIN book B ON I.BID = B.BID
  WHERE B.Author = 'Kiran Bedi';
+-------+
| SNAME |
+-------+
| Bob   |
+-------+


8.SELECT B.BNAME
  FROM book B
  JOIN issuebook I ON B.BID = I.BID
  JOIN student S ON I.SID = S.SID
  WHERE S.SNAME = 'FLOXY';
+------------+
| BNAME      |
+------------+
| Date World |
+------------+


