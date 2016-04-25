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


float4 PS_main(VS_OUT input) : SV_TARGET
{


float4 col = diffuseTexture.Sample(SampleType,input.Uv);


return col;
}





