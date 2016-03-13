//
//  util.hpp
//  Glitter
//
//  Created by André Sá de Mello on 3/9/16.
//
//

#ifndef util_hpp
#define util_hpp

#include <string>

namespace util {
    std::string loadFromFile(const std::string& filename);
    char *createCString(const std::string& str);
}

#endif /* util_hpp */
