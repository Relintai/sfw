#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

class Texture {
public:
    enum TextureFilter {
        TEXTURE_FILTER_NEAREST = 0,
        TEXTURE_FILTER_LINEAR,
    };

    void load_image(const char * file_name, const int format = GL_RGBA, const int internal_components = GL_RGBA);
    void apply_filter();

    TextureFilter filter;
    GLuint texture;
    SDL_Surface *image;

    Texture();
    virtual ~Texture();
};

#endif // TEXTURE_H
