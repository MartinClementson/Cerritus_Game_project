cbuffer lightMatrices : register(b0)
{
	matrix lightWorldMatrix;
	matrix lightView;
	matrix lightProjection;
};
cbuffer cameraMatrices : register(b1)
{
	matrix camWorldMatrix;
	matrix camView;
	matrix camProjection;
};
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

//Vertex shader
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
//Geometry shader!
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
Texture2D diffuseTex	: register(t0);
Texture2D specularTex	: register(t1);
Texture2D normalTex		: register(t2);
Texture2D depthTex		: register(t3);
Texture2D shadowTex		: register(t4);

SamplerState samplerTypeState : register(s0);

struct GBUFFER_SHADOWDEPTH_VS_OUT
{
	float4 position		: SV_POSITION;
};


GBUFFER_SHADOWDEPTH_VS_OUT GBUFFER_SHADOWDEPTH_VS_main(VS_IN input)
{
	GBUFFER_SHADOWDEPTH_VS_OUT output = (GBUFFER_SHADOWDEPTH_VS_OUT)0;

	output.position = float4(input.Pos, 1);

	//mul with lights matrices
	output.position = mul(output.position, lightWorldMatrix);
	output.position = mul(output.position, lightView);
	output.position = mul(output.position, lightProjection);

	return output;
}

struct GBUFFER_PS_OUT
{
	float4 diffuseRes	: SV_Target0;
	float4 specularRes	: SV_Target1;
	float4 glossRes		: SV_Target2;
	float4 normalRes	: SV_Target3;
	float4 depthRes		: SV_Target4;
	float4 shadowRes	: SV_Target5;
};
GBUFFER_PS_OUT GBUFFER_PS_main(GS_OUT input)
{
	GBUFFER_PS_OUT output = (GBUFFER_PS_OUT)0;
	float4 color = float4(1,1,1,1);


	//diffuse
	output.diffuseRes = diffuseTex.Sample(samplerTypeState, input.Uv);
	output.diffuseRes = output.diffuseRes * color;
	output.diffuseRes = saturate(output.diffuseRes);

	//specular
	output.specularRes = specularTex.Sample(samplerTypeState, input.Uv);
	output.specularRes = saturate(output.specularRes);
	
	//gloss

	//normal
	
	//depth
	
	//shadow

	return output;
}





