create database hajolista;
use hajolista;

create table hajo(
    az int not null primary key,
    nev varchar(255) not null,
    tipus varchar(255) not null,
    tulaz int null,
    uzemel boolean not null,
    foreign key (tulaz) references tulajdonos(az)
);

create table tort(
    az int not null primary key,
    hajoaz int not null,
    hajo varchar(255),
    foreign key (hajoaz) references hajo(az) 
);

create table tulajdonos(
    az int not null primary key,
    nev varchar(255) not null,
    varos varchar(255) not null
);

load data infile './hajo.txt'
load table hajo
field terminated by '\t'
lines terminated by '\n'
ignore 1 rows,
(az, nev, tipus, tulaz, uzemel);

LOAD DATA INFILE './tort.txt'
INTO TABLE tort
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(hajoaz, nev);

LOAD DATA INFILE './tulajdonos.txt'
INTO TABLE tulajdonos
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(az, nev, varos);

SELECT * FROM hajo;
SELECT * FROM tort;
SELECT * FROM tulajdonos;
2