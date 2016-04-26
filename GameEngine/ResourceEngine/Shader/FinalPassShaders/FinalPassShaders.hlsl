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
Texture2D shadowTexture		 : register(t4);

float4 PS_main(VS_OUT input) : SV_TARGET
{
	float3 ambient			= float3(0.4f,0.4f,0.4f); // Hardcoded ambient. 
	float depthSample		= depthTexture.Sample(SampleType, input.Uv).x;

	float4 depthPrepare = mul(float4(input.Uv.x *2.0f - 1.0f, input.Uv.y * -2.0f + 1.0f, depthSample, 1.0f), invViewProjMatrix);
	float3 worldPos = depthPrepare.xyz / depthPrepare.w;




	float4 diffuseSample			= diffuseTexture.Sample(SampleType,input.Uv);
	float4 normal					= normalTexture.Sample(SampleType, input.Uv);
	float4 shadow					= shadowTexture.Sample(SampleType, input.Uv);

	//The light ray from the vert position to the light
	//normalized to be used as a direction vector
	float3 vRay				= normalize((float3)(lightPosition.xyz - worldPos));

	float3 v				= normalize(camPos.xyz - worldPos);		 //create a ray from the vert pos to the camera.
	
	float3 r				= reflect(-vRay, normal);						 //Reflect is used in the specular shading
	
	float fDot				= saturate(dot(vRay, normal));					 //Calculate how much of the pixel is to be lit "intensity"

	float3 lightColor		= mul(lightDiffuse.xyz,intensity);

	float shinyPower		= 20;//specularTexture.Sample(SampleType,input.Uv).r; //How much light is to be reflected

	float3 KS				= lightColor;									 //This is the color of the specularity. For now it is set as the light color

	float3 specularLight	= { KS * pow(max(dot(r,v),0.0f),shinyPower) };
	


	float3 diffuse			 = lightColor * fDot;


	float3 finalCol			 = (diffuse + ambient);
	finalCol = diffuseSample * finalCol; // texture * (diffuse + ambient)
	finalCol = saturate(finalCol + specularLight);

	finalCol = finalCol * shadow.r;


	float4 col = { finalCol.xyz,1.0 };		 //depthTexture.Sample(SampleType,input.Uv);


	return col;
}





