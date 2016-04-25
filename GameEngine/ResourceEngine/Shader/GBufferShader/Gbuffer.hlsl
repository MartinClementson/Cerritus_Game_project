//GBUFFER
Texture2D diffuseTex			 : register(t0);
Texture2D specularTex			 : register(t1);
Texture2D normalTex				 : register(t2);
Texture2D depthTex				 : register(t3);
Texture2D shadowTex				 : register(t4);
SamplerState samplerTypeState	 : register(s0);
cbuffer textureSampleBuffer		 : register(b3)
{
	bool diffuseMap;
	bool normalMap;
	bool specularMap;
	bool glowMap;
};

struct GBUFFER_VS_IN
{
	float3 Pos		: POSITION;
	float2 Uv		: TEXCOORD0;
	float3 Normal	: NORMAL;
	float3 Tangent	: TANGENT;
};
struct GBUFFER_VS_OUT
{

	float4 Pos		 : SV_POSITION;
	float2 Uv		 : TEXCOORD0;
	float3 Normal	 : NORMAL;
	float3 Tangent	 : TANGENT;

};
struct GBUFFER_GS_OUT
{
	float4 Pos			: SV_POSITION;
	float2 Uv			: TEXCOORD0;
	float3 Normal		: NORMAL;
	float4 wPos			: WORLDPOS;
	float3 camPos		: CAMERAPOS;
	float3 Tangent		: TANGENT;

};
struct GBUFFER_PS_OUT
{
	float4 diffuseRes	: SV_Target0;
	float4 specularRes	: SV_Target1;
	float4 normalRes	: SV_Target2;
	float4 depthRes		: SV_Target3;
	float4 shadowRes	: SV_Target4;
};

//Vertex shader
GBUFFER_VS_OUT GBUFFER_VS_main(GBUFFER_VS_IN input)
{
	GBUFFER_VS_OUT output;
	output.Pos = float4(input.Pos, 1.0f);
	output.Uv = input.Uv;
	output.Normal = input.Normal;
	output.Tangent = input.Tangent;

	return output;
}


[maxvertexcount(3)]
//Geometry shader!
void GBUFFER_GS_main(
	triangle GBUFFER_VS_OUT input[3],
	inout TriangleStream< GBUFFER_GS_OUT > output)
{
	for (uint i = 0; i < 3; i++)
	{
		GBUFFER_GS_OUT element;
		element.Pos = input[i].Pos;

		output.Append(element);
	}


}

//pixel shader
GBUFFER_PS_OUT GBUFFER_PS_main(GBUFFER_GS_OUT input)
{
	GBUFFER_PS_OUT output = (GBUFFER_PS_OUT)0;

	if (diffuseMap)
	{
	
	}
	else
	{

	}



	if (normalMap)
	{

	}
	else
	{

	}


	if (specularMap)
	{

	}
	else
	{

	}


	if (glowMap)
	{

	}
	else
	{
	
	}

	//DO STYFF

	return output;
}

//GBUFFER shadowmap shader
struct GBUFFER_SHADOWDEPTH_VS_OUT
{
	float4 position		: SV_POSITION;
};
GBUFFER_SHADOWDEPTH_VS_OUT GBUFFER_SHADOWDEPTH_VS_main(GBUFFER_VS_IN input)
{
	GBUFFER_SHADOWDEPTH_VS_OUT output = (GBUFFER_SHADOWDEPTH_VS_OUT)0;

	output.position = float4(input.Pos, 1);

	//mul with lights matrices
	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	return output;
}






