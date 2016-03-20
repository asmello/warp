#include "Texture.hpp"
using namespace warp;

#include <SOIL2.h>

Texture::Texture(GLenum tg) : target(tg), initialized(false), loaded(false)
{
    
}

void Texture::init(const std::shared_ptr<const warp::Shader> shader)
{
    if (initialized) return;
    uniSampler = shader->getUniformLocation("u_sampler");
    glUniform1i(uniSampler, 0);
    initialized = true;
}

void Texture::loadFromFile(const std::string &path)
{
    int width, height;
    unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    
    glGenTextures(1, &txo);
    glBindTexture(target, txo);
    glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(target, 0);
    
    SOIL_free_image_data(image);
    
    loaded = true;
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(target, txo);
}

Texture::~Texture()
{
    if (loaded) glDeleteTextures(1, &txo);
}