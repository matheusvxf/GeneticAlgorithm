#pragma once

#include <fstream>

class Log
{
    std::fstream fs_;
public:
    Log(const std::string &file) { open(file); }
    Log();
    ~Log();

    void open(const std::string& file) { fs_.open(file, std::fstream::out); }
    void close() { fs_.close(); }
    std::fstream& fstream() { return fs_; }
    
};

