attribute vec3 vertex;
attribute vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec3 ma_couleur;
varying vec3 world_pos;
varying vec3 normal;

void main()
{
  gl_Position = projection * view * model * vec4(vertex, 1.0);

  world_pos = vec3( model * vec4(vertex, 1.0));
//  ma_couleur = (1.0 + sommet) / 2.0;
  ma_couleur = vec3(1, 0.7, 0);
//  ma_couleur = abs(gl_Normal);
//  mat3 m = mat3(model[0][0], model[0][1], model[0][1],
//          model[1][0], model[1][1], model[1][2],
//          model[2][0], model[2][2], model[2][2]);
//  normal = vertex;
//  normal =  m * sommet;
  normal = vec3(model * vec4(gl_Normal.xyz, 0.0));
}
