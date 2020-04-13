# beetchef-core

### prerequisites

1. `$ apt install g++`
2. `$ apt install make`
3. `$ apt install cmake`
4. `$ apt install libjack-dev`
5. install [spdlog](https://github.com/gabime/spdlog) library: 
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

### execution

1. `$ <<beetchef-core-root-dir>>/build/bin/beetchef`
