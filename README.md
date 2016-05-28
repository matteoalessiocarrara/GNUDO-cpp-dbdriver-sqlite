# How to build
We use CMake, then

 * create an external build directory
 ~~~
 mkdir -v ../gnudo-build
 ~~~

 * go into the directory, then
 ~~~
 cmake ../GNUDO-backend-cpp
 ~~~

 * run make
 ~~~
 make 
 ~~~

 * You will find binary in src/bin


 How to use debug build (with definition and symbols)?
 *-DCMAKE_BUILD_TYPE="Debug"*

 if not specified, CMAKE_BUILD_TYPE equals to "Release"
 
 for both debug and release types binary is outputted to src/bin

