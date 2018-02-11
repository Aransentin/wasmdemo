imports["glActiveTexture"] = function( slot ){
    gl['activeTexture']( slot );
}
imports["glAttachShader"] = function( program_id, shader_id ){
    let program = gl_id_map[program_id];
    let shader = gl_id_map[shader_id];
    gl.attachShader( program, shader );
}
imports["glBindBuffer"] = function( target, buffer_id ){
    let buffer = gl_id_map[ buffer_id ];
    gl.bindBuffer( target, buffer );
}
//imports["glBindFramebuffer"]
//imports["glBindSampler"]
imports["glBindTexture"] = function( type, tex_id ){
    let tex = gl_id_map[ tex_id ];
    gl['bindTexture']( type, tex );
}
imports["glBindVertexArray"] = function( vao_id ){
    let vao = gl_id_map[ vao_id ];
    gl['bindVertexArray']( vao );
}
//imports["glBlendColor"]
//imports["glBlendEquationSeparate"]
//imports["glBlendFuncSeparate"]
imports["glBufferData"] = function( target, data, usage, length ){
    let dataslice = memory.subarray( data, data+length );
    gl.bufferData( target, dataslice, usage );
}
imports["glClearBuffer"] = function( buffer, drawbuffer, r, g, b, a ){
    gl['clearBufferfv']( buffer, drawbuffer, new Float32Array([r, g, b, a]) );
}
//imports["glColorMask"]
imports["glCompileShader"] = function( shader_id ){
    let shader = gl_id_map[shader_id];
    gl.compileShader( shader );
}
imports["glCreateBuffer"] = function(){
    let buffer = gl.createBuffer();
    let buffer_id = webgl_id_new( buffer );
    return buffer_id;
}
//imports["glCreateFramebuffer"]
imports["glCreateProgram"] = function(){
    let program = gl.createProgram();
    let program_id = webgl_id_new( program );
    return program_id;
}
//imports["glCreateSampler"]
imports["glCreateShader"] = function( type ){
    let shader = gl.createShader( type );
    let shader_id = webgl_id_new( shader );
    return shader_id;
}
//imports["glCreateTexture"]
imports["glCreateVertexArray"] = function(){
    let vao = gl['createVertexArray']();
    let vao_id = webgl_id_new( vao );
    return vao_id;
}
imports["glCullFace"] = function( mode ){
    gl.cullFace( mode );
}
imports["glDeleteBuffer"] = function( buffer_id ){
    let buffer = gl_id_map[ buffer_id ];
    gl.deleteBuffer( buffer );
    webgl_id_remove( buffer_id );
}
//imports["glDeleteFramebuffer"]
imports["glDeleteProgram"] = function( program_id ){
    let program = gl_id_map[program_id];
    gl.deleteProgram( program );
    webgl_id_remove( program_id )
}
//imports["glDeleteSampler"]
imports["glDeleteShader"] = function( shader_id ){
    let shader = gl_id_map[shader_id];
    gl.deleteShader( shader );
    webgl_id_remove( shader_id );
}
//imports["glDeleteTexture"]
imports["glDeleteVertexArray"] = function( vao_id ){
    let vao = gl_id_map[ vao_id ];
    gl['deleteVertexArray']( vao );
    webgl_id_remove( vao_id );
}
//imports["glDepthFunc"]
//imports["glDepthMask"]
imports["glDetachShader"] = function( program_id, shader_id ){
    let program = gl_id_map[program_id];
    let shader = gl_id_map[shader_id];
    gl.detachShader( program, shader );
}
imports["glDisable"] = function( cap ){
    gl.disable( cap );
}
//imports["glDrawArrays"]
//imports["glDrawBuffer"]
imports["glDrawElements"] = function( mode, count, type, offset ){
    gl.drawElements( mode, count, type, offset );
}
imports["glEnable"] = function( cap ){
    gl.enable( cap );
}
imports["glEnableVertexAttribArray"] = function( index ){
    gl.enableVertexAttribArray( index );
}
//imports["glFramebufferParameteri"]
//imports["glFramebufferTexture"]
//imports["glFrontFace"]
//imports["glGenBuffer"]
//imports["glGenFramebuffer"]
//imports["glGenSampler"]
imports["glCreateTexture"] = function(){
    let tex = gl['createTexture']();
    let tex_id = webgl_id_new( tex );
    return tex_id;
}
//imports["glGet"]
imports["glGetProgramParameter"] = function( program_id, param ){
    let program = gl_id_map[program_id];
    return gl.getProgramParameter( program, param );
}
//imports["glGetProgramInfoLog"]
imports["glGetShaderParameter"] = function( shader_id, param ){
    let shader = gl_id_map[shader_id];
    return gl.getShaderParameter( shader, param );
}
//imports["glGetShaderInfoLog"]
imports["glGenerateMipmap"] = function( target ){
    gl['generateMipmap']( target );
}
//imports["glGetString"]
imports["glGetUniformLocation"] = function( program_id, name_ptr, name_len ){
    let program = gl_id_map[program_id];
    let name = utf8decoder.decode( memory.subarray( name_ptr, name_ptr+name_len ) );
    let location = gl.getUniformLocation( program, name );
    let location_id = webgl_id_new( location );
    return location_id;
}
imports["glLinkProgram"] = function( program_id ){
    let program = gl_id_map[program_id];
    gl.linkProgram( program );
}
//imports["glLogicOp"]
imports["glShaderSource"] = function( shader_id, source_ptr, src_len ){
    let shader = gl_id_map[shader_id];
    gl.shaderSource( shader, buf2str( source_ptr, src_len ) );
}
imports["glTexParameterf"] = function( target, pname, param ){
    gl["texParameterf"]( target, pname, param );
}
imports["glTexParameteri"] = function( target, pname, param ){
    gl["texParameteri"]( target, pname, param );
}

