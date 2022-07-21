#ifndef CREATEPFI_H
#define CREATEPFI_H
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeExporter>
#include <kvs/KVSMLUnstructuredVolumeObject>
#include "EnsightFormat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


class CreatePFIFile
{

private:
enum kvsCellType
{
        Point = 0,                    ///< Point.
        Line,                   ///< Line.
        Triangle,               ///< Triangle.
        Quadrangle,             ///< Quadrangle.
        Tetrahedra,             ///< Tetrahedra.
        Pyramid,                ///< Pyramid.
        Prism,                  ///< Prism.
        Hexahedra,              ///< Hexahedra.
        Line2,                  ///< Line.
        Triangle2,              ///< Triangle2.
        Quadrangle2,            ///< Quadrangle2.
        Tetrahedra2,            ///< Quadratic tetrahedra.
        Pyramid2,               ///< Pyramid.
        Prism2,                 ///< Prism.
        Hexahedra2,             ///< Quadratic hexahedra.
        ElementTypeUnknown ,  ///< Unknown element type.
};

    EnsightFormat m_Ensight;
    int m_nblocks;
    int m_total_nodes;
    int m_total_cells;
    const size_t m_nnodes;
    const size_t m_ncells;
    size_t m_nveclen;
    double m_total_bounds[6];
    kvs::ValueArray<size_t> m_sub_nnodes;
    kvs::ValueArray<size_t> m_sub_ncells;
    kvs::ValueArray<float> m_sub_coord_array;
    kvs::ValueArray<float> m_max;
    kvs::ValueArray<float> m_min;
    kvs::ValueArray<float> m_sub_value_array;
    kvs::ValueArray<kvs::Real32> m_coord_array;
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;
    int m_cell_type;
    int m_cell_type_index;
    kvs::ValueArray<int> m_cell_type_array;
    std::string m_file_name;


public:
    CreatePFIFile(std::string fileName,EnsightFormat vtk_parameter_reader);
    //std::string KVSMLFileName(const int i_block) { return "./out/" + m_file_name + "_00000_0000001_" + std::to_string(i_block) + ".kvsml"; }
    void setFileName(std::string file_name) { m_file_name = file_name; } //?
    void createPFIFile(kvs::UnstructuredVolumeObject*);
    void update_subvolume( EnsightFormat ensightFormat, const int iblock);
    void write_pfi();
    
private:
    
    void update_member_function(EnsightFormat ensightFormat);
    void update_cell_type(EnsightFormat ensightFormat);
    //void convert_celltype();
    int convert_celltype(int celltype);
    int get_pfi_unstructured_cell_type(kvs::UnstructuredVolumeObject::CellType kvs_cellType);   
};

#endif // CREATEPFI_H
