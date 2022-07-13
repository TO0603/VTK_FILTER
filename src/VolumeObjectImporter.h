#ifndef CREATEVOLUMEOBJECT_H
#define CREATEVOLUMEOBJECT_H

#include <kvs/UnstructuredVolumeObject>
#include <VTKFormat.h>

class VolumeObjectImporter : public kvs::UnstructuredVolumeObject
{
private:
    VTKFormat m_vtk_format;

public:
    VolumeObjectImporter( VTKFormat vtkFormat );

private:
    kvs::UnstructuredVolumeObject::CellType convert_vtk_cell_type_to_kvs_cell_type( int vtk_cell_type );
    void create_unstructured_volume_object();
};

#endif // CREATEVOLUMEOBJECT_H
