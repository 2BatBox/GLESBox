attribute vec4 aPosition;
attribute vec3 aColor;

uniform float uTime;

varying vec2 vCoord;

void main() {
	gl_Position = aPosition;
	vCoord = vec2(aPosition);
}