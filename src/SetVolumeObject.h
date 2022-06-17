#ifndef CREATEVOLUMEOBJECT_H
#define CREATEVOLUMEOBJECT_H

#include <kvs/UnstructuredVolumeObject>
#include <VTKFormat.h>

class SetVolumeObject : public kvs::UnstructuredVolumeObject
{
private:
    const size_t m_nnodes;
    const size_t m_ncells;
    const size_t m_nveclen;
    kvs::ValueArray<kvs::Real32> m_coord_array;
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;
    int m_vtk_cell_type;
    float m_volume_min_max_coord[6];

public:
    SetVolumeObject(VTKFormat vtk_parameter_reader);

private:
    kvs::UnstructuredVolumeObject::CellType convert_vtk_cell_type_to_kvs_cell_type(int vtk_cell_type);
    kvs::UnstructuredVolumeObject* create_unstructured_volume_object();
};

#endif // CREATEVOLUMEOBJECT_H
