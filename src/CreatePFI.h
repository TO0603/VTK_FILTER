#ifndef CREATEPFI_H
#define CREATEPFI_H
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeExporter>
#include <kvs/KVSMLUnstructuredVolumeObject>
#include "FilterVTK.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


class CreatePFI
{
public:
    enum VTKCellType
    {
        VTK_EMPTY_CELL           = 0,
        VTK_VERTEX               = 1,
        VTK_POLY_VERTEX          = 2,
        VTK_LINE                 = 3,
        VTK_POINT_LINE           = 4,
        VTK_TRIANGLE             = 5,
        VTK_TRIANGLE_STRIPE      = 6,
        VTK_POLYGON              = 7,
        VTK_PIXEL                = 8,
        VTK_QUAD                 = 9,
        VTK_TETRA                = 10,
        VTK_VOXEL                = 11,
        VTK_HEXAHEDRON           = 12,
        VTK_WEDGE                = 13,
        VTK_PYRAMID              = 14,
        VTK_QUADRATIC_TETRA      = 24,
        VTK_QUADRATIC_HEXAHEDRON = 25
    };
private:
    const size_t m_number_of_nodes;
    const size_t m_number_of_cells;
    const size_t m_number_of_veclen;
    kvs::ValueArray<kvs::Real32> m_coord_array;
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;
    int m_cell_type;
    float m_volume_min_max_coord[6];
    std::string m_filename;
public:
//    CreatePFI(FilterVTK filterVTK,long long number_of_nodes,long long number_of_cells, int number_of_veclens, int number_of_points);
    CreatePFI(std::string fileName,FilterVTK filterVTK);
//    void setCoordArray();
//    void setValueArray();
//    void setConnectionArray();

private:
    kvs::UnstructuredVolumeObject::CellType convert_vtk_cell_type_to_kvs_cell_type(int vtk_cell_type);
    int get_pfi_unstructured_cell_type(kvs::UnstructuredVolumeObject::CellType kvs_cellType);
    kvs::UnstructuredVolumeObject* create_unstructured_volume_object(int cellType,
                                                                     const size_t nnodes,
                                                                     const size_t ncells,
                                                                     const size_t veclen,
                                                                     kvs::ValueArray<kvs::Real32> CoordArray,
                                                                     kvs::ValueArray<kvs::Real32> ValueArray,
                                                                     kvs::ValueArray<kvs::UInt32> ConnectionArray);
    void create_kvsml_files(kvs::UnstructuredVolumeObject*);
    void create_pfi_file(kvs::UnstructuredVolumeObject*);
};

#endif // CREATEPFI_H
