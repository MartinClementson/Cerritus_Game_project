Texture2D diffuseTex			 : register(t0);
SamplerState linearSampler		 : register(s0);

cbuffer UV                       : register(b3)
{
	float enemyoffsetX;
	float3 padEnemy;
	float waveoffsetX;
	float3 padWave;
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
	//output.pos = input.pos;
	float2 UV;
	if (waveoffsetX >= 0.0f)
	{
		output.pos = input.pos;
		UV.x = input.uv.x + waveoffsetX;
		UV.y = input.uv.y;
		output.uv = UV;
		return output;
	}
	else if(enemyoffsetX >= 0.0f)
	{
		output.pos = input.pos;
		UV.x = input.uv.x + enemyoffsetX; //+ 0.026f;
		UV.y = input.uv.y;
		//output.uv.y = input.uv.y;
		//output.uv.x += input.uv.x;
		output.uv = UV;

		return output;
	}
	else
	{
		output.pos = input.pos;
		UV.x = input.uv.x; //+ 0.026f;
		UV.y = input.uv.y;
		//output.uv.y = input.uv.y;
		//output.uv.x += input.uv.x;
		output.uv = UV;

		return output;
	}
	
}

float4 PS_main(VS_OUT input) : SV_TARGET
{

	//float4 color = (0.0f, 0.0f, 0.0f, 1.0f);

	//kolla alpha

	float4 txSample = diffuseTex.Sample(linearSampler, input.uv);


	clip(txSample.a < 0.1f ? -1 : 1);



	return txSample;
}