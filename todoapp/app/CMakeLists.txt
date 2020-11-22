# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("devicecontrol")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 라이브러리 추가
add_library(7segment SHARED src/main/cpp/7segment.c)
add_library(dotmatrix SHARED src/main/cpp/dotmatrix.c)
add_library(lcd SHARED src/main/cpp/lcd.c)
add_library(led SHARED src/main/cpp/led.c)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 타겟 라이브러리 연결
target_link_libraries(7segment ${log-lib} )
target_link_libraries(dotmatrix ${log-lib} )
target_link_libraries(lcd ${log-lib} )
target_link_libraries(led ${log-lib} )
