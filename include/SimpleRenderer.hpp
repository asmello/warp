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

class SimpleRenderer : public Renderer {
private:
    std::vector<std::shared_ptr<Mesh>> objects;
    std::chrono::time_point<std::chrono::high_resolution_clock> t_last;
    double t_total;
    
public:
    SimpleRenderer(const std::vector<std::shared_ptr<Mesh>>& objects);
    void init();
    void draw();
};

#endif /* SimpleRenderer_hpp */
