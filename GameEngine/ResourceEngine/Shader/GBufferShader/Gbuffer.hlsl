//GBUFFER
Texture2D diffuseTex			 : register(t0);
Texture2D specularTex			 : register(t1);
Texture2D normalTex				 : register(t2);
Texture2D depthTex				 : register(t3);
Texture2D shadowTex				 : register(t4);
SamplerState samplerTypeState	 : register(s0);
cbuffer cameraConstantBuffer  : register(b0)
{

	matrix view;
	matrix projection;
	float4 camPos;
	float4 mousePos;
	//float3 camLook;

};
cbuffer worldConstantBuffer : register(b1)
{
	matrix world;
};

cbuffer lightBuffer : register(b2)
{

};
cbuffer textureSampleBuffer		 : register(b3)
{
	bool diffuseMap;
	bool normalMap;
	bool specularMap;
	bool glowMap;
};

struct GBUFFER_VS_IN
{
	float3 Pos			 : POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float2 BiTangent	 : TEXCOORD2;
	float2 Tangent		 : TEXCOORD3;
};
struct GBUFFER_VS_OUT
{
	float4 Pos			 : SV_POSITION;
	float3 Normal		 : TEXCOORD0;
	float2 Uv			 : TEXCOORD1;
	float3 BiTangent	 : TEXCOORD2;
	float3 Tangent		 : TEXCOORD3;
};
struct GBUFFER_GS_OUT
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
	output.Normal = input.Normal;
	output.Uv = input.Uv;
	output.BiTangent = float3(input.BiTangent, 1.0f);	//z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)
	output.Tangent = float3(input.Tangent, 1.0f);		//z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)

	return output;
}


[maxvertexcount(3)]
//Geometry shader!
void GBUFFER_GS_main(
	triangle GBUFFER_VS_OUT input[3],
	inout TriangleStream< GBUFFER_GS_OUT > output)
{
	matrix combinedMatrix = mul(world, mul(view, projection));

	for (uint i = 0; i < 3; i++)
	{
		GBUFFER_GS_OUT element;
		element.Pos			 = mul(input[i].Pos, combinedMatrix);
		element.Normal		 = input[i].Normal;
		element.Uv			 = input[i].Uv;
		element.BiTangent	 = input[i].BiTangent;
		element.Tangent		 = input[i].Tangent;





		element.wPos		 = mul(input[i].Pos, world);
		element.camPos		 = camPos;
		element.mousePos	 = mousePos;
		output.Append(element);
	}


}

//pixel shader
GBUFFER_PS_OUT GBUFFER_PS_main(GBUFFER_GS_OUT input)
{
	GBUFFER_PS_OUT output = (GBUFFER_PS_OUT)0;


	float attenuation = 0.05;
	float4 playerPos = { input.camPos.x,0.0,input.camPos.z + 10.0f ,1.0 };


	float4 col = { 1.0,1.0,1.0,1.0 };
	float4 pixelPos = { input.wPos.x, 0.0 , input.wPos.z, 1.0 };


	float4 lightOne = { 20.0, 0.0, -20, 1.0 };
	col.y += 1.0 - saturate(abs(distance(lightOne, pixelPos) * attenuation));


	float4 lightTwo = { -20.0, 0.0, 20.0, 1.0 };
	col.z += 1.0 - saturate(abs(distance(lightTwo, pixelPos) * attenuation));


	float4 lightThree = { -20.0, 0.0, -20.0, 1.0 };
	col.xz += 1.0 - saturate(abs(distance(lightThree, pixelPos) * attenuation));


	float4 lightFour = { 20.0, 0.0,  20.0, 1.0 };
	col.xy += 1.0 - saturate(abs(distance(lightFour, pixelPos) * attenuation));


	//float dist			 = distance(playerPos.xz,pixelPos.xz);
	float dist = distance(input.mousePos.xz, pixelPos.xz);

	col.xyz -= saturate(abs(dist)	* 0.3);  //player color fade 

	col.y += saturate(input.wPos.y);			// green color, (for the objects)



	if (diffuseMap)
	{
		float3 textureSample = diffuseTex.Sample(samplerTypeState, input.Uv).xyz;
		col.xyz = textureSample;
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
	//output.position = mul(output.position, worldMatrix);
	//output.position = mul(output.position, view);
	//output.position = mul(output.position, projection);

	return output;
}






