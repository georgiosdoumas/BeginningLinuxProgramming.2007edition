-- page343create_children2.sql (a variation of page 339 )
-- Create the table children of database practicedb as per page 344 data [ the table that appears in the end of page ]
-- if you are in the directory where this sql program exists , connect to mysql and run so :
-- mysql> use practicedb
-- mysql> source page343create_children.sql  [ or mysql>\. page343create_children.sql ]
--
DROP TABLE children;
CREATE TABLE children (
    childno int(11) AUTO_INCREMENT NOT NULL  PRIMARY KEY,
    fname varchar(30),
    age int(11)
);
-- We assume that the TABLE children had some data from the work done on page 339, so first we deleted it and create a new
-- Populate the table 'children' , no need to assign childno values , since they are auto-increment
-- insert the specific 11 rows 

INSERT INTO children( fname,age) VALUES ('Jenny',21);
INSERT INTO children( fname,age) VALUES ('Andrew',17);
INSERT INTO children( fname,age) VALUES ('Gavin',9);
INSERT INTO children( fname,age) VALUES ('Duncan',6);
INSERT INTO children( fname,age) VALUES ('Emma',4);
INSERT INTO children( fname,age) VALUES ('Alex',15);
INSERT INTO children( fname,age) VALUES ('Adrian',9);
INSERT INTO children( fname,age) VALUES ('Ann',3);
INSERT INTO children( fname,age) VALUES ('Ann',4);
INSERT INTO children( fname,age) VALUES ('Ann',3);
INSERT INTO children( fname,age) VALUES ('Ann',4);
-- end

-- After running the above sql script , you can run the update1.c (hints for update.c are in page 344-345)
