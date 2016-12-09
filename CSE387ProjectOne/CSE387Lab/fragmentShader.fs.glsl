// Targeting version 4.2 of GLSL. 
#version 420 core

#pragma optimize(off)
#pragma debug(on)

// Declare default precision - eliminates warnings 
precision mediump float;

out vec4 fragmentColor;

in vec4 color0;
in vec2 TexCoord0;
uniform sampler2D gSampler;

flat in uint textureModeInt;


void main()
{
	// Use the texture coordinate and the sampler to get a color value
	//fragmentColor = texture2D(gSampler, TexCoord0.st);

	if(textureModeInt == 0){
		fragmentColor = color0;
	}
		
	else if(textureModeInt == 1){
		fragmentColor = texture2D(gSampler, TexCoord0.st);
	}
		
	else if(textureModeInt == 2){
		fragmentColor = texture2D(gSampler, TexCoord0.st) * color0;
	}
		
	

}