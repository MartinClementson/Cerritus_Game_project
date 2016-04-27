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
	float intensity;
};
cbuffer textureSampleBuffer : register(b3)
{	
	bool diffuseMap;
	bool normalMap;
	bool specularMap;
	bool glowMap;
};


struct VS_IN
{
	float3 Pos			 : POSITION;
	float2 Uv			 : TEXCOORD1;
};

struct VS_OUT
{

	float4 Pos			 : SV_POSITION;
	float2 Uv			 : TEXCOORD1;

};

//Vertex shader
VS_OUT VS_main( VS_IN input)
{
	VS_OUT output;
	output.Pos				 = float4(input.Pos, 1.0f);
	output.Uv				 = input.Uv;
	

	return output;
}


SamplerState linearSampler		 : register(s0);
SamplerState pointSampler		 : register(s1);

Texture2D		diffuseTexture		 : register(t0);
Texture2D		specularTexture		 : register(t1);
Texture2D		normalTexture		 : register(t2);
Texture2D		depthTexture		 : register(t3);
Texture2D		positionTexture		 : register(t4);
Texture2D		glowTexture			 : register(t5);
Texture2DArray  shadowTex			 : register(t6);

static const float SSAO_RAD = 0.005f;

float sampleShadowStencils(float4 worldPos)
{

	//shadowmap stuff
	float4 shadowSample = float4(1, 1, 1, 1);
	float tempCooef = 0;
	float SMAP_SIZE = 2048.0;
	uint lightAmount = 1;
	for (uint i = 0; i < lightAmount; i++)
	{

		float bias;
		float2 projectTexCoord;
		float depthValue;
		float lightDepthValue;
		float lightIntensity;
		float4 lightPos;


		////////////////BIAS IS HERE
		bias = 0.001f;

		lightPos = mul(worldPos, lightView);
		lightPos = mul(lightPos, lightProjection);

		projectTexCoord.x = lightPos.x / lightPos.w;
		projectTexCoord.y = lightPos.y / lightPos.w;

		lightDepthValue = lightPos.z / lightPos.w;

		projectTexCoord.x = projectTexCoord.x * 0.5f + 0.5f;
		projectTexCoord.y = projectTexCoord.y * -0.5f + 0.5f;

		depthValue = shadowTex.Sample(linearSampler, float3(projectTexCoord.xy, i)).r + bias;

		//float tempSample = shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i)).r

		float dx = 1.0f / SMAP_SIZE;
		float s0 = (shadowTex.Sample(linearSampler, float3(projectTexCoord, i)).r + bias < lightDepthValue) ? 0.0f : 1.0f;
		float s1 = (shadowTex.Sample(linearSampler, float3(projectTexCoord, i) + float3(dx, 0.0f, 0.0f)).r + bias < lightDepthValue) ? 0.0f : 1.0f;
		float s2 = (shadowTex.Sample(linearSampler, float3(projectTexCoord, i) + float3(0.0f, dx, 0.0f)).r + bias < lightDepthValue) ? 0.0f : 1.0f;
		float s3 = (shadowTex.Sample(linearSampler, float3(projectTexCoord, i) + float3(dx, dx, 0.0f)).r + bias < lightDepthValue) ? 0.0f : 1.0f;

		float2 texelpos = projectTexCoord * SMAP_SIZE;
		float2 lerps = frac(texelpos);
		float shadowcooef = lerp(lerp(s0, s1, lerps.x), lerp(s2, s3, lerps.x), lerps.y);

		tempCooef += shadowcooef;
	}
	shadowSample = shadowSample * tempCooef;
	shadowSample = saturate(shadowSample);
	return shadowSample.x;



}



