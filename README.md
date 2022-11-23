# numeric
Numeric library for the numeric calculations course. I'll try to add new features and keep this thing up-to-date with the course.

# Usage
Windows support is at test.

The easiest way to use the library is to get the shared library and include files from [here](https://github.com/theAester/numeric/releases/tag/v1.0) and place them next to your C code and use 
``` sh
gcc filename numeric.so
```

You can also compile using the provided Makefile to handle projects. Simply place the your C source code(lets call this mycode.c) in the root of the repository and use 
``` sh
make NAME=mycode
```
You may also use 
``` sh
make lib
```
to only generate the numeric.so file. See the content of the Makefile for more details.

## contribution
Email me at hiradcodes@yahoo.com to contribute!
