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
        _In_  ID3D12Resource* pResource,
        UINT NumResourceRegions,
        _In_reads_opt_(NumResourceRegions)  const D3D12_TILED_RESOURCE_COORDINATE* pResourceRegionStartCoordinates,
        _In_reads_opt_(NumResourceRegions)  const D3D12_TILE_REGION_SIZE* pResourceRegionSizes,
        _In_opt_  ID3D12Heap* pHeap,
        UINT NumRanges,
        _In_reads_opt_(NumRanges)  const D3D12_TILE_RANGE_FLAGS* pRangeFlags,
        _In_reads_opt_(NumRanges)  const UINT* pHeapRangeStartOffsets,
        _In_reads_opt_(NumRanges)  const UINT* pRangeTileCounts,
        D3D12_TILE_MAPPING_FLAGS Flags);

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
