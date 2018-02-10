#include "model.h"
#include "glstate.h"
#include "shader.h"
#include "util.h"
#include "webgl.h"

typedef struct
{
    float x, y, z;
    i16 u, v;
    i8 nx, ny, nz, np;
    i8 tx, ty, tz, tp;
} Vertex;

// magic hardcoded values, oh yeah
#define INDICES_N 6075
#define VERTICES_N 1363
#define MODEL_ID 1
#define DIFFUSE_ID 2
#define NORMAL_ID 3

bool model_init( Model model[static 1] )
{
    u8 scratch[512 * 512 * 4];
    if( !util_buffer_get( MODEL_ID, scratch ) )
        return false;

    if( !model->VAO )
        model->VAO = glCreateVertexArray();

    glBindVertexArray( model->VAO );
    i32 VBO = glCreateBuffer();
    i32 IBO = glCreateBuffer();
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );

    // Technically UB but whatever 😎
    u16 * indices = (void *)&scratch[0];
    Vertex * vertices = (void *)&scratch[sizeof( u16 ) * INDICES_N];

    model->indices_n = INDICES_N;

    glBufferData( GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW, ( i32 )( sizeof( Vertex ) * VERTICES_N ) );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW, ( i32 )( sizeof( u16 ) * INDICES_N ) );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    glEnableVertexAttribArray( 3 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, false, sizeof( Vertex ), 0 );
    glVertexAttribPointer( 1, 2, GL_UNSIGNED_SHORT, true, sizeof( Vertex ), 12 );
    glVertexAttribPointer( 2, 3, GL_BYTE, true, sizeof( Vertex ), 16 );
    glVertexAttribPointer( 3, 3, GL_BYTE, true, sizeof( Vertex ), 20 );

    glBindVertexArray( 0 );
    glDeleteBuffer( VBO );
    glDeleteBuffer( IBO );

    let diffuse = glCreateTexture();
    let normal = glCreateTexture();

    util_buffer_get( DIFFUSE_ID, scratch );

    // Bah, bugs
    /*for( u32 i = 0; i < 512 * 512; i++ )
    {
        scratch[i * 4 + 0] = (i%8)*32;
        scratch[i * 4 + 1] = i;
        scratch[i * 4 + 2] = i;
    }*/

    glBindTexture( GL_TEXTURE_2D, diffuse );
    glTexStorage2D( GL_TEXTURE_2D, 10, GL_SRGB8_ALPHA8, 512, 512 );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 512, 512, GL_RGBA, GL_UNSIGNED_BYTE, scratch, 512 * 512 * 4 );
    glGenerateMipmap( GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0 );

    util_buffer_get( NORMAL_ID, scratch );
    for( u32 i = 0; i < 512 * 512; i++ )
    {
        scratch[i * 3 + 0] = scratch[i * 4 + 0];
        scratch[i * 3 + 1] = scratch[i * 4 + 1];
        scratch[i * 3 + 2] = scratch[i * 4 + 2];
    }

    glBindTexture( GL_TEXTURE_2D, normal );
    glTexStorage2D( GL_TEXTURE_2D, 10, GL_RGB8, 512, 512 );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, scratch, 512 * 512 * 3 );
    glGenerateMipmap( GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0 );

    model->diffuse = diffuse;
    model->normal = normal;
    return true;
}

void model_destroy( Model model[static 1] )
{
    if( model->VAO )
    {
        glDeleteVertexArray( model->VAO );
    }
    *model = ( Model ){.VAO = 0};
}

void model_render( Model model[static 1], const f32 camera_matrix[static 16] )
{
    glstate_depth_test( STATE_ENABLE );
    glstate_cull_face( STATE_ENABLE );
    glstate_cull_back( STATE_ENABLE );
    shader_program_bind( shader_mesh.program );
    glUniformMatrix4fv( shader_mesh.pvMat, camera_matrix );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, model->diffuse );
    glActiveTexture( GL_TEXTURE0 + 1 );
    glBindTexture( GL_TEXTURE_2D, model->normal );

    if( model->indices_n )
    {
        glBindVertexArray( model->VAO );
        glDrawElements( GL_TRIANGLES, model->indices_n, GL_UNSIGNED_SHORT, 0 );
    }
}
