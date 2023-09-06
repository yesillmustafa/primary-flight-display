#version 100
// Positions/Coordinates
attribute vec3 aPos;
// Colors
attribute vec3 aColor;
// Texture Coordinates
attribute vec2 aTex;

varying vec3 vPosition;
varying vec2 vTexCoord;
varying vec3 vColor;

// Controls the scale of the vertices
uniform float scale;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	vColor = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	vTexCoord = aTex;
	vPosition = aColor;
}
