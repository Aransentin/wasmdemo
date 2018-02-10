#pragma once

typedef struct
{
    f32 pos[3];
    f32 dir[3];
    f32 nor[3];
    f32 aspect, fov;
    f32 near, far;
} Camera;

void camera_look_at( Camera cam[static 1], const f32 pos[static 3], const f32 trg[static 3], const f32 nor[static 3] );
void camera_normal_fix( Camera cam[static 1] );

void camera_matrix_projection( f32 pmat[static 16], Camera cam[static 1] );
void camera_matrix_view( f32 vmat[static 16], Camera cam[static 1] );
void camera_matrix_normal( f32 nmat[static 9], f32 vmat[static 16], f32 mmat[static 16] );

void camera_matrix_projectionview( f32 mat[static 16], Camera cam[static 1] );
