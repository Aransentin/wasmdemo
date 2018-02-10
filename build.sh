#!/bin/bash

# JS
cat js/globals.js js/utils.js js/imports.js js/loader.js > script.js
#closure-compiler --js script.js --js_output_file script.js.opt --language_in ECMASCRIPT8 -O ADVANCED
#mv script.js.opt script.js

./meshconvert.py > model.buf

# C
for file in src/*\.[ch] ; do clang-format -i "$file" ; done
for file in shaders/*\.glsl ; do clang-format -i "$file" ; done

rm src/shader_src.h
./bufferize shaders/mesh.frag.glsl mesh_frag_src >> src/shader_src.h
./bufferize shaders/mesh.vert.glsl mesh_vert_src >> src/shader_src.h

WARN="-Weverything -Wno-language-extension-token -Wno-gnu-auto-type -Wno-c++98-compat -fcolor-diagnostics -fdiagnostics-show-option -Wno-padded"

clang -cc1 -Ofast -emit-llvm-bc -triple=wasm32-unknown-unknown-wasm -std=gnu11 $WARN -fvisibility hidden -include src/ce.h src/*\.c
llvm-link -o wasm.bc src/*\.bc
opt -O3 wasm.bc -o wasm.bc
llc -O3 -filetype=obj wasm.bc -o wasm.o
wasm-ld --no-entry wasm.o -o binary.wasm --strip-all -allow-undefined-file wasm.syms --import-memory -z stack-size=1572864

zopfli --i20 index.html
zopfli --i20 script.js
zopfli --i20 model.buf
zopfli --i20 binary.wasm

# cleanuo
rm src/*\.bc
rm wasm\.bc
rm wasm\.o
