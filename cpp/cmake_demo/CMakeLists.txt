PROJECT (HELLO) #  指定了工程的名字，并且支持所有语言

SET(SRC_LIST main.cpp) # SET关键字用来显示指定的变量  SET(SRC_LIST main.cpp t1.cpp t2.cpp)
# MESSAGE 关键字主要用于向终端输出用户自定义的信息
# SEND_ERROR，产生错误，生成过程被跳过  STATUS，输出前缀为–的信息  FATAL_ERROR，立即终止所有cmake过程
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})

MESSAGE(STATUS "This is SOURCE dir "${HELLO_SOURCE_DIR})
# ADD_EXECUTABLE关键字用于生成可执行文件
ADD_EXECUTABLE(hello ${SRC_LIST})
