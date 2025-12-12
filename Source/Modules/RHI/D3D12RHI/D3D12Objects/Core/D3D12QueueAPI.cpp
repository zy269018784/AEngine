#include "D3D12Objects/Queue/D3D12Queue.h"

// 实现部分
void STDMETHODCALLTYPE D3D12Queue::UpdateTileMappings(
        ID3D12Resource *resource,
        UINT region_count,
        const D3D12_TILED_RESOURCE_COORDINATE *region_start_coordinates,
        const D3D12_TILE_REGION_SIZE *region_sizes,
        ID3D12Heap *heap,
        UINT range_count,
        const D3D12_TILE_RANGE_FLAGS *range_flags,
        UINT *heap_range_offsets,
        UINT *range_tile_counts,
        D3D12_TILE_MAPPING_FLAGS flags)
{
    Handle->UpdateTileMappings(resource, region_count, region_start_coordinates, region_sizes, heap, range_count, range_flags, heap_range_offsets, range_tile_counts, flags);
    //Handle->UpdateTileMappings(pResource, NumResourceRegions, pResourceRegionStartCoordinates, pResourceRegionSizes, pHeap, NumRanges, pRangeFlags, pHeapRangeStartOffsets, pRangeTileCounts, Flags);
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