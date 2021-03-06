#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4 u_ColorFlash;

void main(void)
{
    vec4 texColor = texture2D(CC_Texture0, v_texCoord); 
	//texColor.rgb = mix(texColor.rgb, u_ColorFlash.rgb*texColor.a, u_ColorFlash.a);
	texColor = vec4(texColor.r * u_ColorFlash.r, texColor.g * u_ColorFlash.g, texColor.b * u_ColorFlash.b, texColor.a * u_ColorFlash.a);
	gl_FragColor = v_fragmentColor * texColor;
}