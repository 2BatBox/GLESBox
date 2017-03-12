precision mediump float;

uniform float uTime;

varying vec2 vCoord;

#define PI (3.14)
#define PI_3 (3.14/3.0)

#define MIX_FACTOR 5.0

vec4 testStar(vec2 nc){
    
    float step = uTime / 2.0;
    float x1,x2,x3;

    float r = .0;
    float g = .0;
    float b = .0;
    
    x1 = sin(nc.x * PI + step) - sin(nc.x * PI_3 + step) / 3.0;
    x2 = sin(-nc.x * PI + PI_3 + step * 1.3) + x1 / 3.0;
    x3 = sin(nc.x * PI + 2.0 * PI_3 + step * 2.0) + (x1 + x2) / 3.0;
    
    r = 1.1 - abs(x1 - nc.y);
    g = 1.1 - abs(x2 - nc.y);
    b = 1.1 - abs(x3 - nc.y);
        
    return vec4(
        r + (g + b) / MIX_FACTOR,
        g + (r + b) / MIX_FACTOR,
        b + (r + g) / MIX_FACTOR,
        1.0);
}

void main() {

	float xn = vCoord.x;
    float yn = vCoord.y;
    xn *= 2.0;
    //xn -= 2.0;
    
    yn *= 2.0;
    //yn -= 2.0;
    
	gl_FragColor = testStar(vec2(xn, yn));
}