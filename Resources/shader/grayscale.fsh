#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
    vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	float grayscaleFactor = 0.2126*texColor.r + 0.7152*texColor.g + 0.0722*texColor.b;
	vec4 finalColor = vec4(grayscaleFactor, grayscaleFactor,
				grayscaleFactor, texColor.a);
 
	gl_FragColor = v_fragmentColor * finalColor;
}