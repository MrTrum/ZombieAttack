#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec3 u_Offset;

void main(void)
{
    vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	float redScale = 0.2126 - u_Offset.r;
	float greenScale = 0.9152 - u_Offset.g;
	float blueScale = 0.9722 - u_Offset.b;
	float grayscaleFactor = redScale*texColor.r + greenScale*texColor.g + blueScale*texColor.b;
	vec4 finalColor = vec4(grayscaleFactor, grayscaleFactor,
				grayscaleFactor, 0.1722*texColor.a);
 
	gl_FragColor = v_fragmentColor * finalColor;
}