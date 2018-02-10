#pragma once

extern struct
{
    i32 program;
    i32 pvMat;
    i32 lPos;
    i32 cPos;
} shader_mesh;

care bool shaders_init( void );
void shader_program_bind( i32 program );
