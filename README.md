# MiniS

A simple relational database written in C++.

## Architecture:

- Frontend:
    - tokenizer
    - parser

- Backend:
    - virtual machine
    - b-tree
    - disk manager: handle read/write to disk

### Tokenizer and Parser

Currently, support insert and select queries.

### Data Storage Structure

The database is stored in a single file called `minis.db`.
The file contains a header and a sequence of records.
The header contains the number of records stored in the file.
The record contains only three fields: id, name, and email.

| Field Name | Type      |
|------------|-----------|
| id         | int       |
| name       | char[32]  |
| email      | char[255] |

| Num tuples = 3 | 
|----------------|
| Record 1       |
| Record 2       |
| Record 3       |

Problem with this design:
whenever we want to find a record, for example, with id = 100,
we have to scan through all the pages to find the record.




