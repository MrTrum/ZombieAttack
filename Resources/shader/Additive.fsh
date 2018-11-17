#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float r;
uniform float g;
uniform float b;
uniform float a;
																			      
void main()
{
	gl_FragColor = texture2D(CC_Texture0, v_texCoord);
	if (gl_FragColor.a > 0.2)
	{	
		gl_FragColor.r += r;
		gl_FragColor.g += g;
		gl_FragColor.b += b;
		gl_FragColor.a += a;
	}
}