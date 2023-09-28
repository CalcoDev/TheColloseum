## CUSTOM MADE BY CALCOPOD
## BAD LMAO
cmake_minimum_required(VERSION 3.20)
project(tomlc99)

add_library(tomlc99 "include/tomlc99/toml.h" "src/toml.c")
target_include_directories(tomlc99 PUBLIC "include/")