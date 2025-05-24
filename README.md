# MiniS

A simple relational database written in C++.

## Architecture:

- Frontend:
    - tokenizer
    - parser

- Backend:
    - command handler
    - disk manager: handle read/write to disk

### Tokenizer and Parser

Currently, support insert and select queries.

### Data Storage Format

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

### Improve performance with B+tree

With the current format, each page stores rows sequentially; thus, insertion is also fast because we just append to the
end. However, searching a particular row requires scanning all the pages.

To solve this problem, we can use a B+tre to index the rows. The key of the B+tree is the id of the row, and
the value is the page number and row id (kinda redundant atm). Within this information, we can find the corresponding
page in constant time and then find the row in that page in constant time as well.

**Note:**
Full-fledge B-plus-tree is f*cking complex. In this phase, I keep it simple stupid with only two supported operations:
**insert** and **find**.

## References:

https://loveforprogramming.quora.com/Memory-locality-the-magic-of-B-Trees
https://15445.courses.cs.cmu.edu/fall2024/project2/