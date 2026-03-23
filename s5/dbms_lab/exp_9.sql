1.CREATE TABLE Job (
    JID INT PRIMARY KEY,
    JNAME VARCHAR(50));

2.CREATE TABLE Department (
    DID INT PRIMARY KEY,
    DNAME VARCHAR(50));


3.CREATE TABLE Employee (
    EID INT PRIMARY KEY,
    ENAME VARCHAR(50),
    DID INT,
    JID INT,
    CONSTRAINT fk_department FOREIGN KEY (DID) 
        REFERENCES Department(DID) ON DELETE CASCADE ON UPDATE CASCADE);

4.ALTER TABLE Employee
 ADD CONSTRAINT fk_job FOREIGN KEY (JID)
 REFERENCES Job(JID) ON DELETE SET NULL;


5.INSERT INTO Job VALUES (100, 'P1'), (101, 'P2'), (102, 'P3');
+-----+-------+
| JID | JNAME |
+-----+-------+
| 100 | P1    |
| 101 | P2    |
| 102 | P3    |
+-----+-------+

-- Department data
INSERT INTO Department VALUES (10, 'Sales'), (11, 'Marketing');
+-----+-----------+
| DID | DNAME     |
+-----+-----------+
|  10 | Sales     |
|  11 | Marketing |
+-----+-----------+


-- Employee data
INSERT INTO Employee VALUES 
(1, 'A', 10, 100),
(2, 'B', 11, 101),
(3, 'C', 10, 101),
(4, 'D', 10, 100);
+-----+-------+------+------+
| EID | ENAME | DID  | JID  |
+-----+-------+------+------+
|   1 | A     |   10 |  100 |
|   2 | B     |   11 |  101 |
|   3 | C     |   10 |  101 |
|   4 | D     |   10 |  100 |
+-----+-------+------+------+

6.DELETE FROM Job WHERE JID = 102;
+-----+-------+------+------+
| EID | ENAME | DID  | JID  |
+-----+-------+------+------+
|   1 | A     |   10 |  100 |
|   2 | B     |   11 |  101 |
|   3 | C     |   10 |  101 |
|   4 | D     |   10 |  100 |
+-----+-------+------+------+


7. DELETE FROM Job WHERE JID = 101;
+-----+-------+------+------+
| EID | ENAME | DID  | JID  |
+-----+-------+------+------+
|   1 | A     |   10 |  100 |
|   2 | B     |   11 | NULL |
|   3 | C     |   10 | NULL |
|   4 | D     |   10 |  100 |
+-----+-------+------+------+


8.DELETE FROM Department WHERE DID = 11;
+-----+-------+------+------+
| EID | ENAME | DID  | JID  |
+-----+-------+------+------+
|   1 | A     |   10 |  100 |
|   3 | C     |   10 | NULL |
|   4 | D     |   10 |  100 |
+-----+-------+------+------+


9.UPDATE Department SET DID = 13 WHERE DNAME = 'Sales';

+-----+-------+
| DID | DNAME |
+-----+-------+
|  13 | Sales |
+-----+-------+


10. ALTER TABLE Employee DROP FOREIGN KEY fk_job;
+-----+-------+------+------+
| EID | ENAME | DID  | JID  |
+-----+-------+------+------+
|   1 | A     |   10 |  100 |
|   3 | C     |   10 | NULL |
|   4 | D     |   10 |  100 |
+-----+-------+------+------+



