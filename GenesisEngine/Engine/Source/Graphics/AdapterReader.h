#pragma once
#include "..\Error.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>


class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter);

	IDXGIAdapter * pAdapter = nullptr;
	DXGI_ADAPTER_DESC adapterDescription;
};

class AdapterReader
{
public:
	static std::vector<AdapterData> GetGraphicsAdapters();
private:
	static std::vector<AdapterData> m_sGraphicsAdapters;
};