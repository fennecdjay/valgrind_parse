# Valgrind output made easy :champagne:

This is a small program that takes valgrind outputs and filters it,
so that you only see relevant information.

## Usage
### Directly read valgrind's output

``` sh
valgrind <valgrind options> test_program 2>&1 > valgrind_parse
```

### From a log
#### Generating a valgrind's log
``` sh
valgrind --log-file=my_log <valgrind options> test_program
```

### Reading the log
There are two way of operations:
### With the log as argument
``` sh
valgrind_parse my_log
```
### With a pipe
``` sh
cat my_log | valgrind_parse
```

## 

### build
``` sh
make
``` sh
### clean
``` sh
mae clean
``` sh
### install
``` sh
make install
``` sh
### uninstall
``` sh
make uninstall
```
### test
```
make test
```
