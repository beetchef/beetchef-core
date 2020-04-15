# beetchef-core

### prerequisites

1. `$ apt install g++ cmake jackd2 libjack-jackd2-dev`
2. install [spdlog](https://github.com/gabime/spdlog) library: 
    - `$ git clone https://github.com/gabime/spdlog.git`
    - `$ cd spdlog`
    - `$ cmake -S . -B build`
    - `$ cmake --build build --target install`

### build

1. `$ git clone https://github.com/beetchef/beetchef-core.git`
2. `$ cd beetchef-core`
3. `$ cmake -S . -B build`
4. `$ cmake --build build` (this step is sufficient for rebuilding after it's

    (this generates executable `beetchef` in `./build/bin/`)

### test

1. `$ cmake --build build --target test`

### execution

1. `$ <<beetchef-core-root-dir>>/build/bin/beetchef`
