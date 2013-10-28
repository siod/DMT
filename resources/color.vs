cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


struct VSInput {
	float3 pos: POSITION0;
	//float3 nor: NORMAL0;
};


float4 ColorVertexShader(VSInput input): SV_POSITION
{
	// mul by WVP
    float4x4 WVP= mul(worldMatrix,viewMatrix );
    WVP = mul(WVP, projectionMatrix);
	float4 outV = mul(float4(input.pos,1.0f),WVP);
	return outV;
}
