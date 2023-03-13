#version 330 core

// This shader is designed to work with "triangle.vert" and it receives an
// interpolated varying which represents the vertex color.

in Varyings {
    vec3 color;
} fs_in;

out vec4 frag_color;

uniform vec4 red;
uniform vec4 green;
uniform vec4 blue;
// currently the shader just returns the interpalated color varying.
// However, we want to mix the color channels around. We can do this using a 
// color matrix which we will send to the shader as 3 uniforms: red, green, blue.
// Each of these 3 variables will be a vec4. To apply the channel mixing for a
// certain channel (e.g. red), we apply this linear transformation:
// frag_color.r = red.r * fs_in.color.r + red.g + fs_in.color.g + red.b + fs_in.color.b + red.a;
// However, this line is too long to write, so we can simplify it using a dot product
// (which is defined in the "dot" function).

//TODO: (Req 1) Finish this shader and apply the channel mixing using the "dot" function.

void main(){
    // frag_color = vec4(fs_in.color,1.0);
    // frag_color.r = red.r * fs_in.color.r + red.g + fs_in.color.g + red.b + fs_in.color.b + red.a;
    // frag_color.g = green.r + fs_in.color.r + green.g + fs_in.color.g * green.b + fs_in.color.b + green.a;
    // frag_color.b = blue.r + fs_in.color.r + blue.g + fs_in.color.g + blue.b * fs_in.color.b + blue.a;
    frag_color.r=dot(vec4(fs_in.color,1.0),red);
    frag_color.g=dot(vec4(fs_in.color,1.0),green);
    frag_color.b=dot(vec4(fs_in.color,1.0),blue);
    frag_color.a=1.0;
}