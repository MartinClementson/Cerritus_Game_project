

struct VS_IN
{
	float3 Pos		: POSITION;
	//float2 Uv		: TEXCOORD0;
	//float3 Normal	: NORMAL;
	//float3 Tangent	: TANGENT;
};

struct VS_OUT
{

	float4 Pos		 : SV_POSITION;
	//float2 Uv		 : TEXCOORD0;
	//float3 Normal	 : NORMAL;
	//float3 Tangent	 : TANGENT;

};

//Vertex shader
VS_OUT VS_main( VS_IN input)
{
	VS_OUT output;
	output.Pos = float4(input.Pos, 1.0f);
	//output.Uv = input.Uv;
	//output.Normal = input.Normal;
	//output.Tangent = input.Tangent;
	
	return output;
}


cbuffer cameraConstantBuffer  : register(b0)
{

	matrix view;
	matrix projection;
	float4 camPos;
	//float3 camLook;

};
cbuffer worldConstantBuffer : register(b1)
{
	matrix world;
};
struct GS_OUT
{
	float4 Pos			: SV_POSITION;
	//float2 Uv			: TEXCOORD0;
	//float3 Normal		: NORMAL;
	//float4 wPos			: WORLDPOS;
	//float3 camPos		: CAMERAPOS;
	//float3 Tangent		: TANGENT;

};

[maxvertexcount(3)]
//Geometry shader!
void GS_main(
	triangle VS_OUT input[3],
	inout TriangleStream< GS_OUT > output)
{
	for (uint i = 0; i < 3; i++)
	{
		GS_OUT element;
		element.Pos = mul(input[i].Pos,mul(view,projection));
	
		output.Append(element);
	}


}


float4 PS_main(GS_OUT input) : SV_TARGET
{

float4 col = {1.0,0.0,0.0,1.0};

return col;
}





