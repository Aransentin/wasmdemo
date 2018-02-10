#!/usr/bin/env python2

import os, sys, struct
from pyassimp import *
from pyassimp.postprocess import *

def f2i8( f ):
    return int( f * 127 )

def f2u16( f ):
    return int( f * 65535 )

for file in os.listdir( "models/" ):
    if not file.endswith(".obj"):
        continue

    base = file.replace( ".obj", "" )
    scene = load( 'models/' + file, file_type="obj", processing=( aiProcess_Triangulate | aiProcess_ImproveCacheLocality | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices ) )
    mesh = scene.meshes[0]
    
    vert = struct.Struct('3f 2H 4b 4b')
    elem = struct.Struct('3H')
    
    for i in range( 0, len( mesh.faces ) ):
        val = elem.pack( mesh.faces[i][0], mesh.faces[i][1], mesh.faces[i][2] )
        sys.stdout.write( val )

    for i in range( 0, len( mesh.vertices ) ):
        val = vert.pack(
            mesh.vertices[i][0], mesh.vertices[i][1], mesh.vertices[i][2],
            f2u16(mesh.texturecoords[0][i][0]), f2u16(1.0-mesh.texturecoords[0][i][1]),
            f2i8(mesh.normals[i][0]), f2i8(mesh.normals[i][1]), f2i8(mesh.normals[i][2]), 0,
            f2i8(mesh.tangents[i][0]), f2i8(mesh.tangents[i][1]), f2i8(mesh.tangents[i][2]), 0
        )
        sys.stdout.write( val )
