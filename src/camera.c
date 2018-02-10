#include "camera.h"
#include "glmath.h"

void camera_normal_fix( Camera cam[static 1] )
{
    f32 side[3];
    vec3_cross( side, cam->dir, cam->nor );
    vec3_normalize( side );
    vec3_cross( cam->nor, side, cam->dir );
    vec3_normalize( cam->nor );
}

void camera_look_at( Camera cam[static 1], const f32 pos[static 3], const f32 trg[static 3], const f32 nor[static 3] )
{
    for( i32 i = 0; i < 3; i++ )
        cam->pos[i] = pos[i];
    for( i32 i = 0; i < 3; i++ )
        cam->nor[i] = nor[i];

    cam->dir[0] = trg[0] - pos[0];
    cam->dir[1] = trg[1] - pos[1];
    cam->dir[2] = trg[2] - pos[2];
    vec3_normalize( cam->dir );

    camera_normal_fix( cam );
}

void camera_matrix_projection( f32 pmat[static 16], Camera cam[static 1] )
{
    let a = 1.0f / cam->fov;
    pmat[0] = a / cam->aspect;
    pmat[1] = 0.0f;
    pmat[2] = 0.0f;
    pmat[3] = 0.0f;
    pmat[4] = 0.0f;
    pmat[5] = a;
    pmat[6] = 0.0f;
    pmat[7] = 0.0f;
    pmat[8] = 0.0f;
    pmat[9] = 0.0f;
    pmat[10] = -( ( cam->far + cam->near ) / ( cam->far - cam->near ) );
    pmat[11] = -1.0f;
    pmat[12] = 0.0f;
    pmat[13] = 0.0f;
    pmat[14] = -( ( 2.0f * cam->far * cam->near ) / ( cam->far - cam->near ) );
    pmat[15] = 0.0f;
}

void camera_matrix_view( f32 vmat[static 16], Camera cam[static 1] )
{
    f32 sid[3];
    let nor = cam->nor;
    let dir = cam->dir;
    vec3_cross( sid, dir, nor );

    vmat[0] = sid[0];
    vmat[1] = nor[0];
    vmat[2] = -dir[0];
    vmat[3] = 0.0f;
    vmat[4] = sid[1];
    vmat[5] = nor[1];
    vmat[6] = -dir[1];
    vmat[7] = 0.0f;
    vmat[8] = sid[2];
    vmat[9] = nor[2];
    vmat[10] = -dir[2];
    vmat[11] = 0.0f;
    vmat[12] = -vec3_dot( sid, cam->pos );
    vmat[13] = -vec3_dot( nor, cam->pos );
    vmat[14] = vec3_dot( dir, cam->pos );
    vmat[15] = 1.0f;
}

void camera_matrix_normal( f32 nmat[static 9], f32 vmat[static 16], f32 mmat[static 16] )
{
    f32 tmp[16];
    // Todo: only multiply for the 3x3 corner matrix
    mat4_mul( tmp, vmat, mmat );

    nmat[0] = tmp[0];
    nmat[1] = tmp[1];
    nmat[2] = tmp[2];
    nmat[3] = tmp[4];
    nmat[4] = tmp[5];
    nmat[5] = tmp[6];
    nmat[6] = tmp[8];
    nmat[7] = tmp[9];
    nmat[8] = tmp[10];
}

void camera_matrix_projectionview( f32 mat[static 16], Camera cam[static 1] )
{
    f32 sid[3];
    let nor = cam->nor;
    let dir = cam->dir;
    vec3_cross( sid, dir, nor );

    const f32 p1 = 1.0f / cam->fov;
    const f32 p0 = p1 / cam->aspect;
    const f32 p2 = -( ( cam->far + cam->near ) / ( cam->far - cam->near ) );
    const f32 p3 = ( 2.0f * cam->far * cam->near ) / ( cam->near - cam->far );

    mat[0] = p0 * sid[0];
    mat[1] = p1 * nor[0];
    mat[2] = p2 * -dir[0];
    mat[3] = dir[0];

    mat[4] = p0 * sid[1];
    mat[5] = p1 * nor[1];
    mat[6] = p2 * -dir[1];
    mat[7] = dir[1];

    mat[8] = p0 * sid[2];
    mat[9] = p1 * nor[2];
    mat[10] = p2 * -dir[2];
    mat[11] = dir[2];

    mat[12] = p0 * -vec3_dot( sid, cam->pos );
    mat[13] = p1 * -vec3_dot( nor, cam->pos );
    mat[14] = p2 * vec3_dot( dir, cam->pos ) + p3;
    mat[15] = -vec3_dot( dir, cam->pos );
}
