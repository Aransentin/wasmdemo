#pragma once

#define GL_TRIANGLES 0x0004
#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_DEPTH 0x1801
#define GL_COLOR 0x1800
#define GL_TRIANGLES 0x0004
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_LINK_STATUS 0x8B82
#define GL_COMPILE_STATUS 0x8B81
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_FLOAT 0x1406
#define GL_CULL_FACE 0x0B44
#define GL_BLEND 0x0BE2
#define GL_DEPTH_TEST 0x0B71
#define GL_FRONT 0x0404
#define GL_BACK 0x0405
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE0 0x84C0
#define GL_RGB8 0x8051
#define GL_RGBA8 0x8058
#define GL_SRGB8 0x8C41
#define GL_SRGB8_ALPHA8 0x8C43
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_SRGB 0x8C40
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_LINEAR 0x2601
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE

void glActiveTexture( i32 slot );
void glAttachShader( i32 shader, i32 program );
void glBindBuffer( i32 target, i32 buffer );
void glBindFramebuffer( void );
void glBindSampler( void );
void glBindTexture( i32 type, i32 texture );
void glBindVertexArray( i32 vao );
void glBlendColor( void );
void glBlendEquationSeparate( void );
void glBlendFuncSeparate( void );
void glBufferData( i32 target, const void * data, i32 usage, i32 length );
void glClearBuffer( i32 buffer, i32 drawbuffer, f32 r, f32 g, f32 b, f32 a );
void glColorMask( void );
void glCompileShader( i32 shader );
i32 glCreateBuffer( void );
void glCreateFramebuffer( void );
i32 glCreateProgram( void );
void glCreateSampler( void );
i32 glCreateShader( i32 type );
i32 glCreateTexture( void );
i32 glCreateVertexArray( void );
void glCullFace( i32 mode );
void glDeleteBuffer( i32 BO );
void glDeleteFramebuffer( void );
void glDeleteProgram( i32 program );
void glDeleteSampler( void );
void glDeleteShader( i32 shader );
void glDeleteTexture( void );
void glDeleteVertexArray( i32 VAO );
void glDepthFunc( void );
void glDepthMask( void );
void glDetachShader( i32 program, i32 shader );
void glDisable( i32 cap );
void glDrawArrays( void );
void glDrawBuffer( void );
void glDrawElements( i32 mode, i32 count, i32 type, i32 offset );
void glEnable( i32 cap );
void glEnableVertexAttribArray( i32 index );
void glFramebufferParameteri( void );
void glFramebufferTexture( void );
void glFrontFace( void );
void glGenBuffer( void );
void glGenFramebuffer( void );
void glGenSampler( void );
void glGet( void );
void glGenerateMipmap( i32 target );
void glGetProgramInfoLog( void );
i32 glGetProgramParameter( i32 program, i32 param );
void glGetShaderInfoLog( void );
i32 glGetShaderParameter( i32 program, i32 param );
i32 glGetUniformLocation( i32 program, const char name[static 1], i32 name_len );
void glGetString( void );
void glLinkProgram( i32 program );
void glLogicOp( void );
void glShaderSource( i32 shader, const char source[static 1], i32 source_len );
void glTexParameterf( i32 target, i32 pname, f32 value );
void glTexParameteri( i32 target, i32 pname, i32 value );
void glTexStorage2D( i32 target, i32 levels, i32 internalformat, i32 width, i32 height );
void glTexSubImage2D( i32 target, i32 level, i32 xoff, i32 yoff, i32 width, i32 height, i32 format, i32 type, u8 data[static 1], i32 len );
void glUniform1i( i32 location, i32 value );
void glUniform3fv( i32 location, f32 x, f32 y, f32 z );
void glUniformMatrix4fv( i32 location, const f32 data[static 16] );
void glUseProgram( i32 program );
void glVertexAttribPointer( i32 index, i32 size, i32 type, i32 normalized, i32 stride, i32 offset );
void glViewport( i32 x, i32 y, i32 w, i32 h );

void glutil_printShaderInfoLog( i32 shader );
void glutil_printProgramInfoLog( i32 shader );
