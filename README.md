# beetchef-core

### prerequisites

1. `$ apt install g++`
2. `$ apt install make`
3. `$ apt install cmake`

### build

1. navigate to beetchef-core root directory
2. `$ cmake .` (this step needs to be run just once to generate Makefile, after that it's sufficient to build project with just `$ make`)
3. `$ make` (this generates executable `beetchef` in `./build/bin/`)


### execution

1. navigate to beetchef-core root directory
2. `$ make run`  
    (alternatively: `$ ./build/bin/beetchef`)
