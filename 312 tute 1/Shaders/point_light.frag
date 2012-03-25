
// Direction of reflection
varying vec3  ReflectDir;
// Intensity of the light
varying float LightIntensity;
// Brightness of the light
uniform float Brightness;
// Texture sampler
uniform sampler2D tex;

void main()
{
	//Get this fragment's texture colour
	vec4 tex_colour = texture2D(tex,gl_TexCoord[0].st);
	//Make the base colour on...
    vec4 base_colour = LightIntensity * tex_colour * Brightness;

	//deepen dark colours
	if(((base_colour.r+base_colour.g+base_colour.b)/2)<=0.5)
	{
		//base_colour.rgb -= 0.04;
	}
	else//brigten brighter colours
	{
		//base_colour.rgb += 0.1;
	}

    gl_FragColor = base_colour;
}