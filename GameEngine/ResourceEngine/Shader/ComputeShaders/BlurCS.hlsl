//We made the Gaussian calculation offline and hardcoded the result.
//It would be much more demanding if we were to calculate the matrix
//each time we ran this CS
//used sigma 6 and size 7 kernel
static const float gaussianFilter[7] = {
	//These are the Weights that the neighbouring pixels will contribute to the blur


	0.133142,	0.142694,	0.148751,	0.150826,	0.148751,	0.142694,	0.133142
};

Texture2D inputTexture : register(t0);
RWTexture2D<float4> output;
//group will be [32,30,1], in the end we will get 800X600
//which is the Resolution
[numthreads(25, 20, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	//Making a location variable to read the gaussian filter
	int3 texturelocation = DTid - int3(3, 0, 0);

	//making the calculations for the final color by multiplying the sampled pixels
	//neighboring pixels with the gaussian filter to blur the final "image".
	//For example, if it's the pixel at the location [3,3]. We will first check
	//the pixel at [0,0] and multiply it by 0.000840725 (which is the first value
	//in our harcoded matrix)
	float4 finalColor = { 0.0, 0.0, 0.0, 1.0 };
	for (uint x = 0; x < 7; x++)
		finalColor += inputTexture.Load(texturelocation + int3(x, 0, 0)) * gaussianFilter[x];


	output[DTid.xy] = finalColor;
}
