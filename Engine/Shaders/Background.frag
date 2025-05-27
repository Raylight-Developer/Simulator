#version 460 core

uniform float iTime;
uniform int   iFrame;
uniform float iTimeDelta;
uniform vec2  iResolution;

uniform float uZoom;
uniform vec2  uCenter;

in vec2 vTexCoord;

out vec4 fragColor;

vec3 palette(float d){
	return mix(vec3(0.2,0.7,0.9),vec3(1.,0.,1.),d);
}

vec2 rotate(vec2 p,float a){
	float c = cos(a);
	float s = sin(a);
	return p*mat2(c,s,-s,c);
}

float map(vec3 p){
	for( int i = 0; i<8; ++i){
		float t = iTime*0.2;
		p.xz =rotate(p.xz,t);
		p.xy =rotate(p.xy,t*1.89);
		p.xz = abs(p.xz);
		p.xz-=.5;
	}
	return dot(sign(p),p)/5.;
}

vec4 rm (vec3 ro, vec3 rd){
	float t = 0.;
	vec3 col = vec3(0.);
	float d;
	for(float i =0.; i<64.; i++){
		vec3 p = ro + rd*t;
		d = map(p)*.5;
		if(d<0.02){
			break;
		}
		if(d>100.){
			break;
		}
		//col+=vec3(0.6,0.8,0.8)/(400.*(d));
		col+=palette(length(p)*.1)/(400.*(d));
		t+=d;
	}
	return vec4(col,1./(d*100.));
}

vec3 palette_b( float t ) {
	vec3 a = vec3(0.5, 0.5, 0.5);
	vec3 b = vec3(0.5, 0.5, 0.5);
	vec3 c = vec3(1.0, 1.0, 1.0);
	vec3 d = vec3(0.263,0.416,0.557);

	return a + b*cos( 6.28318*(c*t+d) );
}

void main() {
	fragColor = vec4(0);
	return;

	vec2 fragCoord = gl_FragCoord.xy;

	vec2 worldPos = (gl_FragCoord.xy - iResolution * 0.5) / uZoom - uCenter;
	vec2 minBound = vec2(-60.0, -40.0);
	vec2 maxBound = vec2( 60.0,  40.0);
	bool inside = all(greaterThanEqual(worldPos, minBound)) && all(lessThanEqual(worldPos, maxBound));
	if (inside) {
		fragColor = vec4(0.4, 0.4, 0.4, 1);
		return;
	}

//	vec2 uv = (fragCoord-(iResolution.xy/2.))/iResolution.x;
//	vec3 ro = vec3(0.,0.,-50.);
//	ro.xz = rotate(ro.xz,iTime);
//	vec3 cf = normalize(-ro);
//	vec3 cs = normalize(cross(cf,vec3(0.,1.,0.)));
//	vec3 cu = normalize(cross(cf,cs));
//	
//	vec3 uuv = ro+cf*3. + uv.x*cs + uv.y*cu;
//	
//	vec3 rd = normalize(uuv-ro);
//	
//	vec4 col = rm(ro,rd);
//
//	fragColor = vec4(col.rgb, 0.1);

	vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
	vec2 uv0 = uv;
	vec3 finalColor = vec3(0.0);

	for (float i = 0.0; i < 4.0; i++) {
		uv = fract(uv * 1.5) - 0.5;

		float d = length(uv) * exp(-length(uv0));

		vec3 col = palette_b(length(uv0) + i*.4 + iTime*.4);

		d = sin(d*8. + iTime)/8.;
		d = abs(d);

		d = pow(0.01 / d, 1.2);

		finalColor += col * d;
	}

	fragColor = clamp(mix(vec4(finalColor, 1.0), vec4(0,0,0,1), 0.9), 0.0, 0.075);
}