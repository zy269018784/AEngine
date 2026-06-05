#include "D3D11RHI/D3D11Objects/CommandBuffer/D3D11CommandBuffer.h"

void D3D11CommandBuffer::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports)
{
	Handle->RSSetViewports(NumViewports, pViewports);
}

void D3D11CommandBuffer::RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects)
{
	Handle->RSSetScissorRects(NumRects, pRects);
}

void D3D11CommandBuffer::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology)
{
	Handle->IASetPrimitiveTopology(PrimitiveTopology);
}

void D3D11CommandBuffer::IASetVertexBuffers( UINT StartSlot, UINT NumBuffers,
	 ID3D11Buffer *const *ppVertexBuffers,
	 const UINT *pStrides,
	 const UINT *pOffsets)
{
	Handle->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void D3D11CommandBuffer::IASetIndexBuffer(ID3D11Buffer *pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	Handle->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}


void D3D11CommandBuffer::DrawIndexedInstanced(UINT IndexCountPerInstance,
									 UINT InstanceCount,
									 UINT StartIndexLocation,
									 INT BaseVertexLocation,
									 UINT StartInstanceLocation)
{
	Handle->DrawIndexedInstanced(IndexCountPerInstance,
								 InstanceCount,
								 StartIndexLocation,
								 BaseVertexLocation,
								 StartInstanceLocation);
}

void D3D11CommandBuffer::DrawInstanced(UINT VertexCountPerInstance,
				   UINT InstanceCount,
				   UINT StartVertexLocation,
				   UINT StartInstanceLocation)
{
	Handle->DrawInstanced(VertexCountPerInstance,
						  InstanceCount,
						  StartVertexLocation,
						  StartInstanceLocation);
}


