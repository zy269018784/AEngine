#include "D3D11RHI/D3D11Objects/Resource/D3D11Buffer.h"

ID3D11Buffer* D3D11Buffer::GetHandle() const
{
    return Handle;
}