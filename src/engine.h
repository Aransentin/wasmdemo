#pragma once
#include "camera.h"
#include "model.h"

extern struct
{
    struct
    {
        i32 w, h;
    } window;

    Camera camera;
    Model model;

    bool initialized;
} engine;

export void engine_window_resize( i32 w, i32 h );
bool engine_init( void );
