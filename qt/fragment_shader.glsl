varying vec3 world_pos;
varying vec3 ma_couleur;
varying vec3 normal;

void main()
{
    float ambiant = 0.1;
    vec3 light_source = vec3(-2, 2, 2);


    vec3 light_dir = normalize(light_source - world_pos);
    vec3 n = normalize(normal);
    float diff = max(dot(n, light_dir), 0.0);

    gl_FragColor = vec4((ambiant + diff ) * ma_couleur, 1.0);
//    gl_FragColor = vec4(world_pos, 1);
//    gl_FragColor = vec4(ma_couleur, 1.0);
//    gl_FragColor = vec4(light_dir, 1.0);

}
