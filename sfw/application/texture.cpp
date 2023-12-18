#include "texture.h"

#include <stdio.h>

void Texture::load_image(const char * file_name, const int format, const int internal_components) {
    if (image) {
        SDL_FreeSurface(image);
        image = NULL;
        glDeleteTextures(1, &texture);
    }

    SDL_Surface *img = SDL_LoadBMP(file_name);

    if (!img) {
        printf("Couldn't load %s.\n", file_name);
    } else {
        image = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA32, 0);
        SDL_FreeSurface(img);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, internal_components, GL_UNSIGNED_BYTE, image->pixels);
        apply_filter();
    }
}

void Texture::apply_filter() {
    GLint params = GL_NEAREST;

    if (filter == TEXTURE_FILTER_LINEAR) {
        params = GL_LINEAR;
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params);
}

Texture::Texture() {
    filter = TEXTURE_FILTER_NEAREST;
    texture = 0;
    image = NULL;
}

Texture::~Texture() {
    if (image) {
        SDL_FreeSurface(image);

        glDeleteTextures(1, &texture);
    }
}
