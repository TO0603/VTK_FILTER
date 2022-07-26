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
    EnsightFormat m_Ensight;
    int m_nblocks;
    int m_timesteps;
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
    kvs::ValueArray<int> m_numarray_celltype; 
    std::string m_file_name;

public:
    CreatePFIFile(std::string fileName,EnsightFormat vtk_parameter_reader);
    void setFileName(std::string file_name) { m_file_name = file_name; } //?
    void createPFIFile(kvs::UnstructuredVolumeObject* UnstructuredVolumeObject);
    void update_subvolume( EnsightFormat ensightFormat, const int iblock, const int i_step);
    void write_pfi();
    void write_pfl(); 
    void update_cell_type(EnsightFormat ensightFormat);
    void update_member_function(EnsightFormat ensightFormat);
};

#endif // CREATEPFI_H
