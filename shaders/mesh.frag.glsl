#version 300 es
precision mediump float;

uniform sampler2D tDiffuse;
uniform sampler2D tNormal;

uniform vec3 cPos;
uniform vec3 lPos;

in vec3 fPos;
in vec2 fUV;
in mat3 fTBN;

out vec4 oCol;

void main( void )
{
    vec3 rNor = texture( tNormal, fUV ).xyz * 2.0 - 1.0;
    vec3 fNor = normalize( fTBN * rNor );
    vec3 tDif = texture( tDiffuse, fUV ).rgb;

    vec3 cDir = normalize( lPos - cPos );

    vec3 fCol = vec3( 0.0 );

    {
        vec3 lnPos = lPos;
        vec3 lDir = normalize( lnPos - fPos );
        float lDist = length( lnPos - fPos );
        float lDiff = max( dot( fNor, lDir ), 0.0 );
        float lSpec = 2.0 * pow( max( dot( reflect( -lDir, fNor ), -cDir ), 0.0 ), 12.0 );
        fCol += 10.0 * vec3( 0.77, 0.09, 0.61 ) * tDif * ( lDiff + lSpec ) / pow( lDist, 2.0 );
    }
    {
        vec3 lnPos = vec3( -lPos.y, lPos.xz );
        // vec3 lnPos = lPos;
        vec3 lDir = normalize( lnPos - fPos );
        float lDist = length( lnPos - fPos );
        float lDiff = max( dot( fNor, lDir ), 0.0 );
        float lSpec = 2.0 * pow( max( dot( reflect( -lDir, fNor ), -cDir ), 0.0 ), 12.0 );
        fCol += 10.0 * vec3( 0.24, 0.33, 0.76 ) * tDif * ( lDiff + lSpec ) / pow( lDist, 2.0 );
    }

    oCol = vec4( pow( fCol, vec3( 1.0 / 2.2 ) ), 1.0 );
    // oCol = vec4( cDir * 0.5 + 0.5, 1.0 );
}
