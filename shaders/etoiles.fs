#version 330

in vec3 vCouleur;
out vec4 fragColor;

uniform float fade;

void main() {
  float dist = length(gl_PointCoord * 2.0 - 1.0);
  if(dist > 1.0)
    discard;

  fragColor = vec4(vCouleur, (1.0 - dist) * fade);
}