#include "FilterVTK.h"

FilterVTK::FilterVTK():
    m_number_of_field_data_in_file( 0 ),
    m_number_of_scalars_in_file( 0 ),
    m_point_data( nullptr ),
    m_cell_data( nullptr ),
    m_number_of_point_data_arrays( 0 ),
    m_number_of_point_data_components( 0 ),
    m_number_of_point_data_tuples( 0 ),
    m_number_of_cell_data_arrays( 0 ),
    m_number_of_cell_data_components( 0 ),
    m_number_of_cell_data_tuples( 0 ),
    m_number_of_nodes( 0 ),
    m_number_of_elements( 0 ),
    m_number_of_kinds( 0 ),
    m_number_of_points( 0 )
{

}

void FilterVTK::readVTKFile(std::string input_vtk_file)
{
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName(input_vtk_file.c_str());
    reader->Update();
    check_vtk_data_set_type(reader);
}

void FilterVTK::check_vtk_data_set_type(vtkGenericDataObjectReader *reader)
{
//switch(*reader)
//{
//case reader->IsFilePolyData():
//    std::cout << "not implemented!" << std::endl;
//    return EXIT_SUCCESS;

//case reader->IsFileUnstructuredGrid():
//    std::cout << "VTK DATASET TYPE IS UnstructuredGrid" << std::endl;
//    read_vtk_file_parameter(reader);
//    break;

//default:
//    std::cout << "VTK DATASET TYPE COULD NOT BE DETERMINED" << std::endl;
//}
    if(reader->IsFilePolyData())
    {
        std::cout << "not implemented!" << std::endl;
    }
    if(reader->IsFileUnstructuredGrid())
    {
        std::cout << "VTK DATASET TYPE IS UnstructuredGrid" << std::endl;
        read_vtk_file_parameter(reader);
    }
}

void FilterVTK::read_vtk_file_parameter(vtkGenericDataObjectReader *reader)
{
    auto output = reader->GetUnstructuredGridOutput();
//    vtkDataSet* output = reader->GetUnstructuredGridOutput();

    m_number_of_field_data_in_file    = reader->GetNumberOfFieldDataInFile();
    m_number_of_scalars_in_file       = reader->GetNumberOfScalarsInFile();
    m_point_data                      = output->GetPointData();
    m_cell_data                       = output->GetCellData();
    m_number_of_point_data_arrays     = m_point_data->GetNumberOfArrays();
    m_number_of_point_data_components = m_point_data->GetNumberOfComponents();
    m_number_of_point_data_tuples     = m_point_data->GetNumberOfTuples();
    m_number_of_cell_data_arrays      = m_cell_data->GetNumberOfArrays();
    m_number_of_cell_data_components  = m_cell_data->GetNumberOfComponents();
    m_number_of_cell_data_tuples      = m_cell_data->GetNumberOfTuples();
    m_number_of_nodes                 = output->GetNumberOfPoints();
    m_number_of_elements              = output->GetNumberOfCells();
    m_number_of_kinds                 = m_number_of_point_data_components + m_number_of_cell_data_components;
    m_number_of_points                = output->GetCell( 0 )->GetNumberOfPoints();

    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    std::cout << "m_number_of_field_data_in_file    = " << m_number_of_field_data_in_file    << std::endl;
    std::cout << "m_number_of_scalars_in_file       = " << m_number_of_scalars_in_file       << std::endl;
//    std::cout << "m_point_data                      = " << m_point_data                      << std::endl;
//    std::cout << "m_cell_data                       = " << m_cell_data                       << std::endl;
    std::cout << "m_number_of_point_data_arrays     = " << m_number_of_point_data_arrays     << std::endl;
    std::cout << "m_number_of_point_data_components = " << m_number_of_point_data_components << std::endl;
    std::cout << "m_number_of_point_data_tuples     = " << m_number_of_point_data_tuples     << std::endl;
    std::cout << "m_number_of_cell_data_arrays      = " << m_number_of_cell_data_arrays      << std::endl;
    std::cout << "m_number_of_cell_data_components  = " << m_number_of_cell_data_components  << std::endl;
    std::cout << "m_number_of_cell_data_tuples      = " << m_number_of_cell_data_tuples      << std::endl;
    std::cout << "m_number_of_nodes                 = " << m_number_of_nodes                 << std::endl;
    std::cout << "m_number_of_elements              = " << m_number_of_elements              << std::endl;
    std::cout << "m_number_of_kinds                 = " << m_number_of_kinds                 << std::endl;
    std::cout << "m_number_of_points                = " << m_number_of_points                << std::endl;
//    std::cout << *m_vtk_data_set->GetPoint(2) << std::endl;
}
