# Simple Args
A tiny simple command line arguments parser for c++.

```
./SimpleArgs --help
  --verbosity            Show verbose developer information
   0 = only print helpoutput
   1 = both print help and paraments
  Default = 1.
  --log                  A string/Path variable for testing
  --f_value              A float value for testing
  --if_flag              A bool value for testing
verbosity                     : 1
log                           : /tmp/log.txt
f_value                       : 1.000000
if_flag                       : 1
```

```
./SimpleArgs --verbosity 1 --log /path/to/log.txt --f_value 3.1415 --if_flag false

 verbosity                     : 1
 log                           : /path/to/log.txt
 f_value                       : 3.141500
 if_flag                       : 0
```

## Build
```
git clone git@github.com:hova88/SimpleArgs.git && cd SimpleArgs
mkdir build && cd build
cmake .. && make
./SimpleArgs --help
```

## Reference
- Copy from [**gemma.cpp/utils/args.h**](https://github.com/google/gemma.cpp/blob/main/util/args.h)
