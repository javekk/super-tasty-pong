#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float xOffset;

void main(){
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor + xOffset, 1.0); 
}
