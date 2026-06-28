#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 couleur;
layout(location = 2) in float taille;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 vCouleur;

void main() {
  vec4 posMonde = model * vec4(pos, 1.0);
  vec4 posVue = view * posMonde;
  gl_Position = proj * posVue;

  float dist = length(posVue.xyz);
  gl_PointSize = taille * (100.0 / max(dist, 1.0));

  vCouleur = couleur;
}
