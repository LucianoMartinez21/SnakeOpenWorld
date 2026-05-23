#version 330 core

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;   // raylib's default texture slot
uniform sampler2D palette;

uniform float screen_height;
uniform float amplitude;
uniform float frequency;
uniform float speed;
uniform float amplitude_vertical;
uniform float frequency_vertical;
uniform float speed_vertical;
uniform vec2 scroll_direction;
uniform float scrolling_speed;
uniform int enable_palette_cycling;  // raylib doesn't support bool uniforms; use int
uniform float palette_speed;
uniform float TIME;

void main()
{
    vec2 UV = fragTexCoord;

    float diff_x = amplitude * sin((frequency * UV.y) + (speed * TIME));
    float diff_y = amplitude_vertical * sin((frequency_vertical * UV.y) + (speed_vertical * TIME));
    vec2 scroll = scroll_direction * TIME * scrolling_speed;

    vec4 tex = texture(texture0, vec2(UV.x + diff_x, UV.y + diff_y) + scroll);
    float palette_swap = mod(tex.r - TIME * palette_speed, 1.0);

    vec4 COLOR;
    if (enable_palette_cycling == 1)
    {
        COLOR = vec4(texture(palette, vec2(palette_swap, 0.0)).rgb, tex.a);
    }
    else
    {
        COLOR = tex;
    }

    // Scanline effect
    COLOR = mix(vec4(0.0), COLOR, float(int(UV.y * screen_height) % 2));

    finalColor = COLOR * fragColor;
}
