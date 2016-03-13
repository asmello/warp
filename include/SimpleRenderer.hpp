//
//  SimpleRenderer.hpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#ifndef SimpleRenderer_hpp
#define SimpleRenderer_hpp

#include "Renderer.hpp"

#include <GL/glew.h>

#include <chrono>

class SimpleRenderer : Renderer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    GLint uniColor;
    
public:
    void init();
    void draw();
};

#endif /* SimpleRenderer_hpp */
