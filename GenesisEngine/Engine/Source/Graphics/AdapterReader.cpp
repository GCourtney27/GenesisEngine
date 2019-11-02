#include "AdapterReader.h"

#pragma comment(lib, "dxgi.lib")

std::vector<AdapterData> AdapterReader::m_sGraphicsAdapters;

AdapterData::AdapterData(IDXGIAdapter * pAdapter)
{
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->adapterDescription);
	if (FAILED(hr))
	{
		MessageBoxW(NULL, L"Failed to get description for selected adapter.", L"Error", MB_ICONERROR);
	}


}

std::vector<AdapterData> AdapterReader::GetGraphicsAdapters()
{
	if (m_sGraphicsAdapters.size() > 0)
		return m_sGraphicsAdapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		MessageBoxW(NULL, L"Failed to initialize DXGI Factory.", L"Fatal Error", MB_ICONERROR);
		exit(-1);
	}

	IDXGIAdapter * pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		m_sGraphicsAdapters.push_back(AdapterData(pAdapter));
		index++;
	}
	return m_sGraphicsAdapters;
}
