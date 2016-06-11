#include "Texture.hpp"
#include "TextureManager.hpp"

#include "ShaderManager.hpp"
#include "Shader.hpp"

#include <SOIL2.h>
#include <cassert>

using namespace warp;

template<> ResourceManager<Texture> * Object<Texture>::manager = TextureManager::getInstance();

Texture::Texture(GLenum tg) : target(tg), loaded(false)
{
    
}

void Texture::load2D(const std::string& path)
{
    assert(target == GL_TEXTURE_2D);
    
    int width, height;
    unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    glGenTextures(1, &txo);
    glBindTexture(GL_TEXTURE_2D, txo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    
    loaded = true;
}

void Texture::loadCubemap(const std::string &path)
{
    txo = SOIL_load_OGL_single_cubemap(path.c_str(), "EWUDNS", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    loaded = true;
}

void Texture::loadCubemapFromMultiple(const std::vector<std::string>& path)
{
    assert(target == GL_TEXTURE_CUBE_MAP);
    assert(path.size()==6);
    
    glGenTextures(1, &txo);
    glBindTexture(GL_TEXTURE_CUBE_MAP, txo);
    
    int width, height;
    unsigned char *image;
    for (int i = 0; i < 6; ++i)
    {
        image = SOIL_load_image(path[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
        if (image == NULL)
        {
            fprintf(stderr, "WARN: Failed to load cubemap face %d from \"%s\"\n", i, path[i].c_str());
            break;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    loaded = true;
}

Texture::~Texture()
{
    if (loaded) glDeleteTextures(1, &txo);
}