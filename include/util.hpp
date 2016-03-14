#ifndef util_hpp
#define util_hpp

#include <iostream>
#include <string>

#include <glm/glm.hpp>

namespace util {
    std::string loadFromFile(const std::string& filename);
    char *createCString(const std::string& str);
    void printMat4(const glm::mat4& matrix);
    std::string resourcePath(void);
}

#endif /* util_hpp */
