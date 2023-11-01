#include"Graphics/DescripterManager/DescriptorManager.h"

struct  TexData
{
	uint32_t index;
	ComPtr<ID3D12Resource> resource;
};

class TexDataResource
{
public:
	TexDataResource(string filePath, TexData texData);
	~TexDataResource();

	uint32_t GetTexHandle() { return texData_.index; }
	void texRelease() { texData_.resource.Reset(); }

private:

	string filePath_;
	TexData texData_;
};
