cmake_minimum_required(VERSION 2.8)

set(GEN_PRO_NAME "typerANDviewer")
project(${GEN_PRO_NAME})

add_executable(typer "typer.cpp")
add_executable(viewer "viewer.cpp")
