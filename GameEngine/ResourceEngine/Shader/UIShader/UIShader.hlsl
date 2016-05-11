Texture2D diffuseTex			 : register(t0);
SamplerState linearSampler		 : register(s0);

cbuffer UV                       : register(b0)
{
	float enemyOffsetX;
	float waveOffsetX;
};

struct VS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;

};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output;
	output.pos = input.pos;
	float2 UV;
	UV.x = input.uv.x; //+ 0.026f;
	UV.y = input.uv.y;
	//output.uv.y = input.uv.y;
	//output.uv.x += input.uv.x;
	output.uv = UV;
	
	return output;
}

float4 PS_main(VS_OUT input) : SV_TARGET
{

	//float4 color = (0.0f, 0.0f, 0.0f, 1.0f);

	//kolla alpha

	float4 txSample = diffuseTex.Sample(linearSampler, input.uv);


	clip(txSample.a < 0.1f ? -1 : 1);



	return txSample;
}