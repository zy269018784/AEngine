#pragma once
#include "D3D12Objects/Device/D3D12Device.h"

class D3D12Queue
{
public:
	D3D12Queue(D3D12Device *InDevice);
	~D3D12Queue();
	ID3D12CommandQueue* GetHandle();
public:
    void STDMETHODCALLTYPE UpdateTileMappings(
        ID3D12Resource *resource,
        UINT region_count,
        const D3D12_TILED_RESOURCE_COORDINATE *region_start_coordinates,
        const D3D12_TILE_REGION_SIZE *region_sizes,
        ID3D12Heap *heap,
        UINT range_count,
        const D3D12_TILE_RANGE_FLAGS *range_flags,
        UINT *heap_range_offsets,
        UINT *range_tile_counts,
        D3D12_TILE_MAPPING_FLAGS flags);

    void STDMETHODCALLTYPE CopyTileMappings(
        _In_  ID3D12Resource* pDstResource,
        _In_  const D3D12_TILED_RESOURCE_COORDINATE* pDstRegionStartCoordinate,
        _In_  ID3D12Resource* pSrcResource,
        _In_  const D3D12_TILED_RESOURCE_COORDINATE* pSrcRegionStartCoordinate,
        _In_  const D3D12_TILE_REGION_SIZE* pRegionSize,
        D3D12_TILE_MAPPING_FLAGS Flags);

    void STDMETHODCALLTYPE ExecuteCommandLists(
        _In_  UINT NumCommandLists,
        _In_reads_(NumCommandLists)  ID3D12CommandList* const* ppCommandLists);

    void STDMETHODCALLTYPE SetMarker(
        UINT Metadata,
        _In_reads_bytes_opt_(Size)  const void* pData,
        UINT Size);

    void STDMETHODCALLTYPE BeginEvent(
        UINT Metadata,
        _In_reads_bytes_opt_(Size)  const void* pData,
        UINT Size);

    void STDMETHODCALLTYPE EndEvent(void);

    HRESULT STDMETHODCALLTYPE Signal(
        ID3D12Fence* pFence,
        UINT64 Value);

    HRESULT STDMETHODCALLTYPE Wait(
        ID3D12Fence* pFence,
        UINT64 Value);

    HRESULT STDMETHODCALLTYPE GetTimestampFrequency(
        _Out_  UINT64* pFrequency);

    HRESULT STDMETHODCALLTYPE GetClockCalibration(
        _Out_  UINT64* pGpuTimestamp,
        _Out_  UINT64* pCpuTimestamp);
private:
	ID3D12CommandQueue* Handle = nullptr;
	D3D12Device* Device = nullptr;
};
