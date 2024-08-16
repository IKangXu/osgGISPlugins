#include "osgdb_gltf/GltfOptimizer.h"
using namespace osgGISPlugins;
size_t GltfOptimizer::calculateNumComponents(const int type)
{
	switch (type) {
	case TINYGLTF_TYPE_SCALAR:
		return 1;
	case TINYGLTF_TYPE_VEC2:
		return 2;
	case TINYGLTF_TYPE_VEC3:
		return 3;
	case TINYGLTF_TYPE_VEC4:
		return 4;
		// Add cases for other data types if needed.
	default:
		return 0; // Return 0 for unknown types.
	}
}

void GltfOptimizer::restoreBuffer(tinygltf::Buffer& buffer, tinygltf::BufferView& bufferView, osg::ref_ptr<osg::Array> newBufferData)
{
	buffer.data.resize(newBufferData->getTotalDataSize());
	const unsigned char* ptr = (unsigned char*)(newBufferData->getDataPointer());
	std::copy(ptr, ptr + newBufferData->getTotalDataSize(), buffer.data.begin());
	bufferView.byteLength = buffer.data.size();
}
