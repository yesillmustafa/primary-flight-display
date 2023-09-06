// Outputs colors in RGBA
precision mediump float;
// Inputs the texture coordinates from the Vertex Shader
varying vec2 vTexCoord;
varying vec3 vColor;
varying vec3 vPosition;
// Gets the Texture Unit from the main function
uniform sampler2D tex0;

void main()
{

   gl_FragColor = texture2D(tex0, vTexCoord);
   //gl_FragColor = vec4(vColor,1.0f);
}
