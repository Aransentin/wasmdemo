#include "glstate.h"
#include "webgl.h"

void glstate_depth_test( u8 state )
{
    static u8 prev;
    if( prev == state )
        return;

    if( state == STATE_ENABLE )
        glEnable( GL_DEPTH_TEST );
    else
        glDisable( GL_DEPTH_TEST );
    prev = state;
}

void glstate_cull_face( u8 state )
{
    static u8 prev;
    if( prev == state )
        return;

    if( state == STATE_ENABLE )
        glEnable( GL_CULL_FACE );
    else
        glDisable( GL_CULL_FACE );
    prev = state;
}

void glstate_cull_back( u8 state )
{
    static u8 prev;
    if( prev == state )
        return;

    if( state == STATE_ENABLE )
        glCullFace( GL_BACK );
    else
        glCullFace( GL_FRONT );
    prev = state;
}
