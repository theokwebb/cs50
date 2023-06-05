# cs50
Solutions to problem sets and labs from [CS50 course](https://cs50.harvard.edu/x/2023/).

## recover.c
Simple program from cs50 PS4 that recovers JPEGs from a forensic image.
- It assumes any slack space is zeroed and JPEGs are stored back-to-back.

## inheritance.c
Simple program from cs50’s Lab5 that simulates the inheritance of blood types for each member of a family.

## speller
A program designed to spell-check a file using a hash table after loading a dictionary of words from disk into memory.
- Usage: ./speller [dictionary] [text]
- [dictionary] is assumed to be a file which contains a list of alphabetically sorted lowercase words with one word per line, each of which ends with \n and is no longer than 45 characters.
- [text] is the file to be spell-checked. 
- Provision of dictionary is optional; if this argument is omitted, speller will use dictionaries/large by default.
- “misspelled” in output means that some word is not in the dictionary provided.
- Test with: ./speller dictionaries/large texts/lalaland.txt
