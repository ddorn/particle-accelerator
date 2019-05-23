attribute vec3 vertex;
attribute vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec4 base_color;
varying vec3 world_pos;
varying vec3 normal;
varying vec2 texturePos;

vec3 rainbow(vec3 pos) {
  vec2 p = normalize(pos.xy);
  float a = (acos(p.x) * 180.0 / 3.1415926535);
  if (p.y < 0.0) { a = 360.0 - a; }
  
  float X = 1.0 - abs(mod(a / 60.0, 2.0) - 1.0);
  float Rs, Gs, Bs;

  if (a >= 0. && a < 60.) {
    Rs = 1.0;
    Gs = X;
    Bs = 0.0;
  } else if (a >= 60. && a < 120.) {
    Rs = X;
    Gs = 1.0;
    Bs = 0.0;
  } else if (a >= 120. && a < 180.) {
    Rs = 0.0;
    Gs = 1.0;
    Bs = X;
  } else if (a >= 180. && a < 240.) {
    Rs = 0.0;
    Gs = X;
    Bs = 1.0;
  } else if (a >= 240. && a < 300.) {
    Rs = X;
    Gs = 0.0;
    Bs = 1.0;
  } else {
    Rs = 1.0;
    Gs = 0.0;
    Bs = X;
  }

  return vec3(Rs, Gs, Bs);
}

void main()
{
  gl_Position = projection * view * model * vec4(vertex, 1.0);

  world_pos = vec3(model * vec4(vertex, 1.0));

  if (color == vec4(1.0, 1.0, 1.0, 0.0)) {
    base_color = vec4(rainbow(world_pos), 0.7);
  } else {
    base_color = min(abs(color), 1.0);
  }

  if (gl_Normal == vec3(0, 0, 0)) {
    // Case of a sphere
    // Note that this works only because we don't rotate spheres
    // And that we pass a 0 normal before drawing spheres
    normal = vertex;
    texturePos = 0.5 * vertex.yz + vec2(.5, .5);
  } else {
    // Case of something I somewhat control

    normal = gl_Normal;
  }
}
