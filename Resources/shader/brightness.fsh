#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float value;

void main(void)
{	
	vec4 vC = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	gl_FragColor = vec4(vC.r * value, vC.g * value, vC.b * value, vC.a);
}