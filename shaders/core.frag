#version 330 core

in vec4 vertexColor;

out vec4 fragColor;

void main() {
    fragColor = vertexColor + vec4( 0.5, 0.5, 0.0, 0.0 );
}