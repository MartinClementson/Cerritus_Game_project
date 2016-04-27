//GBUFFER
Texture2D diffuseTex			 : register(t0);
Texture2D normalTex				 : register(t1);
Texture2D specularTex			 : register(t2);
Texture2D glowTex				 : register(t3);
Texture2DArray shadowTex		 : register(t6);
SamplerState samplerTypeState	 : register(s0);


cbuffer cameraConstantBuffer  : register(b0)
{

	matrix view;
	matrix projection;
	matrix invViewProjMatrix;
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
	matrix lightView;
	matrix lightProjection;
	float4 lightDir;
	float4 lightDiffuse;
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

	output.Pos			 = float4(input.Pos, 1.0f);
	output.Normal		 = input.Normal;
	output.Uv			 = input.Uv;
	output.BiTangent.xy	 = input.BiTangent;						  //z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)
	output.Tangent.xy	 = input.Tangent;						  //z value NEEDS TO BE CALCULATED (1 is just a placeholder!!)

	output.BiTangent.z	 = (1 - length(input.BiTangent));
	output.Tangent.z	 = (1 - length(input.Tangent));

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
		element.Pos				 = mul(input[i].Pos, combinedMatrix);

		element.Normal			 = normalize( mul( float4(input[i].Normal,0.0f),    world ).xyz).xyz;
		element.BiTangent		 = normalize( mul(float4(input[i].BiTangent,0.0f), world ).xyz).xyz;
		element.Tangent			 = normalize( mul(float4(input[i].Tangent,0.0f),   world ).xyz).xyz;
		element.Uv				 = input[i].Uv;
		element.wPos			 = mul(input[i].Pos, world);
		element.camPos			 = camPos;
		element.mousePos		 = mousePos;

		output.Append(element);
	}


}


float3 normalToWorldSpace(float3 normalMapSample, float3 normal, float3 tangent,float3 biTangent) //Function for normal mapping  
{

	// here we build the tbn basis. to transform the sampled normal to texture space
	//then we return the normal and use it with our calculations

	//Convert from [0,1] to [-1,1]
	float3 normalT = 2.0f * normalMapSample - 1.0f;

	//Build basis
	float3 N = normal;

	//Make sure tangent is completely orthogonal to normal
	float3 T = normalize(tangent - dot(tangent, N)* N); //Read page 582
	float3 B = biTangent;						//cross(N, T); //Bitangent

							//Create the "Texture Space" matrix
	float3x3 TBN = float3x3(T, B, N);

	//Convert normal from normal map to texture space and store in input.normal

	float3 bumpedNormal = mul(normalT, TBN);

	return normalize(bumpedNormal);

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
		output.diffuseRes = float4(0.7, 0.7, 0.7, 1);
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
		norMap.xyz = normalToWorldSpace(norMap.xyz, input.Normal, input.Tangent, input.BiTangent);

		//norMap = (norMap*2.0f) - 1.0f;

		//norMap.z = (norMap.z * -1);

		//Normal = (norMap.x * input.Tangent) + (norMap.y * input.BiTangent) + (norMap.z * input.Normal);
		//Normal = normalize(Normal);

		//lightDirection = (float3(-1, -1, 1) - input.wPos.xyz); //flaot 3 is lightDir

		//lightIntensity = saturate(dot(Normal, lightDirection));

		//normalSample = saturate(ambientValue * lightIntensity);
		output.normalRes = norMap;
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
	//float tempCooef = 0;
	//float SMAP_SIZE = 2048.0;
	//uint lightAmount = 1;
	//for (uint i = 0; i < lightAmount; i++)
	//{
	//	
	//	float bias;
	//	float2 projectTexCoord;
	//	float depthValue;
	//	float lightDepthValue;
	//	float lightIntensity;
	//	float4 lightPos;
	//	

	//	////////////////BIAS IS HERE
	//	bias = 0.001f;

	//	lightPos				 = mul(input.wPos, lightView);
	//	lightPos				 = mul(lightPos, lightProjection);

	//	projectTexCoord.x		 = lightPos.x / lightPos.w;
	//	projectTexCoord.y		 = lightPos.y / lightPos.w;

	//	lightDepthValue			 = lightPos.z / lightPos.w;

	//	projectTexCoord.x		 = projectTexCoord.x * 0.5f + 0.5f;
	//	projectTexCoord.y		 = projectTexCoord.y * -0.5f + 0.5f;

	//	depthValue = shadowTex.Sample(samplerTypeState, float3(projectTexCoord.xy, i)).r + bias;

	//	//float tempSample = shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i)).r

	//	float dx = 1.0f / SMAP_SIZE;
	//	float s0 = (shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i)).r							 + bias < lightDepthValue) ? 0.0f : 1.0f;
	//	float s1 = (shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i) + float3(dx, 0.0f, 0.0f)).r	 + bias < lightDepthValue) ? 0.0f : 1.0f;
	//	float s2 = (shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i) + float3(0.0f, dx, 0.0f)).r	 + bias < lightDepthValue) ? 0.0f : 1.0f;
	//	float s3 = (shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i) + float3(dx, dx, 0.0f)).r		 + bias < lightDepthValue) ? 0.0f : 1.0f;

	//	float2 texelpos		 = projectTexCoord * SMAP_SIZE;
	//	float2 lerps		 = frac(texelpos);
	//	float shadowcooef	 = lerp(lerp(s0, s1, lerps.x), lerp(s2, s3, lerps.x), lerps.y);

	//	tempCooef			+= shadowcooef;
	//}
	//shadowSample			= shadowSample * tempCooef;
	//shadowSample			= saturate(shadowSample);
	//output.shadowRes		= shadowSample;

	float depth = input.Pos.z / input.Pos.w;
	output.depthRes = float4(depth, depth, depth, 1.0);

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
	matrix combinedMatrix = mul(world, mul(lightView, lightProjection));

		output.position = float4(input.Pos, 1);

		output.position = mul(output.position, combinedMatrix);

	return output;
}






