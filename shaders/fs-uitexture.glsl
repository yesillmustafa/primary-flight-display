#version 100
precision mediump float;
varying vec2 fragTexCoord;
uniform sampler2D textureSampler;

void main() {
    vec4 texColor = texture2D(textureSampler, fragTexCoord);
    
    // Eğer texColor'ın rengi siyaha yakınsa alfa değerini kıs
    float grayscale = dot(texColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (grayscale < 0.1) { // Eşik değeri burada ayarlanabilir
        texColor.a *= 0.3; // Alfa değeri
    }
    
    gl_FragColor = texColor;
}
