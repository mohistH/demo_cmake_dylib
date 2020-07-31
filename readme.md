
## 1、introduce
this is a demo of using cmake to make dylib, including static and dynamic library 


## 2、CMakeLists.txt
```


cmake_minimum_required(VERSION 3.1)

#项目名
project(libhello)

# 1、指定库的目录变量
set(libhello_src src/hello.cxx)
# 指定头文件搜索路径
include_directories("${PROJECT_SOURCE_DIR}/include")



# 2、添加库(对应的两个项目)
add_library( hello_shared SHARED ${libhello_src})
add_library( hello_static STATIC ${libhello_src})
#  按照一般的习惯，静态库名字跟动态库名字应该是一致的，只是扩展名不同；
# 即：静态库名为 libhello.a； 动态库名为libhello.so ；
# 所以，希望 "hello_static" 在输出时，不是"hello_static"，而是以"hello"的名字显示，故设置如下
# SET_TARGET_PROPERTIES (hello_static PROPERTIES OUTPUT_NAME "hello")




# 3、cmake在构建一个新的target时，会尝试清理掉其他使用这个名字的库，
# 因此，在构建libhello.a时，就会清理掉libhello.so.
# 为了回避这个问题，比如再次使用SET_TARGET_PROPERTIES定义 CLEAN_DIRECT_OUTPUT属性。
SET_TARGET_PROPERTIES (hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (hello_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)




# 4、按照规则，动态库是应该包含一个版本号的，
# VERSION指代动态库版本，SOVERSION指代API版本。
SET_TARGET_PROPERTIES (hello_static PROPERTIES VERSION 1.1 SOVERSION 1)
SET_TARGET_PROPERTIES (hello_shared PROPERTIES VERSION 1.1 SOVERSION 1)




# 5、若将libhello.a, libhello.so.x以及hello.h安装到系统目录，才能真正让其他人开发使用，
# 本例中，将hello的共享库安装到<prefix>/lib目录；
# 将hello.h安装<prefix>/include/hello目录。
#INSTALL (TARGETS hello hello_shared LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
#INSTALL (TARGETS hello hello_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
#INSTALL (FILES hello.h DESTINATION include/hello)


```



## 3、the tree of this demo
```

│  CMakeLists.txt
│  index.txt
│  
├─build
├─include
│      hello.h
│      hi.h
│      
└─src
        hello.cxx
        hi.cxx

```

## 4、command
use the following command to configure and generate:
'''
cd xx/to/path
cd build
cmake ..

