function buf2str( ptr, len ){
    let arr = memory.subarray( ptr, ptr+len );
    return utf8decoder.decode( arr );
}

function error_fatal( message ){
    console.log( message );
    throw message;
}

function webgl_id_new( obj ){
    if( gl_id_freelist.length == 0 )
    {
        gl_id_map.push( obj );
        return gl_id_map.length - 1;
    }
    else
    {
        let id = gl_id_freelist.shift();
        gl_id_map[id] = obj;
        return id;
    }
}

function webgl_id_remove( id ){
    delete gl_id_map[id];
    gl_id_freelist.push( id );
}
