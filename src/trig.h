#pragma once

static inline f64 cos( f64 x )
{
    double cv = 0.0;

    x = x - __builtin_floor( x / ( 2.0 * 3.14159265 ) ) * 3.14159265 * 2.0;

    if( x < -3.14159265 )
        x += 6.28318531;
    else if( x > 3.14159265 )
        x -= 6.28318531;

    x += 1.57079632;
    if( x > 3.14159265 )
        x -= 6.28318531;

    if( x < 0 )
    {
        cv = 1.27323954 * x + 0.405284735 * x * x;

        if( cv < 0 )
            cv = .225 * ( cv * -cv - cv ) + cv;
        else
            cv = .225 * ( cv * cv - cv ) + cv;
    }
    else
    {
        cv = 1.27323954 * x - 0.405284735 * x * x;

        if( cv < 0 )
            cv = .225 * ( cv * -cv - cv ) + cv;
        else
            cv = .225 * ( cv * cv - cv ) + cv;
    }
    return cv;
}

static inline f64 sin( f64 x )
{
    double cv = 0.0;

    x = x - __builtin_floor( x / ( 2.0 * 3.14159265 ) ) * 3.14159265 * 2.0;

    if( x < -3.14159265 )
        x += 6.28318531;
    else if( x > 3.14159265 )
        x -= 6.28318531;

    if( x < 0 )
    {
        cv = 1.27323954 * x + 0.405284735 * x * x;

        if( cv < 0 )
            cv = .225 * ( cv * -cv - cv ) + cv;
        else
            cv = .225 * ( cv * cv - cv ) + cv;
    }
    else
    {
        cv = 1.27323954 * x - 0.405284735 * x * x;

        if( cv < 0 )
            cv = .225 * ( cv * -cv - cv ) + cv;
        else
            cv = .225 * ( cv * cv - cv ) + cv;
    }
    return cv;
}

/*
static inline f64 sin( f64 x )
{
    double cos = 0.0, sin = 0.0;

    if( x < -3.14159265 )
        x += 6.28318531;
    else if( x > 3.14159265 )
        x -= 6.28318531;

    // compute sine
    if( x < 0 )
    {
        sin = 1.27323954 * x + .405284735 * x * x;

        if( sin < 0 )
            sin = .225 * ( sin * -sin - sin ) + sin;
        else
            sin = .225 * ( sin * sin - sin ) + sin;
    }
    else
    {
        sin = 1.27323954 * x - 0.405284735 * x * x;

        if( sin < 0 )
            sin = .225 * ( sin * -sin - sin ) + sin;
        else
            sin = .225 * ( sin * sin - sin ) + sin;
    }

    // compute cosine: sin(x + PI/2) = cos(x)
    x += 1.57079632;
    if( x > 3.14159265 )
        x -= 6.28318531;

    if( x < 0 )
    {
        cos = 1.27323954 * x + 0.405284735 * x * x;

        if( cos < 0 )
            cos = .225 * ( cos * -cos - cos ) + cos;
        else
            cos = .225 * ( cos * cos - cos ) + cos;
    }
    else
    {
        cos = 1.27323954 * x - 0.405284735 * x * x;

        if( cos < 0 )
            cos = .225 * ( cos * -cos - cos ) + cos;
        else
            cos = .225 * ( cos * cos - cos ) + cos;
    }
    *cv = cos;
    *sv = sin;
}
*/
