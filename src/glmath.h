#pragma once

static inline void vec3_normalize( f32 v[static 3] )
{
    let len = __builtin_sqrtf( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] );
    assume( len > 0.0f );
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

static inline void vec3_cross( f32 res[restrict static 3], const f32 v1[restrict static 3], const f32 v2[restrict static 3] )
{
    res[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

static inline care f32 vec3_dot( const f32 v1[restrict static 3], const f32 v2[restrict static 3] )
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

static inline void mat4_vec4_mul( f32 res[restrict static 4], const f32 v[restrict static 4], const f32 m[restrict static 16] )
{
    for( i32 j = 0; j < 4; ++j )
    {
        res[j] = 0.0f;
        for( i32 i = 0; i < 4; ++i )
            res[j] += m[i * 4 + j] * v[i];
    }
}

static inline void mat4_mul( f32 res[restrict static 16], const f32 m1[restrict static 16], const f32 m2[restrict static 16] )
{
    for( i32 c = 0; c < 4; c++ )
    {
        for( i32 r = 0; r < 4; r++ )
        {
            res[c * 4 + r] = 0.0f;
            for( i32 k = 0; k < 4; k++ )
                res[c * 4 + r] += m1[k * 4 + r] * m2[c * 4 + k];
        }
    }
}

static inline void mat4_invert( f32 dst[restrict static 16], const f32 src[restrict static 16] )
{
    f32 s[6];
    f32 c[6];
    s[0] = src[0] * src[5] - src[4] * src[1];
    s[1] = src[0] * src[6] - src[4] * src[2];
    s[2] = src[0] * src[7] - src[4] * src[3];
    s[3] = src[1] * src[6] - src[5] * src[2];
    s[4] = src[1] * src[7] - src[5] * src[3];
    s[5] = src[2] * src[7] - src[6] * src[3];

    c[0] = src[8] * src[13] - src[12] * src[9];
    c[1] = src[8] * src[14] - src[12] * src[10];
    c[2] = src[8] * src[15] - src[12] * src[11];
    c[3] = src[9] * src[14] - src[13] * src[10];
    c[4] = src[9] * src[15] - src[13] * src[11];
    c[5] = src[10] * src[15] - src[14] * src[11];

    const f32 det = ( s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0] );
    assume( det > 0.0f );
    const f32 idet = 1.0f / det;

    dst[0] = ( src[5] * c[5] - src[6] * c[4] + src[7] * c[3] ) * idet;
    dst[1] = ( -src[1] * c[5] + src[2] * c[4] - src[3] * c[3] ) * idet;
    dst[2] = ( src[13] * s[5] - src[14] * s[4] + src[15] * s[3] ) * idet;
    dst[3] = ( -src[9] * s[5] + src[10] * s[4] - src[11] * s[3] ) * idet;

    dst[4] = ( -src[4] * c[5] + src[6] * c[2] - src[7] * c[1] ) * idet;
    dst[5] = ( src[0] * c[5] - src[2] * c[2] + src[3] * c[1] ) * idet;
    dst[6] = ( -src[12] * s[5] + src[14] * s[2] - src[15] * s[1] ) * idet;
    dst[7] = ( src[8] * s[5] - src[10] * s[2] + src[11] * s[1] ) * idet;

    dst[8] = ( src[4] * c[4] - src[5] * c[2] + src[7] * c[0] ) * idet;
    dst[9] = ( -src[0] * c[4] + src[1] * c[2] - src[3] * c[0] ) * idet;
    dst[10] = ( src[12] * s[4] - src[13] * s[2] + src[15] * s[0] ) * idet;
    dst[11] = ( -src[8] * s[4] + src[9] * s[2] - src[11] * s[0] ) * idet;

    dst[12] = ( -src[4] * c[3] + src[5] * c[1] - src[6] * c[0] ) * idet;
    dst[13] = ( src[0] * c[3] - src[1] * c[1] + src[2] * c[0] ) * idet;
    dst[14] = ( -src[12] * s[3] + src[13] * s[1] - src[14] * s[0] ) * idet;
    dst[15] = ( src[8] * s[3] - src[9] * s[1] + src[10] * s[0] ) * idet;
}

static inline void mat4_translation_set( f32 dst[restrict static 16], f32 x, f32 y, f32 z )
{
    dst[0] = 1.0f;
    dst[1] = 0.0f;
    dst[2] = 0.0f;
    dst[3] = 0.0f;

    dst[4] = 0.0f;
    dst[5] = 1.0f;
    dst[6] = 0.0f;
    dst[7] = 0.0f;

    dst[8] = 0.0f;
    dst[9] = 0.0f;
    dst[10] = 1.0f;
    dst[11] = 0.0f;

    dst[12] = x;
    dst[13] = y;
    dst[14] = z;
    dst[15] = 1.0f;
}

static inline void mat4_rotate_X( f32 dst[restrict static 16], f32 m[restrict static 16], f32 angle )
{
    const f32 s = __builtin_sinf( angle );
    const f32 c = __builtin_cosf( angle );
    f32 tmp[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    mat4_mul( dst, m, tmp );
}

static inline void mat4_rotate_Y( f32 dst[restrict static 16], f32 m[restrict static 16], f32 angle )
{
    const f32 s = __builtin_sinf( angle );
    const f32 c = __builtin_cosf( angle );
    f32 tmp[16] = {c, 0.0f, s, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -s, 0.0f, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    mat4_mul( dst, m, tmp );
}

static inline void mat4_rotate_Z( f32 dst[restrict static 16], f32 m[restrict static 16], f32 angle )
{
    const f32 s = __builtin_sinf( angle );
    const f32 c = __builtin_cosf( angle );
    f32 tmp[16] = {c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    mat4_mul( dst, m, tmp );
}
