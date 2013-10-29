cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


struct VSInput {
	float3 pos: POSITION0;
	float3 norm: NORMAL0;
	float2 tex: TEXCOORD0;
};
struct VSOutput {
	float4 pos: SV_POSITION;
	float3 norm: TEXCOORD0;
	float3 posW: TEXCOORD1;
};


VSOutput ColorVertexShader(VSInput input) {
	// mul by WVP
	VSOutput vout;
    float4x4 WVP= mul(worldMatrix,viewMatrix );
    WVP = mul(WVP, projectionMatrix);
	vout.pos  = mul(float4(input.pos,1.0f),WVP);
	vout.posW = mul(float4(input.pos,1.0f),worldMatrix).xyz;
	vout.norm = normalize(mul(float4(input.norm,1.0f),worldMatrix)).xyz;
	return vout;
}
