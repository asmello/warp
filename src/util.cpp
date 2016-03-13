#include "util.hpp"

#include <fstream>
#include <cerrno>

namespace util {
    std::string loadFromFile(const std::string& filename) {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (!in) {
            perror(filename.c_str());
            return "";
        }
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    
    char *createCString(const std::string& str) {
        char *cstr = new char[str.length()+1];
        std::strcpy(cstr, str.c_str());
        return cstr;
    }
}
