varying vec3 world_pos;
varying vec4 base_color;
varying vec3 normal;

void main()
{
    if (base_color.a < 0.5)
        discard;
    float ambiant = 0.1;
    vec3 light_source = vec3(0, 2, 4);


//    vec3 light_dir = normalize(light_source - world_pos);
//     We consider the light source is far enough (~sun) so it's always the same direction
    vec3 light_dir = normalize(light_source);
    vec3 n = normalize(normal);
    float diff = max(dot(n, light_dir), 0.0);

    gl_FragColor = vec4((ambiant + diff) * base_color.xyz, base_color.a);
//    gl_FragColor = vec4(world_pos, 1);
//    gl_FragColor = vec4(ma_couleur, 1.0);
//    gl_FragColor = vec4(light_dir, 1.0);

}
