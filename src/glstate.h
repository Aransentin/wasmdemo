#pragma once

#define STATE_ENABLE 1
#define STATE_DISABLE 2

/* Can't make a generic function, not all state is simply glEnable and glDisable */
void glstate_depth_test( u8 state );
void glstate_cull_face( u8 state );
void glstate_cull_back( u8 state );
