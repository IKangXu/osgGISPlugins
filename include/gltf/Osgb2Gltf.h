#ifndef OSG_GIS_PLUGINS_OSGB2GLTF_H
#define OSG_GIS_PLUGINS_OSGB2GLTF_H 1
#include <osg/NodeVisitor>
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include <tinygltf/tiny_gltf.h>
#include "material/GltfPbrMRMaterial.h"
#include "material/GltfPbrSGMaterial.h"
#include "compress/GltfComporessor.h"
#include "merge/GltfMerge.h"
#include <stack>
#include <osg/PrimitiveSet>
#include <iostream>
class Osgb2Gltf :public osg::NodeVisitor {
	typedef std::map<osg::ref_ptr<const osg::Node>, int> OsgNodeSequenceMap;
	typedef std::map<osg::ref_ptr<const osg::BufferData>, int> ArraySequenceMap;
	typedef std::map<osg::ref_ptr<const osg::Array>, int> AccessorSequenceMap;
	typedef std::vector<osg::ref_ptr<osg::StateSet>> StateSetStack;

	std::vector<osg::ref_ptr<osg::Texture>> _textures;
	GltfComporessor* _gltfComporessor;

	std::stack<tinygltf::Node*> _gltfNodeStack;
	OsgNodeSequenceMap _osgNodeSeqMap;
	ArraySequenceMap _buffers;
	ArraySequenceMap _bufferViews;
	ArraySequenceMap _accessors;
	StateSetStack _ssStack;
	osg::ref_ptr<osg::Geode> _cacheGeode = nullptr;
	int _vco = 1;
	double _ratio = 1.0;

	void push(tinygltf::Node& gnode);

	void pop();

	bool pushStateSet(osg::StateSet* stateSet);

	void popStateSet();

	unsigned getBytesInDataType(const GLenum dataType);

	unsigned getBytesPerElement(const osg::Array* data);

	unsigned getBytesPerElement(const osg::DrawElements* data);

	int getOrCreateBuffer(const osg::BufferData* data);

	int getOrCreateBufferView(const osg::BufferData* data, const GLenum target);

	int getOrCreateAccessor(const osg::Array* data, osg::PrimitiveSet* pset, tinygltf::Primitive& prim, const std::string& attr);

	int getCurrentMaterial();

	int getOrCreateTexture(const osg::ref_ptr<osg::Texture>& osgTexture);

	int getOsgTexture2Material(tinygltf::Material& gltfMaterial, const osg::ref_ptr<osg::Texture>& osgTexture);

	int getOsgMaterial2Material(tinygltf::Material& gltfMaterial, const osg::ref_ptr<osg::Material>& osgMaterial);

	int getCurrentMaterial(tinygltf::Material& gltfMaterial);

	void apply(osg::Node& node) override;

	void apply(osg::Group& group) override;

	void apply(osg::MatrixTransform& xform) override;

	void apply(osg::Drawable& drawable) override;

public:
	tinygltf::Model model;
	Osgb2Gltf() = default;
	Osgb2Gltf(GltfComporessor* gltfComporessor);
	~Osgb2Gltf();
};

#endif // !OSG_GIS_PLUGINS_OSGB2GLTF_H
