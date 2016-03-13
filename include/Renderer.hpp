//
//  Renderer.hpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

class Renderer {
    
public:
    virtual void init() = 0;
    virtual void draw() = 0;
};

#endif /* Renderer_hpp */
