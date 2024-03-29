#version 330 core

in vec2 textureCoordinates;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main(){    
    color = vec4(spriteColor, 1.0) * texture(image, textureCoordinates);
}  
