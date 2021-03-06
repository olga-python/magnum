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

#include <Corrade/TestSuite/Compare/Container.h>

#include "Magnum/MultisampleTexture.h"
#include "Magnum/TextureFormat.h"
#include "Magnum/Math/Vector3.h"
#include "Magnum/Test/AbstractOpenGLTester.h"

namespace Magnum { namespace Test {

class MultisampleTextureGLTest: public AbstractOpenGLTester {
    public:
        explicit MultisampleTextureGLTest();

        void construct2D();
        #ifndef MAGNUM_TARGET_GLES
        void construct2DArray();
        #endif

        void bind2D();
        #ifndef MAGNUM_TARGET_GLES
        void bind2DArray();
        #endif

        void storage2D();
        #ifndef MAGNUM_TARGET_GLES
        void storage2DArray();
        #endif

        void invalidateImage2D();
        #ifndef MAGNUM_TARGET_GLES
        void invalidateImage2DArray();
        #endif

        void invalidateSubImage2D();
        #ifndef MAGNUM_TARGET_GLES
        void invalidateSubImage2DArray();
        #endif
};

MultisampleTextureGLTest::MultisampleTextureGLTest() {
    addTests({&MultisampleTextureGLTest::construct2D,
              #ifndef MAGNUM_TARGET_GLES
              &MultisampleTextureGLTest::construct2DArray,
              #endif

              &MultisampleTextureGLTest::bind2D,
              #ifndef MAGNUM_TARGET_GLES
              &MultisampleTextureGLTest::bind2DArray,
              #endif

              &MultisampleTextureGLTest::storage2D,
              #ifndef MAGNUM_TARGET_GLES
              &MultisampleTextureGLTest::storage2DArray,
              #endif

              &MultisampleTextureGLTest::invalidateImage2D,
              #ifndef MAGNUM_TARGET_GLES
              &MultisampleTextureGLTest::invalidateImage2DArray,
              #endif

              &MultisampleTextureGLTest::invalidateSubImage2D,
              #ifndef MAGNUM_TARGET_GLES
              &MultisampleTextureGLTest::invalidateSubImage2DArray
              #endif
              });
}

void MultisampleTextureGLTest::construct2D() {
    #ifndef MAGNUM_TARGET_GLES
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));
    #else
    if(!Context::current()->isVersionSupported(Version::GLES310))
        CORRADE_SKIP("OpenGL ES 3.1 is not supported.");
    #endif

    {
        MultisampleTexture2D texture;

        MAGNUM_VERIFY_NO_ERROR();
        CORRADE_VERIFY(texture.id() > 0);
    }

    MAGNUM_VERIFY_NO_ERROR();
}

#ifndef MAGNUM_TARGET_GLES
void MultisampleTextureGLTest::construct2DArray() {
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));

    {
        MultisampleTexture2DArray texture;

        MAGNUM_VERIFY_NO_ERROR();
        CORRADE_VERIFY(texture.id() > 0);
    }

    MAGNUM_VERIFY_NO_ERROR();
}
#endif

void MultisampleTextureGLTest::bind2D() {
    #ifndef MAGNUM_TARGET_GLES
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));
    #else
    if(!Context::current()->isVersionSupported(Version::GLES310))
        CORRADE_SKIP("OpenGL ES 3.1 is not supported.");
    #endif

    MultisampleTexture2D texture;
    texture.bind(15);

    MAGNUM_VERIFY_NO_ERROR();

    AbstractTexture::unbind(15);

    MAGNUM_VERIFY_NO_ERROR();

    AbstractTexture::bind(7, {&texture, nullptr, &texture});

    MAGNUM_VERIFY_NO_ERROR();

    AbstractTexture::unbind(7, 3);

    MAGNUM_VERIFY_NO_ERROR();
}

#ifndef MAGNUM_TARGET_GLES
void MultisampleTextureGLTest::bind2DArray() {
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));

    MultisampleTexture2DArray texture;
    texture.bind(15);

    MAGNUM_VERIFY_NO_ERROR();

    AbstractTexture::unbind(15);

    MAGNUM_VERIFY_NO_ERROR();

    AbstractTexture::bind(7, {&texture, nullptr, &texture});

    MAGNUM_VERIFY_NO_ERROR();

    AbstractTexture::unbind(7, 3);

    MAGNUM_VERIFY_NO_ERROR();
}
#endif

void MultisampleTextureGLTest::storage2D() {
    #ifndef MAGNUM_TARGET_GLES
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));
    #else
    if(!Context::current()->isVersionSupported(Version::GLES310))
        CORRADE_SKIP("OpenGL ES 3.1 is not supported.");
    #endif

    MultisampleTexture2D texture;
    texture.setStorage(4, TextureFormat::RGBA8, {16, 16});

    MAGNUM_VERIFY_NO_ERROR();

    CORRADE_COMPARE(texture.imageSize(), Vector2i(16, 16));

    MAGNUM_VERIFY_NO_ERROR();
}

#ifndef MAGNUM_TARGET_GLES
void MultisampleTextureGLTest::storage2DArray() {
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));

    MultisampleTexture2DArray texture;
    texture.setStorage(4, TextureFormat::RGBA8, {16, 16, 5});

    MAGNUM_VERIFY_NO_ERROR();

    CORRADE_COMPARE(texture.imageSize(), Vector3i(16, 16, 5));

    MAGNUM_VERIFY_NO_ERROR();
}
#endif

void MultisampleTextureGLTest::invalidateImage2D() {
    #ifndef MAGNUM_TARGET_GLES
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));
    #else
    if(!Context::current()->isVersionSupported(Version::GLES310))
        CORRADE_SKIP("OpenGL ES 3.1 is not supported.");
    #endif

    MultisampleTexture2D texture;
    texture.setStorage(4, TextureFormat::RGBA8, {16, 16});
    texture.invalidateImage();

    MAGNUM_VERIFY_NO_ERROR();
}

#ifndef MAGNUM_TARGET_GLES
void MultisampleTextureGLTest::invalidateImage2DArray() {
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));

    MultisampleTexture2DArray texture;
    texture.setStorage(4, TextureFormat::RGBA8, {16, 16, 5});
    texture.invalidateImage();

    MAGNUM_VERIFY_NO_ERROR();
}
#endif

void MultisampleTextureGLTest::invalidateSubImage2D() {
    #ifndef MAGNUM_TARGET_GLES
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));
    #else
    if(!Context::current()->isVersionSupported(Version::GLES310))
        CORRADE_SKIP("OpenGL ES 3.1 is not supported.");
    #endif

    MultisampleTexture2D texture;
    texture.setStorage(4, TextureFormat::RGBA8, {16, 16});
    texture.invalidateSubImage({3, 4}, {5, 6});

    MAGNUM_VERIFY_NO_ERROR();
}

#ifndef MAGNUM_TARGET_GLES
void MultisampleTextureGLTest::invalidateSubImage2DArray() {
    if(!Context::current()->isExtensionSupported<Extensions::GL::ARB::texture_multisample>())
        CORRADE_SKIP(Extensions::GL::ARB::texture_multisample::string() + std::string(" is not supported."));

    MultisampleTexture2DArray texture;
    texture.setStorage(4, TextureFormat::RGBA8, {16, 16, 5});
    texture.invalidateSubImage({3, 4, 1}, {5, 6, 3});

    MAGNUM_VERIFY_NO_ERROR();
}
#endif

}}

CORRADE_TEST_MAIN(Magnum::Test::MultisampleTextureGLTest)
