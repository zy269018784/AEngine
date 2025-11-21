#include "D3D12Objects/Queue/D3D12Queue.h"

// 实现部分
void STDMETHODCALLTYPE D3D12Queue::UpdateTileMappings(
    _In_  ID3D12Resource* pResource,
    UINT NumResourceRegions,
    _In_reads_opt_(NumResourceRegions)  const D3D12_TILED_RESOURCE_COORDINATE* pResourceRegionStartCoordinates,
    _In_reads_opt_(NumResourceRegions)  const D3D12_TILE_REGION_SIZE* pResourceRegionSizes,
    _In_opt_  ID3D12Heap* pHeap,
    UINT NumRanges,
    _In_reads_opt_(NumRanges)  const D3D12_TILE_RANGE_FLAGS* pRangeFlags,
    _In_reads_opt_(NumRanges)  const UINT* pHeapRangeStartOffsets,
    _In_reads_opt_(NumRanges)  const UINT* pRangeTileCounts,
    D3D12_TILE_MAPPING_FLAGS Flags)
{
    Handle->UpdateTileMappings(pResource, NumResourceRegions, pResourceRegionStartCoordinates, pResourceRegionSizes, pHeap, NumRanges, pRangeFlags, pHeapRangeStartOffsets, pRangeTileCounts, Flags);
}

void STDMETHODCALLTYPE D3D12Queue::CopyTileMappings(
    _In_  ID3D12Resource* pDstResource,
    _In_  const D3D12_TILED_RESOURCE_COORDINATE* pDstRegionStartCoordinate,
    _In_  ID3D12Resource* pSrcResource,
    _In_  const D3D12_TILED_RESOURCE_COORDINATE* pSrcRegionStartCoordinate,
    _In_  const D3D12_TILE_REGION_SIZE* pRegionSize,
    D3D12_TILE_MAPPING_FLAGS Flags)
{
    Handle->CopyTileMappings(pDstResource, pDstRegionStartCoordinate, pSrcResource, pSrcRegionStartCoordinate, pRegionSize, Flags);
}

void STDMETHODCALLTYPE D3D12Queue::ExecuteCommandLists(
    _In_  UINT NumCommandLists,
    _In_reads_(NumCommandLists)  ID3D12CommandList* const* ppCommandLists)
{
    Handle->ExecuteCommandLists(NumCommandLists, ppCommandLists);
}

void STDMETHODCALLTYPE D3D12Queue::SetMarker(
    UINT Metadata,
    _In_reads_bytes_opt_(Size)  const void* pData,
    UINT Size)
{
    Handle->SetMarker(Metadata, pData, Size);
}

void STDMETHODCALLTYPE D3D12Queue::BeginEvent(
    UINT Metadata,
    _In_reads_bytes_opt_(Size)  const void* pData,
    UINT Size)
{
    Handle->BeginEvent(Metadata, pData, Size);
}

void STDMETHODCALLTYPE D3D12Queue::EndEvent(void)
{
    Handle->EndEvent();
}

HRESULT STDMETHODCALLTYPE D3D12Queue::Signal(
    ID3D12Fence* pFence,
    UINT64 Value)
{
    return Handle->Signal(pFence, Value);
}

HRESULT STDMETHODCALLTYPE D3D12Queue::Wait(
    ID3D12Fence* pFence,
    UINT64 Value)
{
    return Handle->Wait(pFence, Value);
}

HRESULT STDMETHODCALLTYPE D3D12Queue::GetTimestampFrequency(
    _Out_  UINT64* pFrequency)
{
    return Handle->GetTimestampFrequency(pFrequency);
}

HRESULT STDMETHODCALLTYPE D3D12Queue::GetClockCalibration(
    _Out_  UINT64* pGpuTimestamp,
    _Out_  UINT64* pCpuTimestamp)
{
    return Handle->GetClockCalibration(pGpuTimestamp, pCpuTimestamp);
}