#ifndef Magnum_Implementation_TextureState_h
#define Magnum_Implementation_TextureState_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <string>
#include <vector>

#include "Magnum/Magnum.h"
#include "Magnum/OpenGL.h"

namespace Magnum { namespace Implementation {

struct TextureState {
    explicit TextureState(Context& context, std::vector<std::string>& extensions);
    ~TextureState();

    void reset();

    void(*unbindImplementation)(GLint);
    void(*bindMultiImplementation)(GLint, Containers::ArrayReference<AbstractTexture* const>);
    void(AbstractTexture::*createImplementation)();
    void(AbstractTexture::*bindImplementation)(GLint);
    void(AbstractTexture::*parameteriImplementation)(GLenum, GLint);
    void(AbstractTexture::*parameterfImplementation)(GLenum, GLfloat);
    #ifndef MAGNUM_TARGET_GLES2
    void(AbstractTexture::*parameterivImplementation)(GLenum, const GLint*);
    #endif
    void(AbstractTexture::*parameterfvImplementation)(GLenum, const GLfloat*);
    #ifndef MAGNUM_TARGET_GLES
    void(AbstractTexture::*parameterIuivImplementation)(GLenum, const GLuint*);
    void(AbstractTexture::*parameterIivImplementation)(GLenum, const GLint*);
    #endif
    void(AbstractTexture::*setMaxAnisotropyImplementation)(GLfloat);
    #ifndef MAGNUM_TARGET_GLES2
    void(AbstractTexture::*getLevelParameterivImplementation)(GLenum, GLint, GLenum, GLint*);
    #endif
    void(AbstractTexture::*mipmapImplementation)();
    #ifndef MAGNUM_TARGET_GLES
    void(AbstractTexture::*storage1DImplementation)(GLenum, GLsizei, TextureFormat, const Math::Vector<1, GLsizei>&);
    #endif
    void(AbstractTexture::*storage2DImplementation)(GLenum, GLsizei, TextureFormat, const Vector2i&);
    void(AbstractTexture::*storage3DImplementation)(GLenum, GLsizei, TextureFormat, const Vector3i&);
    #ifndef MAGNUM_TARGET_GLES2
    void(AbstractTexture::*storage2DMultisampleImplementation)(GLenum, GLsizei, TextureFormat, const Vector2i&, GLboolean);
    #endif
    #ifndef MAGNUM_TARGET_GLES
    void(AbstractTexture::*storage3DMultisampleImplementation)(GLenum, GLsizei, TextureFormat, const Vector3i&, GLboolean);
    void(AbstractTexture::*getImageImplementation)(GLenum, GLint, ColorFormat, ColorType, std::size_t, GLvoid*);
    void(AbstractTexture::*image1DImplementation)(GLenum, GLint, TextureFormat, const Math::Vector<1, GLsizei>&, ColorFormat, ColorType, const GLvoid*);
    #endif
    void(AbstractTexture::*image2DImplementation)(GLenum, GLint, TextureFormat, const Vector2i&, ColorFormat, ColorType, const GLvoid*);
    void(AbstractTexture::*image3DImplementation)(GLenum, GLint, TextureFormat, const Vector3i&, ColorFormat, ColorType, const GLvoid*);
    #ifndef MAGNUM_TARGET_GLES
    void(AbstractTexture::*subImage1DImplementation)(GLenum, GLint, const Math::Vector<1, GLint>&, const Math::Vector<1, GLsizei>&, ColorFormat, ColorType, const GLvoid*);
    #endif
    void(AbstractTexture::*subImage2DImplementation)(GLenum, GLint, const Vector2i&, const Vector2i&, ColorFormat, ColorType, const GLvoid*);
    void(AbstractTexture::*subImage3DImplementation)(GLenum, GLint, const Vector3i&, const Vector3i&, ColorFormat, ColorType, const GLvoid*);
    void(AbstractTexture::*invalidateImageImplementation)(GLint);
    void(AbstractTexture::*invalidateSubImageImplementation)(GLint, const Vector3i&, const Vector3i&);

    #ifndef MAGNUM_TARGET_GLES
    void(BufferTexture::*setBufferImplementation)(BufferTextureFormat, Buffer&);
    void(BufferTexture::*setBufferRangeImplementation)(BufferTextureFormat, Buffer&, GLintptr, GLsizeiptr);
    #endif

    GLint maxSize,
        max3DSize,
        maxCubeMapSize;
    #ifndef MAGNUM_TARGET_GLES2
    GLint maxArrayLayers;
    #endif
    #ifndef MAGNUM_TARGET_GLES
    GLint maxRectangleSize,
        maxBufferSize;
    #endif
    GLint maxTextureUnits;
    #ifndef MAGNUM_TARGET_GLES2
    GLfloat maxLodBias;
    #endif
    GLfloat maxMaxAnisotropy;
    GLint currentTextureUnit;
    #ifndef MAGNUM_TARGET_GLES2
    GLint maxColorSamples,
        maxDepthSamples,
        maxIntegerSamples;
    #endif
    #ifndef MAGNUM_TARGET_GLES
    GLint bufferOffsetAlignment;
    #endif

    std::vector<std::pair<GLenum, GLuint>> bindings;
};

}}

#endif
