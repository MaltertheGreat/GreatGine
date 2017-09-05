cbuffer GGConstantBufferPerShader : register(b0)
{
	matrix viewProjMatrix;
}

cbuffer GGConstantBufferPerMesh : register(b1)
{
	matrix worldMatrix;
}

struct VertexOutputType
{
	float4 pos : SV_POSITION;
};

VertexOutputType main(float4 pos : POSITION)
{
	VertexOutputType output;

	output.pos = pos;
	output.pos = mul(worldMatrix, output.pos);
	output.pos = mul(viewProjMatrix, output.pos);

	return output;
}