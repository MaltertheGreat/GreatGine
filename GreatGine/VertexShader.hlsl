struct VertexOutputType
{
	float4 position : SV_POSITION;
};

VertexOutputType main(float4 pos : POSITION)
{
	VertexOutputType output;

	output.position = pos;

	return output;
}