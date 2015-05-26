#pragma once

#include <fstream>

class Log
{
    std::fstream fs_;
public:
    Log(const std::string &file) { open(file); }
    Log();
    ~Log();

    inline void open(const std::string& file) { open(file, std::fstream::out); }
    inline void open(const std::string& file, int mode) { fs_.open(file, mode); }
    inline void close() { fs_.close(); }
    inline std::fstream& fstream() { return fs_; }
    
};

