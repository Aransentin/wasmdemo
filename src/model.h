#pragma once

typedef struct
{
    i32 VAO;
    i32 indices_n;
    i32 diffuse;
    i32 normal;
} Model;

bool model_init( Model model[static 1] );
void model_destroy( Model model[static 1] );
void model_render( Model model[static 1], const f32 camera_matrix[static 16] );
