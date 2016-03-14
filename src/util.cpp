#include "util.hpp"

#include <fstream>
#include <cerrno>

#include <glm/gtc/matrix_access.hpp>

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
    
    void printMat4(const glm::mat4& matrix) {
        for (int i = 0; i < 4; ++i) {
            auto row = glm::row(matrix, i);
            for (int j = 0; j < 4; ++j) {
                std::cout << row[j] << " ";
            }
            std::cout << std::endl;
        }
    }
}
