
// Direction of reflection
varying vec3  ReflectDir;
// Intensity of the light
varying float LightIntensity;
// Model coordinate position
varying vec2  MCposition;
// Position of the light
uniform vec3  LightPos;
// Adjust the specular contribution
const float SpecularContribution = 0.4;
// Adjust the diffuse contribution according to spec
const float DiffuseContribution  = 1.0 - SpecularContribution;

void main()
{
	vec4 pos      = gl_ModelViewMatrix * gl_Vertex;
	vec3 normal   = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec = normalize(LightPos - pos);
	ReflectDir    = reflect(-lightVec, normal);
	vec3 viewVec  = normalize(pos);
    
	float diffuse = max(dot(lightVec, normal), 0.0);
    float spec    = 0.0;

	// If the angle between the light vec and the normal
	// was less than 90 deg calculate the reflection
    if (diffuse > 0.0)
    {
        spec = max(dot(ReflectDir, viewVec), 0.0);
        spec = pow(spec, 16.0);
    }
	// Calculate the light intensity on ...
    LightIntensity = DiffuseContribution * diffuse +
                      SpecularContribution * spec;

	/*if(diffuse >= 0.3)
    {
		LightIntensity*=2.1;
    }
	else
	{
		LightIntensity*=0.25;
	}*/


	MCposition      = gl_Vertex.xy;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}