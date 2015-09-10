# Locality-Sensitive Binary Codes from Shift-Invariant Kernels
Implement [Locality-Sensitive Binary Codes from Shift-Invariant Kernels NIPS(2009)](http://www.robots.ox.ac.uk/~vgg/rg/papers/binarycodes.pdf)  
Here is two versions of the implementation (Java and C++)  
Any questions is welcomed.    

### Java
#### Usage
This is a eclipse maven project, you can import it from eclipse menu:
File -> Import... -> Maven -> Existing Maven Projects -> Next  

----
Look junit test in /src/test/java/pers/yy/algorithm/lsh/KernelLshTest.java for example  
High \sigma means little difference in raw feature will produce a different bit hash

### C++
#### Usage
make  
run main  
High \sigma means little difference in raw features will produce a different bit hash
### Annotation
 - C++ code used scoped_ptr and scoped_array in base dir.
It is copied from [gjstest](https://github.com/google/gjstest/tree/master/base).  
You can use boost or write it yourself instead.
 - Used libsvm like features in C++ implementation.
 - Used org.apache.mahout.math.SequentialAccessSparseVector in Java implementation.
