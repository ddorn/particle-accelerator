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

  world_pos = vec3(model * vec4(vertex, 1.0));
  ma_couleur = vec3(1, 0.7, 0);

  if (gl_Normal == vec3(0, 0, 0)) {
    // Case of a sphere
    // Note that this works only because we don't rotate spheres
    normal = vertex;
  } else {
    // Case of something I control
    normal = gl_Normal;
  }
}
