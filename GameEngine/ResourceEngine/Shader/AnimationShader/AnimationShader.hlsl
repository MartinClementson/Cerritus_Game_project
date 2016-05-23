
cbuffer cbufferPerFrame     : register(b0)
{

	matrix view;
	matrix projection;
	matrix invViewProjMatrix;
	float4 camPos;
	float4 mousePos;
	int numPointLights;
	int numSpotLights;
	int numDirLights;
	//float3 camLook;

};

struct ANIM_VS_IN
{
	float3 Pos			 : POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float2 BiTangent	 : TEXCOORD2;
	float2 Tangent		 : TEXCOORD3;
	float4x4 worldMatrix : WORLD;
	//uint vertexID		 : SV_VertexID; <-- for animation

};


struct ANIM_VS_OUT
{
	float4 Pos			 : SV_POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float3 BiTangent	 : TEXCOORD2;
	float3 Tangent		 : TEXCOORD3;
	float4 wPos			 : WORLDPOS;
};


//Vertex shader
ANIM_VS_OUT ANIM_VS_main(ANIM_VS_IN input)
{
	ANIM_VS_OUT output;

	output.Pos = mul(float4(input.Pos, 1.0f), input.worldMatrix);
	output.wPos = output.Pos;
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);

	output.BiTangent.xy = input.BiTangent.xy;
	output.Tangent.xy = input.Tangent.xy;

	output.BiTangent.z = sqrt(1 - pow(input.BiTangent.x, 2) + pow(input.BiTangent.y, 2));
	output.Tangent.z = sqrt(1 - pow(input.Tangent.x, 2) + pow(input.Tangent.y, 2));







	output.Normal = normalize(mul(float4(input.Normal, 0.0f), input.worldMatrix).xyz).xyz;
	output.BiTangent = normalize(mul(float4(output.BiTangent, 0.0f), input.worldMatrix).xyz).xyz;
	output.Tangent = normalize(mul(float4(output.Tangent, 0.0f), input.worldMatrix).xyz).xyz;
	output.Uv = input.Uv;

	return output;
}
