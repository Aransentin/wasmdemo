#include "shader.h"
#include "shader_src.h"
#include "webgl.h"

typeof( shader_mesh ) shader_mesh = {.program = 0};

care static i32 shader_init_generic( i32 type, const char src[static 1], i32 len )
{
    let shader = glCreateShader( type );
    glShaderSource( shader, src, len );

    glCompileShader( shader );

    if( !glGetShaderParameter( shader, GL_COMPILE_STATUS ) )
    {
        glutil_printShaderInfoLog( shader );
        glDeleteShader( shader );
        return 0;
    }

    return shader;
}

care static i32 program_init_generic( const char vsrc[static 1], i32 vn, const char fsrc[static 1], i32 fn )
{
    let program = glCreateProgram();

    let vs = shader_init_generic( GL_VERTEX_SHADER, vsrc, vn );
    let fs = shader_init_generic( GL_FRAGMENT_SHADER, fsrc, fn );

    if( !vs || !fs )
    {
        glDeleteProgram( program );
        if( !vs )
            glDeleteShader( vs );
        if( !fs )
            glDeleteShader( fs );
        return 0;
    }

    glAttachShader( program, vs );
    glAttachShader( program, fs );
    glLinkProgram( program );

    if( !glGetProgramParameter( program, GL_LINK_STATUS ) )
    {
        glutil_printProgramInfoLog( program );
        glDeleteShader( vs );
        glDeleteShader( fs );
        glDeleteProgram( program );
        return 0;
    }
    glDetachShader( program, vs );
    glDetachShader( program, fs );
    glDeleteShader( vs );
    glDeleteShader( fs );
    return program;
}

care bool shaders_init( void )
{

    shader_mesh.program = program_init_generic( (const char *)mesh_vert_src, sizeof( mesh_vert_src ), (const char *)mesh_frag_src, sizeof( mesh_frag_src ) );
    if( !shader_mesh.program )
        return false;

    shader_program_bind( shader_mesh.program );
    shader_mesh.pvMat = glGetUniformLocation( shader_mesh.program, "pvMat", __builtin_strlen( "pvMat" ) );
    shader_mesh.lPos = glGetUniformLocation( shader_mesh.program, "lPos", __builtin_strlen( "lPos" ) );
    shader_mesh.cPos = glGetUniformLocation( shader_mesh.program, "cPos", __builtin_strlen( "cPos" ) );

    glUniform1i( glGetUniformLocation( shader_mesh.program, "tDiffuse", __builtin_strlen( "tDiffuse" ) ), 0 );
    glUniform1i( glGetUniformLocation( shader_mesh.program, "tNormal", __builtin_strlen( "tNormal" ) ), 1 );

    return true;
}

void shader_program_bind( i32 program )
{
    static i32 prev = 0;

    if( program == prev )
        return;
    else
        glUseProgram( program );

    prev = program;
}
