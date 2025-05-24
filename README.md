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

Improvement: using B+Tree to store pages.

Alternative Table Formats
-----
With the current format, each page stores only rows (no metadata) so it is pretty space efficient.
Insertion is also fast because we just append to the end.
However, finding a particular row can only be done by scanning the entire table.
And if we want to delete a row, we have to fill in the hole by moving every row that comes after it.

If we stored the table as an array, but kept rows sorted by id, we could use binary search to find a particular id.
However, insertion would be slow because we would have to move a lot of rows to make space.

Instead, we’re going with a tree structure. Each node in the tree can contain a variable number of rows, so we have to
store some information in each node to keep track of how many rows it contains. Plus there is the storage overhead of
all the internal nodes which don’t
store any rows. In exchange for a larger database file, we get fast insertion,
deletion and lookup.

Full-fledge B-plus-tree is f*cking complex. In this phase, I make it stupid simple as follow:

- The leaf node contains the lists of keys and the corresponding record ids.
- The internal node contains the lists of keys and the list of children node ptr.
- Support only insert and find methods.

# Reference:

https://loveforprogramming.quora.com/Memory-locality-the-magic-of-B-Trees
https://15445.courses.cs.cmu.edu/fall2024/project2/