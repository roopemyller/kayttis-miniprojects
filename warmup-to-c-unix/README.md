# Warmup to C and UNIX programming

## Summary

For this project, I implemented a command-line utility called `reverse` that reads text from an input source and outputs the lines in reverse order. The program handles three different usage scenarios:

1. `./reverse` - Reads from standard input and prints to standard output
2. `./reverse input.txt` - Reads from the specified input file and prints to standard output
3. `./reverse input.txt output.txt` - Reads from the specified input file and writes to the specified output file

## Design choices

- I chose to use linked list since it is the best way to dynamically allocate memory. Linked list also makes it easy to reverse, especially when file is read and last read line is also the tail (last node) and therefore can be traversed from tail to head because of the data structure.

- Instead of reading lines by allocating fixed-size buffers (e.g., limiting line length to 1024 characters) or character by character, I used the `getline()` function which dynamically allocates memory for lines of any length.

## Compiling and Running

While in the warmup-to-c-unix folder:<br>
`gcc reverse.c -o reverse`

Run with:<br>
`./reverse <input> <output>`<br>
where input and output are optional (expect input must be given if output is given)

## Examples

Input file contents (named as `input` in examples):

```
1
2
3
Sauna
```

Compile:
![Compile](img/compile-reverse.png)

Run with input parameter:
![Run with input parameter](img/reverse-input.png)

Run with input and output parameter:
![Run with input and output parameter](img/reverse-output.png)

## Points requested

| Requirement                                                                              | Points |
| ---------------------------------------------------------------------------------------- | :----: |
| Everything submitted compiles and works at least on some level.                          |   1    |
| The documentation is appropriate, correct and the repository is available                |   0    |
| The documentation is detailed, and the provided source code is reasonably well commented |   1    |
| All additional assumptions                                                               |   1    |
| Errors mentioned are addressed                                                           |   2    |
