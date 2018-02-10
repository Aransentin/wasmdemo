#include "render.h"
#include "engine.h"
#include "glstate.h"
#include "shader.h"
#include "trig.h"
#include "util.h"
#include "webgl.h"

export void render( void )
{
    if( !engine.initialized )
        return;

    f64 ts = date_now();

    const f32 * cPos = ( f32[3] ){
        (f32)cos( ts ) * 12.0f,
        (f32)sin( ts ) * 12.0f,
        6.0f,
    };

    camera_look_at( &engine.camera, cPos, ( f32[3] ){0.0f, 0.0f, 3.5f}, ( f32[3] ){0.0f, 0.0f, 1.0f} );

    glViewport( 0, 0, engine.window.w, engine.window.h );
    glClearBuffer( GL_COLOR, 0, 0.0f, 0.0f, 0.0f, 0.0f );
    glClearBuffer( GL_DEPTH, 0, 1.0f, 0.0f, 0.0f, 0.0f );

    f32 pvMat[16];
    camera_matrix_projectionview( pvMat, &engine.camera );

    shader_program_bind( shader_mesh.program );
    glUniform3fv( shader_mesh.lPos, (f32)cos( ts * 1.3 ) * 6.0f, (f32)sin( ts * 1.3 ) * 6.0f, 2.0 );
    glUniform3fv( shader_mesh.cPos, cPos[0], cPos[1], cPos[2] );

    model_render( &engine.model, pvMat );
}
