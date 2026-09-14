cmake_minimum_required(VERSION 3.10)
project(Ember)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ember
    main.cpp
    Lexer.cpp
    SyntaxToken.h
    Lexer.h
)