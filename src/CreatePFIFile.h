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
    VTKFormat m_vtk_format;
    std::string m_file_name;

public:
    CreatePFIFile(  std::string fileName,VTKFormat vtkFormat );
    std::string KVSMLFileName() { return "./out/" + m_file_name + "_00000_0000001_0000001.kvsml"; }
    std::string getFileName() { return m_file_name; }
    void setFileName( std::string file_name ) { m_file_name = file_name; } //?
    void createPFIFile( kvs::UnstructuredVolumeObject* );

private:
    int get_pfi_unstructured_cell_type( kvs::UnstructuredVolumeObject::CellType kvs_cellType );
};

#endif // CREATEPFI_H
