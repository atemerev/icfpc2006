# ICFPC'2006 UM in C++

This is my exercise in C++. No guarantees at all. This is a "naive" implementation,
no JIT, no branch prediction, no quantum acceleration, no nothing.

## How to build

```shell script
mkdir build
cd build
cmake ..
make
```

(or `cmake -DCMAKE_BUILD_TYPE=Release ..` for some extra speed).

## How to run

Download `codex.umz` and/or `sandmark.umz` from http://boundvariable.org/task.shtml.

From the `build` directory:

```shell script
./boundvar /path/to/sandmark.umz
```

(Or `codex.umz` for the actual task.)

Happy hacking!




