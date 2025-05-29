#version 330 core
layout ( location = 0 ) in vec3 inPos;
layout ( location = 1 ) in vec3 inColor;
layout ( location = 2 ) in vec2 inTexCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    gl_Position = projection * view * model * vec4( inPos, 1.0 );
    vertexColor = vec4( inColor, 1.0 );
    texCoord = inTexCoord;
}