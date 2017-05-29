varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_normals;
uniform vec3  u_lightPos;
uniform vec2  u_contentSize;
uniform vec3  u_lightColor;
uniform vec3  u_ambientColor;

uniform float  u_brightness;
uniform float u_cutoffRadius;
uniform float u_halfRadius;

void main()
{
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	gl_FragColor = texColor;
}