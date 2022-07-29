#include "VTKFormat.h"

VTKFormat::VTKFormat()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
}

void VTKFormat::read( std::string input_vtk_file )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    vtkSmartPointer<vtkGenericDataObjectReader> reader = vtkGenericDataObjectReader::New();

    reader->SetFileName( input_vtk_file.c_str() );
    reader->Update();

    m_reader = reader;
}
