#include "engine.h"
#include "shader.h"
#include "webgl.h"

typeof( engine ) engine = {.window.w = 0};

export void engine_window_resize( i32 w, i32 h )
{
    engine.window.w = w;
    engine.window.h = h;
    engine.camera.aspect = w / (f32)h;
}

bool engine_init( void )
{
    // Context already exists

    if( !shaders_init() )
        return false;

    if( !model_init( &engine.model ) )
        return false;

    engine.initialized = true;
    return true;
}
