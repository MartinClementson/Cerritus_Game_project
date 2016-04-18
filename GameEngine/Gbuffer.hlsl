

struct VS_IN
{
	float3 Pos		: POSITION;
	float2 Uv		: TEXCOORD0;
	float3 Normal	: NORMAL;
	float3 Tangent	: TANGENT;
};

struct VS_OUT
{

	float4 Pos		 : SV_POSITION;
	float2 Uv		 : TEXCOORD0;
	float3 Normal	 : NORMAL;
	float3 Tangent	 : TANGENT;

};

Vertex shader
VS_OUT VS_main(VS_IN input)
{
	VS_OUT output;
	output.Pos = float4(input.Pos, 1.0f);
	output.Uv = input.Uv;
	output.Normal = input.Normal;
	output.Tangent = input.Tangent;

	return output;
}

struct GS_OUT
{
	float4 Pos			: SV_POSITION;
	float2 Uv			: TEXCOORD0;
	float3 Normal		: NORMAL;
	float4 wPos			: WORLDPOS;
	float3 camPos		: CAMERAPOS;
	float3 Tangent		: TANGENT;

};

[maxvertexcount(3)]
Geometry shader!
void GS_main(
	triangle VS_OUT input[3],
	inout TriangleStream< GS_OUT > output)
{
	for (uint i = 0; i < 3; i++)
	{
		GS_OUT element;
		element.Pos = input[i].Pos;

		output.Append(element);
	}


}

//GBUFFER

struct GBUFFER_SHADOWDEPTH_VS_OUT
{
	float4 position		: SV_POSITION;
};


GBUFFER_SHADOWDEPTH_VS_OUT GBUFFER_SHADOWDEPTH_VS_main(VS_IN input)
{
	GBUFFER_SHADOWDEPTH_VS_OUT output = (GBUFFER_SHADOWDEPTH_VS_OUT)0;

	output.position = float4(input.pos, 1);

	//mul with lights matrices
	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	return output;
}

struct GBUFFER_PS_OUT
{
	float4 diffuseRes	: SV_Target0;
	float4 specularRes	: SV_Target1;
	float4 normalRes	: SV_Target2;
	float4 depthRes		: SV_Target3;
	float4 shadowRes	: SV_Target4;
};
GBUFFER_PS_OUT GBUFFER_PS_main(GS_OUT input)
{
	GBUFFER_PS_OUT output = (GBUFFER_PS_OUT)0;

	//DO STYFF

	return output;
}