imports["glTexStorage2D"] = function( target, levels, internalformat, width, height ){
    gl['texStorage2D']( target, levels, internalformat, width, height );
}
imports["glTexSubImage2D"] = function( target, level, xoff, yoff, width, height, format, type, data, len ){
    let buffer = memory.slice( data, data+len );
    gl['texSubImage2D']( target, level, xoff, yoff, width, height, format, type, buffer );
}
imports["glUniform1i"] = function( location_id, value ){
    let location = gl_id_map[location_id];
    gl['uniform1i']( location, value );
}
imports["glUniform3fv"] = function( location_id, x, y, z ){
    let location = gl_id_map[location_id];
    gl['uniform3fv']( location, [x, y, z] );
}
imports["glUniformMatrix4fv"] = function( location_id, data ){
    let location = gl_id_map[location_id];
    let dataslice = memory.slice( data, data+4*16 );
    gl.uniformMatrix4fv( location, false, new Float32Array( dataslice.buffer ) );
}
imports["glUseProgram"] = function( program_id ){
    let program = gl_id_map[program_id];
    gl.useProgram( program );    
}
imports["glVertexAttribPointer"] = function( index, size, type, normalized, stride, offset ){    
    gl.vertexAttribPointer( index, size, type, normalized, stride, offset );
}
imports["glViewport"] = function( x, y, w, h ){    
    gl.viewport( x, y, w, h );
}

imports["glutil_printShaderInfoLog"] = function( shader_id ){
    let shader = gl_id_map[shader_id];
    let log = gl.getShaderInfoLog( shader );
    console.log( "Shader log:\n" + log );
}
imports["glutil_printProgramInfoLog"] = function( program_id ){
    let program = gl_id_map[program_id];
    let log = gl.getProgramInfoLog( program );
    console.log( "Program log:\n" + log );
}

imports["util_buffer_get"] = function( id, buf ){    
    let file = files[id];
    let arr = memory.subarray( buf, buf+file.byteLength );
    arr.set( new Uint8Array( file ) );
    return true;
}

imports["date_now"] = function(){
    return Date.now() * 0.001;
}
