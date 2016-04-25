//GBUFFER
Texture2D diffuseTex			 : register(t0);
Texture2D normalTex				 : register(t1);
Texture2D specularTex			 : register(t2);
Texture2D glowTex				 : register(t3);
//Texture2D shadowTex				 : register(t4);
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
	float4 lightPosition;
	float4 lightColor;
	float intensity;
	float3 pad;
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
	float4 glowRes		: SV_Target5;
};

//Vertex shader
GBUFFER_VS_OUT GBUFFER_VS_main(GBUFFER_VS_IN input)
{
	GBUFFER_VS_OUT output;

	output.Pos = float4(input.Pos, 1.0f);
	output.Normal = input.Normal;
	output.Uv = input.Uv;
	output.BiTangent.xy = input.BiTangent;                    //z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)
	output.Tangent.xy = input.Tangent;                    //z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)

	output.BiTangent.z = (1 - length(input.BiTangent));
	output.Tangent.z = (1 - length(input.Tangent));

	normalize(output.BiTangent);
	normalize(output.Tangent);

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

	float4 ambientValue = float4(1, 1, 1, 1);
	float4 textureSample;
	if (diffuseMap)
	{
		textureSample = diffuseTex.Sample(samplerTypeState, input.Uv);
		output.diffuseRes = textureSample;
	}
	else
	{
		//textureSample = float4(0.6, 0.2, 0.9, 1.0);
		output.diffuseRes = col;
	}


	float4 normalSample;
	if (normalMap)
	{
		float4 texColor;
		float4 norMap;
		float3 Normal;
		float3 lightDirection;
		float lightIntensity;

		norMap = normalTex.Sample(samplerTypeState, input.Uv);

		norMap = (norMap*2.0f) - 1.0f;

		norMap.z = (norMap.z * -1);

		Normal = (norMap.x * input.Tangent) + (norMap.y * input.BiTangent) + (norMap.z * input.Normal);
		Normal = normalize(Normal);

		lightDirection = (float3(-1, -1, 1) - input.wPos.xyz); //flaot 3 is lightDir

		lightIntensity = saturate(dot(Normal, lightDirection));

		normalSample = saturate(ambientValue * lightIntensity);
		output.normalRes = normalSample;
	}
	else
	{
		normalSample = float4(input.Normal, 1);
		output.normalRes = normalSample;
	}

	float4 specularSample;
	if (specularMap)
	{
		specularSample.rgba = float4(0, 0, 0, 0);
		specularSample.r = diffuseTex.Sample(samplerTypeState, input.Uv).a;
		output.specularRes = specularSample;
	}
	else
	{
		specularSample.rgba = float4(0, 0, 0, 0);
		output.specularRes = specularSample;
	}

	float4 glowSample;
	if (glowMap)
	{
		glowSample = glowTex.Sample(samplerTypeState, input.Uv);
		output.glowRes = glowSample;
	}
	else
	{
		glowSample = float4 (0, 0, 0, 0);
		output.glowRes = glowSample;
	}

	////shadowmap stuff
	//float4 shadowSample = float4(1, 1, 1, 1);
	//float SMAP_SIZE = 1024.0;
	//for (int i = 0; i < shadowMapAmount; i++)
	//{
	//	
	//	float bias;
	//	float2 projectTexCoord;
	//	float depthValue;
	//	float lightDepthValue;
	//	float lightIntensity;
	//	float4 lightPos;
	//	

	//	bias = 0.00175f;

	//	lightPos				 = mul(input.wPos, view);
	//	lightPos				 = mul(lightPos, projection);

	//	projectTexCoord.x		 = lightPos.x / lightPos.w;
	//	projectTexCoord.y		 = lightPos.y / lightPos.w;

	//	lightDepthValue			 = lightPos.z / lightPos.w;

	//	projectTexCoord.x		 = projectTexCoord.x * 0.5f + 0.5f;
	//	projectTexCoord.y		 = projectTexCoord.y * -0.5f + 0.5f;

	//	depthValue = shadowTex.Sample(samplerTypeState, projectTexCoord.xy).r + bias;

	//	float dx = 1.0f / SMAP_SIZE;
	//	float s0 = (shadowTex.Sample(samplerTypeState, projectTexCoord).r						 + bias < lightDepthValue) ? 0.0f : 1.0f;
	//	float s1 = (shadowTex.Sample(samplerTypeState, projectTexCoord	 + float2(dx, 0.0f)).r	 + bias < lightDepthValue) ? 0.0f : 1.0f;
	//	float s2 = (shadowTex.Sample(samplerTypeState, projectTexCoord	 + float2(0.0f, dx)).r	 + bias < lightDepthValue) ? 0.0f : 1.0f;
	//	float s3 = (shadowTex.Sample(samplerTypeState, projectTexCoord	 + float2(dx, dx)).r	 + bias < lightDepthValue) ? 0.0f : 1.0f;

	//	float2 texelpos = projectTexCoord * SMAP_SIZE;
	//	float2 lerps = frac(texelpos);
	//	float shadowcooef = lerp(lerp(s0, s1, lerps.x), lerp(s2, s3, lerps.x), lerps.y);

	//	shadowSample = shadowSample * shadowcooef;
	//}
	//output.shadowRes = shadowSample;
	float depth = input.Pos.z / input.Pos.w;
	output.depthRes = float4(depth, depth, depth, depth);

	output.depthRes = saturate(output.depthRes * 4);
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

	unsigned int lightAmt = 1;

	for (unsigned int i = 0; i < lightAmt; i++)
	{
		//mul with lights matrices
		//output.position = mul(output.position, worldMatrix);
		//output.position = mul(output.position, view);
		//output.position = mul(output.position, projection);

		output.position = float4(input.Pos, 1);
	}



	



	return output;
}






