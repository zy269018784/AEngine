#include "D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"

#include <d3d12.h>


void STDMETHODCALLTYPE D3D12CommandBuffer::ClearRenderTargetView(
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
    _In_  const FLOAT ColorRGBA[4],
    _In_  UINT NumRects,
    _In_reads_(NumRects)  const D3D12_RECT* pRects)
{
    Handle->ClearRenderTargetView(RenderTargetView, ColorRGBA, NumRects, pRects);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::OMSetRenderTargets(
    _In_  UINT NumRenderTargetDescriptors,
    _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors,
    _In_  BOOL RTsSingleHandleToDescriptorRange,
    _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor)
{
    Handle->OMSetRenderTargets(NumRenderTargetDescriptors, pRenderTargetDescriptors, RTsSingleHandleToDescriptorRange, pDepthStencilDescriptor);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::SetGraphicsRootSignature(_In_opt_ ID3D12RootSignature* pRootSignature)
{
    Handle->SetGraphicsRootSignature(pRootSignature);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::RSSetViewports(_In_ UINT NumViewports, _In_reads_(NumViewports) const D3D12_VIEWPORT* pViewports)
{
    Handle->RSSetViewports(NumViewports, pViewports);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::RSSetScissorRects(_In_ UINT NumRects, _In_reads_(NumRects) const D3D12_RECT* pRects)
{
    Handle->RSSetScissorRects(NumRects, pRects);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::IASetPrimitiveTopology(_In_ D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology)
{
    Handle->IASetPrimitiveTopology(PrimitiveTopology);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::IASetVertexBuffers(_In_ UINT StartSlot, _In_ UINT NumViews, _In_reads_opt_(NumViews) const D3D12_VERTEX_BUFFER_VIEW* pViews)
{
    Handle->IASetVertexBuffers(StartSlot, NumViews, pViews);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::DrawInstanced(_In_ UINT VertexCountPerInstance, _In_ UINT InstanceCount, _In_ UINT StartVertexLocation, _In_ UINT StartInstanceLocation)
{
    Handle->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::DrawIndexedInstanced(_In_ UINT IndexCountPerInstance, _In_ UINT InstanceCount, _In_ UINT StartIndexLocation, _In_ INT BaseVertexLocation, _In_ UINT StartInstanceLocation)
{
    Handle->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::ResourceBarrier(_In_ UINT NumBarriers, _In_reads_(NumBarriers) const D3D12_RESOURCE_BARRIER* pBarriers)
{
    Handle->ResourceBarrier(NumBarriers, pBarriers);
}

HRESULT STDMETHODCALLTYPE D3D12CommandBuffer::Close(void)
{
    return Handle->Close();
}

HRESULT STDMETHODCALLTYPE D3D12CommandBuffer::Reset(_In_ ID3D12CommandAllocator* pAllocator, _In_opt_ ID3D12PipelineState* pInitialState)
{
    return Handle->Reset(pAllocator, pInitialState);
}

void STDMETHODCALLTYPE D3D12CommandBuffer::ClearState(_In_opt_ ID3D12PipelineState* pPipelineState)
{
    Handle->ClearState(pPipelineState);
}
