This file contains a brief explanation about the extra
files you may encounter during the coursework.

.VecsAndMats.cpp -> functions necessary for working with vectors.
.VecsAndMats.hpp -> Its corresponding header file.

# Note on .cpp and .hpp files:

.cpp files: contain the actual code of the functions.
.hpp files: 
	Contain the headers of the functions of the .cpp files,
	along with a brief explanation of what each function does and 
	how to use them.
	By looking at this files you can get an idea of the functions
	contained in the .cpp and what they do, without looking at the code.

*Note: I include the headers so I can use the functions in the
.cpp without compiling the .cpp.
Therefore, I include all .cpp files in the Driver so they are compiled,
and then just include the header files on the dependencies so I can use
the functions contained in them without explicitly declaring the prototype,
nor compiling multiple times.






