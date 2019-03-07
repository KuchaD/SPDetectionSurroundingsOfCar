

cmake_minimum_required(VERSION 3.12)
# Every project needs a name.  We call this the "examples" project.
project(PROJEKT)



# Tell cmake we will need dlib.  This command will pull in dlib and compile it
# into your project.  Note that you don't need to compile or install dlib.  All
# cmake needs is the dlib source code folder and it will take care of everything.
add_subdirectory(../../dlib dlib_build)


# The next thing we need to do is tell CMake about the code you want to
# compile.  We do this with the add_executable() statement which takes the name
# of the output executable and then a list of .cpp files to compile.  Here we
# are going to compile one of the dlib example programs which has only one .cpp
# file, assignment_learning_ex.cpp.  If your program consisted of multiple .cpp
# files you would simply list them here in the add_executable() statement.


add_executable(assignment_learning_ex main.cpp src/Network.cpp src/Network.h utils/Utils.h utils/Utils.cpp)
# Finally, you need to tell CMake that this program, assignment_learning_ex,
# depends on dlib.  You do that with this statement:
target_link_libraries(assignment_learning_ex dlib::dlib)

