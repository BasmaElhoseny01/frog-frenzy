#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;

out vec4 frag_color;

// Vignette is a postprocessing effect that darkens the corners of the screen
// to grab the attention of the viewer towards the center of the screen

void main(){
    //TODO: (Req 11) Modify this shader to apply vignette
    // To apply vignette, divide the scene color
    // by 1 + the squared length of the 2D pixel location the NDC space
    // Hint: remember that the NDC space ranges from -1 to 1
    // while the texture coordinate space ranges from 0 to 1
    // We have the pixel's texture coordinate, how can we compute its location in the NDC space?

    vec2 map = vec2((2 * tex_coord) - 1);
    // get the texture coordinates to NDC space
    frag_color = texture(tex, tex_coord);  
    frag_color = frag_color/(1+(map.x*map.x)+(map.y*map.y));
    // divide the scene color by the eqn attached to apply vignette
}