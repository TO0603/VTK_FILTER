#ifndef CREATEVOLUMEOBJECT_H
#define CREATEVOLUMEOBJECT_H

#include <kvs/UnstructuredVolumeObject>
#include <VTKFormat.h>

class SetVolumeObject : public kvs::UnstructuredVolumeObject
{
private:
    VTKFormat m_vtk_format;
//    const size_t m_nnodes;
//    const size_t m_ncells;
//    const size_t m_nveclen;
//    kvs::ValueArray<kvs::Real32> m_coord_array;
//    kvs::ValueArray<kvs::Real32> m_value_array;
//    kvs::ValueArray<kvs::UInt32> m_connection_array;
//    int m_vtk_cell_type;
//    float m_volume_min_max_coord[6];

public:
//    const size_t getNumberOfNodes() { return m_nnodes; }
//    const size_t getNumberOfCells() { return m_ncells; }
//    const size_t getNumberOfVeclen() { return m_nveclen; }
//    kvs::ValueArray<kvs::Real32> getCoordArray() { return m_coord_array; }
//    kvs::ValueArray<kvs::Real32> getValuewArray() { return m_value_array; }
//    kvs::ValueArray<kvs::UInt32> getConnectionArray() { return m_connection_array; }
//    int getVTKCellType() { return m_vtk_cell_type; }

//    void setNumberOfNodes( const size_t nnodes ) { m_nnodes = nnodes; }
//    void setNumberOfCells( const size_t ncells ) { m_ncells = ncells; }
//    void setNumberOfVeclen( const size_t nveclen ) { m_nveclen = nveclen; }
//    void setCoordArray( kvs::ValueArray<kvs::Real32> coord_array ) { m_coord_array = coord_array; }
//    void setValueArray( kvs::ValueArray<kvs::Real32> value_array ) { m_value_array = value_array; }
//    void setConnectionArray( kvs::ValueArray<kvs::UInt32> connection_array ) { m_connection_array = connection_array; }
//    void setVTKCellType( int vtk_cell_type ) { m_vtk_cell_type = vtk_cell_type; }

    SetVolumeObject(VTKFormat vtk_parameter_reader);

private:
    kvs::UnstructuredVolumeObject::CellType convert_vtk_cell_type_to_kvs_cell_type(int vtk_cell_type);
    kvs::UnstructuredVolumeObject* create_unstructured_volume_object();
};

#endif // CREATEVOLUMEOBJECT_H
