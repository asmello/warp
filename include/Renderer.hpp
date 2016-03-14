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
protected:
    bool paused;
    
public:
    Renderer() : paused(false) { }
    virtual void draw() = 0;
    void pause() { paused = !paused; };
    bool isPaused() const { return paused; };
};

#endif /* Renderer_hpp */
