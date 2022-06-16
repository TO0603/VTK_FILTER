#ifndef CREATEPFI_H
#define CREATEPFI_H
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeExporter>
#include <kvs/KVSMLUnstructuredVolumeObject>
#include "VTKFormat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


class CreatePFIFile
{

private:
    const size_t m_nnodes;
    const size_t m_ncells;
    const size_t m_nveclen;
    kvs::ValueArray<kvs::Real32> m_coord_array;
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;
    int m_cell_type;
    std::string m_file_name;
public:
    CreatePFIFile(std::string fileName,VTKFormat vtk_parameter_reader);
    std::string KVSMLFileName() { return "./out/" + m_file_name + "_00000_0000001_0000001.kvsml"; }
    void setFileName(std::string file_name) { m_file_name = file_name; } //?
    void createPFIFile(kvs::UnstructuredVolumeObject*);
private:
    int get_pfi_unstructured_cell_type(kvs::UnstructuredVolumeObject::CellType kvs_cellType);    
};

#endif // CREATEPFI_H
