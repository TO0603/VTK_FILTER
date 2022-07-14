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

class CreatePFI
{

private:
    VTKFormat m_vtk_format;
    std::string m_base_name;

public:
    CreatePFI(  std::string fileName,VTKFormat vtkFormat );
    std::string KVSMLFileName() { return "./out/" + m_base_name + "_00000_0000001_0000001.kvsml"; }
    std::string getFileName() { return m_base_name; }
    void setFileName( std::string file_name ) { m_base_name = file_name; } //?
    void write( kvs::UnstructuredVolumeObject* );

private:
    int get_pfi_unstructured_cell_type( kvs::UnstructuredVolumeObject::CellType kvs_cellType );
};

#endif // CREATEPFI_H
