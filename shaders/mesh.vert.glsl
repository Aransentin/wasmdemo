#version 300 es
precision mediump float;

layout( location = 0 ) in vec3 vPos;
layout( location = 1 ) in vec2 vUV;
layout( location = 2 ) in vec3 vNor;
layout( location = 3 ) in vec3 vTan;

out vec3 fPos;
out vec2 fUV;
out mat3 fTBN;

uniform mat4 pvMat;

void main( void )
{
    fPos = vPos;
    fUV = vUV;

    // TBN
    vec3 nNor = normalize( vNor );
    vec3 nTan = normalize( vTan );
    fTBN = mat3( nTan, cross( nNor, nTan ), nNor );

    gl_Position = pvMat * vec4( vPos, 1.0 );
}
