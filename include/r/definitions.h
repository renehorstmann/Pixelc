#ifndef R_DEFINITIONS_H
#define R_DEFINITIONS_H

// will be appended on the top of a shader
#ifdef USING_GLES
#define R_VERTEX_BEGIN "#version 300 es\n"
#define R_FRAGMENT_BEGIN "#version 300 es\nprecision mediump float;\n"
#else
#define R_VERTEX_BEGIN "#version 330 core\n"
#define R_FRAGMENT_BEGIN "#version 330 core\n"
#endif


#endif //R_DEFINITIONS_H
