

//GBUFFER
Texture2D diffuseTex			 : register(t0);
Texture2D normalTex				 : register(t1);
Texture2D specularTex			 : register(t2);
Texture2D glowTex				 : register(t3);
Texture2DArray shadowTex		 : register(t6);

SamplerState linearSampler		 : register(s0);
SamplerState pointSampler		 : register(s1);

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

cbuffer textureSampleBuffer		 : register(b2)
{
	bool diffuseMap;
	bool normalMap;
	bool specularMap;
	bool glowMap;
};



struct BILLBOARD_VS_IN
{
	float3 worldPos		 : POSITION;
	float2 height		 : HEIGHT;
	float2 width		 : WIDTH;
};
struct BILLBOARD_VS_OUT
{
	float4 worldPos		 : SV_POSITION;
	float2 height		 : HEIGHT;
	float2 width		 : WIDTH;
};

struct BILLBOARD_GS_OUT
{
	float4 Pos			: SV_POSITION;
	float3 Normal		: TEXCOORD0;
	float2 Uv			: TEXCOORD1;
	float3 BiTangent	: TEXCOORD2;
	float3 Tangent		: TEXCOORD3;


	float4 wPos			: WORLDPOS;
	float4 camPos		: CAMERAPOS;
	float4 mousePos		: MOUSEPOS;
};

struct BILLBOARD_PS_OUT
{
	float4 diffuseRes	: SV_Target0;
	float4 specularRes	: SV_Target1;
	float4 normalRes	: SV_Target2;
	float4 depthRes		: SV_Target3;
	float4 positionRes	: SV_Target4;
	float4 glowRes		: SV_Target5;
};



BILLBOARD_VS_OUT BILLBOARD_VS(BILLBOARD_VS_IN input )
{
	BILLBOARD_VS_OUT output;
	output.worldPos		= float4(input.worldPos,1.0f);
	output.width		= input.width;
	output.height		= input.height;

	return output;
}



[maxvertexcount(3)]

void BILLBOARD_GS(triangle BILLBOARD_VS_OUT input[3],
	inout TriangleStream< BILLBOARD_GS_OUT > output)
{
	for (uint i = 0; i < 3; i++)
	{


		BILLBOARD_GS_OUT element;
		//element.Pos			 = mul(input[i].Pos, view);
		//element.Pos			 = mul(input[i].Pos, projection);
		element.Pos = input[i].worldPos;
		element.Normal		= float3 (1.0f, 1.0f, 1.0f);
		element.BiTangent	= float3 (1.0f, 1.0f, 1.0f);
		element.Tangent		= float3 (1.0f, 1.0f, 1.0f);
		element.Uv = float2 (1.0f, 1.0f);
		element.wPos = input[i].worldPos;
		element.camPos = camPos;
		element.mousePos = mousePos;

		output.Append(element);
	}

}



BILLBOARD_PS_OUT BILLBOARD_PS(BILLBOARD_GS_OUT input)
{

	BILLBOARD_PS_OUT output;

	return output;
}