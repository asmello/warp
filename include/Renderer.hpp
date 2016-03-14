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
