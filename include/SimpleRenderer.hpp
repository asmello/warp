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
#include "Mesh.hpp"

#include <GL/glew.h>

#include <vector>
#include <chrono>

class SimpleRenderer : Renderer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    GLint uniColor;
    GLint uniTrans;
    std::vector<std::shared_ptr<Mesh>> objects;
    
public:
    void init(const std::vector<std::shared_ptr<Mesh>>& objects);
    void draw();
};

#endif /* SimpleRenderer_hpp */
