//We made the Gaussian calculation offline and hardcoded the result.
//It would be much more demanding if we were to calculate the matrix
//each time we ran this CS
static const float gaussianFilter[7][7] = {
	//These are the Weights that the neighbouring pixels will contribute to the blur

	/*first row = seventh row*/
	0.000840725, 0.00301024, 0.00647097, 0.00835139, 0.00647097,
	0.00301024, 0.000840725,
	/*second row = sixth row*/
	0.00301024, 0.0107783, 0.0231695, 0.0299024, 0.0231695,
	0.0107783, 0.00301024,
	/*third row = fifth row*/
	0.00647097, 0.0231695, 0.0498063, 0.0642797, 0.0498063,
	0.0231695, 0.00647097,
	/*fourth row*/
	0.00835139, 0.0299024, 0.0642797,  0.083959, 0.0642797,
	0.0299024, 0.00835139,
	/*Fifth row = third row*/
	0.00647097, 0.0231695, 0.0498063, 0.0642797, 0.0498063,
	0.0231695, 0.00647097,
	/*sixth row = second row*/
	0.00301024, 0.0107783, 0.0231695, 0.0299024, 0.0231695,
	0.0107783, 0.00301024,
	/*seventh row = first row*/
	0.000840725, 0.00301024, 0.00647097, 0.00835139, 0.00647097,
	0.00301024, 0.000840725,
};

Texture2D inputTexture : register(t0);
RWTexture2D<float4> output;
//group will be [32,30,1], in the end we will get 800X600
//which is the Resolution
[numthreads(25, 20, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	//Making a location variable to read the gaussian filter
	int3 texturelocation = DTid - int3(3, 3, 0);

	//making the calculations for the final color by multiplying the sampled pixels
	//neighboring pixels with the gaussian filter to blur the final "image".
	//For example, if it's the pixel at the location [3,3]. We will first check
	//the pixel at [0,0] and multiply it by 0.000840725 (which is the first value
	//in our harcoded matrix)
	float4 finalColor = { 0.0, 0.0, 0.0, 1.0 };
	for (uint x = 0; x < 7; x++)
		for (uint y = 0; y < 7; y++)
			finalColor += inputTexture.Load(texturelocation + int3(x, y, 0)) * gaussianFilter[x][y];

	output[DTid.xy] = finalColor;
}