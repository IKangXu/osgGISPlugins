#include "osgdb_gltf/b3dm/BatchIdVisitor.h"
#include <osg/Geometry>
#include <osg/Geode>
using namespace osgGISPlugins;
void BatchIdVisitor::apply(osg::Drawable& drawable) {
    osg::Geometry* geometry = drawable.asGeometry();
    if (geometry) {
        const osg::Vec3Array* positions = dynamic_cast<osg::Vec3Array*>(geometry->getVertexArray());
        if (positions) {
            osg::ref_ptr<osg::FloatArray> batchIds = new osg::FloatArray;
            batchIds->assign(positions->size(), _currentBatchId);

            const osg::Array* vertexAttrib = geometry->getVertexAttribArray(0);
            if (vertexAttrib) {
                OSG_WARN << "Warning: geometry's VertexAttribArray(0 channel) is not null, it will be overwritten!" << std::endl;
            }
            geometry->setVertexAttribArray(0, batchIds, osg::Array::BIND_PER_VERTEX);
        }
    }
}

void BatchIdVisitor::apply(osg::Geode& geode)
{
    if (geode.getNumDrawables()) {
        traverse(geode);
        _currentBatchId++;
    }
}
