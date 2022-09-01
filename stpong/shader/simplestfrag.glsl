#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float xOffset;

void main(){
    FragColor = mix(
            texture(texture1, TexCoord), 
            texture(texture2, TexCoord) * vec4(ourColor + xOffset, 1.0), 
            0.5
        );
}
