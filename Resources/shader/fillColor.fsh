#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float red;
uniform float green;
uniform float blue;

void main(void)
{	
	vec4 color      = texture2D(CC_Texture0, v_texCoord);
	gl_FragColor    = v_fragmentColor * vec4(red, green, blue, color.w);
}