#ifndef CREATEVOLUMEOBJECT_H
#define CREATEVOLUMEOBJECT_H

#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeExporter>
#include <kvs/KVSMLUnstructuredVolumeObject>
#include "EnsightFormat.h"

//    cell_type_list
//{
//    0, /* 0: NON_EXISTENT */
//    1, /*  1: VTK_VERTEX */
//    0, /*  2: VTK_POLY_VERTEX, size unknown at compile time */
//    2, /*  3: VTK_LINE    */
//    0, /*  4: VTK_POLY_LINE, size unknown at compile time */
//    3, /*  5: VTK_TRIANGLE    */
//    0, /*  6: VTK_TRIANGLE_STRIP  ,size unknown at compile time*/
//    0, /*  7: VTK_POLYGON   ,size unknown at compile time */
//    4, /*  8: VTK_PIXEL  */
//    4, /*  9: VTK_QUAD   */
//    4, /* 10: VTK_TETRA  */
//    8, /* 11: VTK_VOXEL */
//    8, /* 12: VTK_HEXAHEDRON   */
//    6, /* 13: VTK_WEDGE */
//    5, /* 14: VTK_PYRAMID   */
//    3, /* 11: VTK_Q_EDGE */
//    6, /* 12: VTK_Q_TRIANGLE   */
//    8, /* 13: VTK_Q_QUAD */
//    10, /* 14: VTK_Q_TETRA   */
//    20, /* 14: VTK_Q_HEXAHEDRON   */
//};


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
    //float m_volume_min_max_coord[6];
public:
    SetVolumeObject(EnsightFormat vtk_parameter_reader);
private:
    kvs::UnstructuredVolumeObject::CellType convert_vtk_cell_type_to_kvs_cell_type(int vtk_cell_type);
    kvs::UnstructuredVolumeObject* create_unstructured_volume_object();
};

#endif // CREATEVOLUMEOBJECT_H
