#version 330 core

layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture variable has attribute position 2


out vec3 ourColor; 
out vec3 ourPosition; 
out vec2 TexCoord;

uniform float xOffset;
uniform float yOffset;

void main(){
    gl_Position = vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0);
    ourColor = aColor; 
    TexCoord = aTexCoord;
}
