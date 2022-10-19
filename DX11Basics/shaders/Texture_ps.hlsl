Texture2D tex;
SamplerState splr;
float4 main(float2 tc : TexCoord) : SV_TARGET
{
	float4 color = tex.Sample(splr, tc);
	float avg = (color.r + color.g + color.b) / 3.0f;
	return float4(color.r, color.g, color.b, 1.0f);
}