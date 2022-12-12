# XML file parsing with hashing

## Language

C

## Presentation

* Project's compilation :
```bash
make clean
make
```

* Project's launch :
Print the time to parse and build the hashinge table
```bash
./bin/exe -i <interface> -o <interface> -p -g -t
```
Print the line of an that containing NAME
```bash
./bin/exe -o <interface> -l NAME -a AUTHOR -r -s 
```
Print articles of an author
```bash
./bin/exe -o <interface> -a AUTHOR 
```
Print articles the number of unique authors and the number of articles
```bash
./bin/exe -o <interface> -r -s 
 ```
 
 * Test's launch :
 ```bash
 cd tests
 make
 ./bin/tests
 cd ..
 ```
