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

	
	return output;
}


struct GS_OUT
{
	float4 Pos			: SV_POSITION;
	//float2 Uv			: TEXCOORD0;
	//float3 Normal		: NORMAL;
	float4 wPos			: WORLDPOS;
	//float3 camPos		: CAMERAPOS;
	//float3 Tangent		: TANGENT;

};

[maxvertexcount(3)]
//Geometry shader!
void GS_main(
	triangle VS_OUT input[3],
	inout TriangleStream< GS_OUT > output)
{
	//combining the matrices for simpler use, also more efficient
	matrix combinedMatrix = mul(world, mul(view, projection));

	for (uint i = 0; i < 3; i++)
	{
		GS_OUT element;
		element.Pos = mul(input[i].Pos,combinedMatrix);
		element.wPos = mul(input[i].Pos,world);
		output.Append(element);
	}


}


float4 PS_main(GS_OUT input) : SV_TARGET
{

	float4 origin = {0.0,0.0,0.0,1.0};
float4 col = {1.0,0.0,0.0,1.0};

float dist = distance(origin, input.wPos);
//col.x -= saturate((abs(input.wPos.x) + abs(input.wPos.z))*0.006);
col.x -= saturate(dist* 0.05);
col.y = saturate(input.wPos.y);



return col;
}





