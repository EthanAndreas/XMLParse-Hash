# XML file parsing and hashing
[![version](https://img.shields.io/badge/version-0.0.1-blue.svg)](https://github.com/EthanAndreas/XMLParse-Hash)
[![compiler](https://img.shields.io/badge/compiler-gcc-red.svg)](https://github.com/EthanAndreas/XMLParse-Hash/blob/main/Makefile)
[![author](https://img.shields.io/badge/author-EthanAndreas-blue)](https://github.com/EthanAndreas)

## Table of Contents
1. [Functionality](#functionality)
2. [Command](#command)
3. [Tests](#tests)

## Functionality
- Parse XML file into binary file
- Build a hash table from the parsed file
- Make a research of an author 
- Display article from an author
- Display number of author and article
- Option to measure the runtime of each step

## Command

- Compilation :
```bash
make
```

- Launch :
```bash
./bin/exe <options>
```

- Help :
```bash
./bin/exe -h
```
 
 ## Tests 
 ```bash
 cd tests
 make
 ./bin/tests
 cd ..
 ```
