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


SamplerState SampleType;

Texture2D diffuseTexture	 : register(t0);
Texture2D specularTexture	 : register(t1);
Texture2D normalTexture		 : register(t2);
Texture2D depthTexture		 : register(t3);
//Texture2D shadowTexture		 : register(t4);
Texture2DArray shadowTex	: register(t6);



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

		depthValue = shadowTex.Sample(SampleType, float3(projectTexCoord.xy, i)).r + bias;

		//float tempSample = shadowTex.Sample(samplerTypeState, float3(projectTexCoord, i)).r

		float dx = 1.0f / SMAP_SIZE;
		float s0 = (shadowTex.Sample(SampleType, float3(projectTexCoord, i)).r + bias < lightDepthValue) ? 0.0f : 1.0f;
		float s1 = (shadowTex.Sample(SampleType, float3(projectTexCoord, i) + float3(dx, 0.0f, 0.0f)).r + bias < lightDepthValue) ? 0.0f : 1.0f;
		float s2 = (shadowTex.Sample(SampleType, float3(projectTexCoord, i) + float3(0.0f, dx, 0.0f)).r + bias < lightDepthValue) ? 0.0f : 1.0f;
		float s3 = (shadowTex.Sample(SampleType, float3(projectTexCoord, i) + float3(dx, dx, 0.0f)).r + bias < lightDepthValue) ? 0.0f : 1.0f;

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
	float3 ambient			= float3(0.4f,0.4f,0.4f); // Hardcoded ambient. 
	float depthSample		= depthTexture.Sample(SampleType, input.Uv).x;

	float4 depthPrepare		= mul(float4(input.Uv.x *2.0f - 1.0f, input.Uv.y * -2.0f + 1.0f, depthSample, 1.0f), invViewProjMatrix);
	
	float3 worldPos			=  depthPrepare / depthPrepare.w;


	float4 diffuseSample			= diffuseTexture.Sample(SampleType,input.Uv);
	float4 normal					= normalTexture.Sample(SampleType, input.Uv);
	//float4 shadow					= shadowTexture.Sample(SampleType, input.Uv);

	//The light ray from the vert position to the light
	//normalized to be used as a direction vector
	float3 vRay				 = normalize((float3)(lightPosition - worldPos));
							 
	float3 v				 = normalize(camPos.xyz - worldPos);				 //create a ray from the vert pos to the camera.
							 
	float3 r				 = reflect(-vRay, normal.xyz);						 //Reflect is used in the specular shading
							 
	float fDot				 = saturate(dot(vRay, normal.xyz));					 //Calculate how much of the pixel is to be lit "intensity"
							 
	float3 lightColor		 = mul(lightDiffuse.xyz,intensity);
							 
	float shinyPower		 = 20;//specularTexture.Sample(SampleType,input.Uv).r; //How much light is to be reflected
							 
	float3 KS				 = lightColor;									 //This is the color of the specularity. For now it is set as the light color
							 
	float3 specularLight	 = { KS * pow(max(dot(r,v),0.0f),shinyPower) };
							 
	float3 lightDiffuse		 = lightColor * fDot;

	float3 finalCol			 = (lightDiffuse + ambient);

	finalCol				 = diffuseSample.xyz * finalCol; // texture * (lightDiffuse + ambient)

	finalCol				 = saturate(finalCol + specularLight);

	finalCol = finalCol; //* sampleShadowStencils(worldPos);

	float4 col				 = { worldPos,1.0 };		 //depthTexture.Sample(SampleType,input.Uv);


	return col;
}





