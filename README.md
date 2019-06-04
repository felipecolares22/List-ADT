# Abstract Data Type List
In this project our objective is to build our own version of the std::vector with linked lists, the sc::list.

### Dependencies
* `cmake`
* `make`
* `g++`
* `google tests`
* `Doxygen (to gerenate code documentation)`

### Usage
To use the library, you will need to import the `list.h` file located on the `include` folder to your project. Look the documentation for a more detailed explanation of each sc::list method.

### Generate Documentation
Go to your project directory and type

```bash
doxygen config
```

Then, open in your browser the `index.html` file, located on the `docs/html/` folder.

### Run Tests

#### Compile
To test the `sc::list` library, go to the project directory and type

```bash
mkdir build
cd build
cmake ../
make
```

#### Run
Type `./list_tests` and see the results.

## Authorship
Program developed by [Matheus de Andrade](https://github.com/matheusmas132) and [Felipe Colares](https://github.com/felipecolares22), 2019.1

