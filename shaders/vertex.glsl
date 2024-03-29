#version 330 core

const int MAX_JOINTS = 50;

layout(location = 0) in vec3	vertexPosition;
layout(location = 1) in vec3	vertexNormal;
layout(location = 2) in vec2	vertexUV;
layout(location = 3) in vec4	vertexJointIncides;
layout(location = 4) in vec4	vertexWeights;

out vec3	fragmentNormal;
out vec2	fragmentUV;
out vec3	frsgmrntPosition;

uniform bool	isAnimated;
uniform mat4	jointTransforms[MAX_JOINTS];
uniform mat4	transformation;
uniform mat4	view;

void main() {
	mat4 skinMatrix = mat4(1.0);

	if (isAnimated) {
		skinMatrix =	vertexWeights.x * jointTransforms[int(vertexJointIncides.x)] +
						vertexWeights.y * jointTransforms[int(vertexJointIncides.y)] +
						vertexWeights.z * jointTransforms[int(vertexJointIncides.z)] +
						vertexWeights.w * jointTransforms[int(vertexJointIncides.w)];
	}

	mat4 transform = transformation * skinMatrix;
	vec4 position = transform * vec4(vertexPosition, 1.0);
	gl_Position = view * position;

	fragmentNormal = (transform * vec4(vertexNormal, 0.0)).xyz;
	fragmentUV = vertexUV;
	frsgmrntPosition =  position.xyz;
}