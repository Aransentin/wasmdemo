#include "engine.h"

export bool init( void );
export bool init( void )
{
    if( !engine_init() )
        return false;

    engine.camera.near = 1.0f;
    engine.camera.far = 512.0f;
    engine.camera.fov = 0.4f;

    camera_look_at( &engine.camera, ( f32[3] ){8.0f, 8.0f, 6.0f}, ( f32[3] ){0.0f, 0.0f, 3.5f}, ( f32[3] ){0.0f, 0.0f, 1.0f} );

    return true;
}
