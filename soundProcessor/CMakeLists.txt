cmake_minimum_required(VERSION 4.0)
project(soundProcessor)

set(CMAKE_CXX_STANDARD 20)

add_executable(soundProcessor main.cpp
        src/WAV.cpp
        src/WAV.h
        src/Sound.h
        src/Factory.h
        src/Converters.cpp
        src/Converters.h
        src/CMDParser.cpp
        src/CMDParser.h
        src/CFGParser.cpp
        src/CFGParser.h
        src/SNDProcessor.cpp
        src/SNDProcessor.h
)