float4 PS_main(VS_OUT input) : SV_TARGET
{
	float4 ambient			= float4(0.2f,0.2f,0.2f,1.0f); // Hardcoded ambient. 
	float depthSample		= depthTexture.Sample(pointSampler, input.Uv);

	float4 depthPrepare		= mul(float4(input.Uv.x *2.0f - 1.0f, input.Uv.y * -2.0f + 1.0f, depthSample, 1.0f), invViewProjMatrix);
	
	float3 worldPos			= positionTexture.Sample(pointSampler, input.Uv); //depthPrepare / depthPrepare.w;


	float4 diffuseSample			= diffuseTexture.Sample(pointSampler,input.Uv);
	float4 normal					= normalTexture.Sample(pointSampler, input.Uv);
	float4 specular					= specularTexture.Sample(pointSampler, input.Uv);
	float4 shadow					= sampleShadowStencils(float4(worldPos, 1.0f));

	//The light ray from the vert position to the light
	//normalized to be used as a direction vector
	
	float3 vRay				= (float3)(lightPosition - worldPos);
	float rayLength			= length(vRay);
	vRay					/= rayLength;

	float3 v				= normalize(camPos.xyz - worldPos);				 //create a ray from the vert pos to the camera.
							
	float3 r				= reflect(-vRay, normal.xyz);						 //Reflect is used in the specular shading
							
	float fDot				= saturate(dot(vRay, normal.xyz));					 //Calculate how much of the pixel is to be lit "intensity"
							
	float4 lightColor		= mul(lightDiffuse,intensity);
							
	float shinyPower		= 20.0f;//specularTexture.Sample(SampleType,input.Uv).r; //How much light is to be reflected
							
	float3 KS				= specular.xyz;									 //This is the color of the specularity. For now it is set as the light color
							
	float3 specularLight	= { KS * pow(max(dot(r,v),0.0f),shinyPower) };
				
	

	float4 lightDiffuse		= saturate( lightColor * fDot ) + float4(specularLight, 1.0f);
	
	float3 spotDir			= normalize(lightDir - lightPosition);

//	lightDiffuse			*= pow(max(dot(-vRay, spotDir), 0.0f), 30.0f);

	float radio			= 80.0f;
	float lightLength	= length(lightDir - worldPos);
	if (lightLength > radio)
		lightDiffuse *= 0.0;
	else
		lightDiffuse *= ((radio - lightLength) / radio);

	


	//========== Screen Space Ambient Occlusion =============
	 //quite fake. Use AO maps if possible. dis should be for objects without AO maps
	float ssao = 0.0f;

	float2 vec[8] = { 
		float2(1.0f, 0.0f),		 float2(-1.0f, 0.0f),
		float2(0.0f, 1.0f),		 float2(0.0f, -1.0f),
		float2(0.707f, 0.707f),  float2(-0.707f, -0.707f),
		float2(-0.707f, 0.707f), float2(0.707f, -0.707f), };

	[unroll]
	for (int j = 0; j < 8; j++)
	{
		for (float k = 0.0f; k < 1.01f; k += 0.5f)
		{
			float2  sampleVec = input.Uv + vec[j] * SSAO_RAD * k;
			float	ssaoDepthSample = depthTexture.Sample(pointSampler, sampleVec);
			float4  ssaoDepthPrepare = mul(float4(sampleVec.x * 2.0f - 1.0f, sampleVec.y * -2.0f + 1.0f, ssaoDepthSample, 1.0f), invViewProjMatrix);
			float3 dif = ssaoDepthPrepare.xyz / ssaoDepthPrepare.w - worldPos;
			float l = length(dif) * 0.05f;
			dif = normalize(dif);

			ssao += max(0.0f, dot(normal.xyz, dif) - 0.01f) * 1.0f / (10.0f + l);
		}
	}

	ssao = 1.0f - ssao / 16.0f;



	float4 finalCol = diffuseSample * ( ambient * ssao + (lightDiffuse * shadow) );
	finalCol.r += diffuseSample.a; //Laser point color
	finalCol = saturate(finalCol);





	return finalCol;
}





