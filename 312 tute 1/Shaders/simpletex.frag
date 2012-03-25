

uniform sampler2D tex;
void main()
{
	vec4 tex_colour = texture2D(tex,gl_TexCoord[0].st);
    gl_FragColor = tex_colour;
}