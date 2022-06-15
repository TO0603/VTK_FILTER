#include "FilterVTK.h"

FilterVTK::FilterVTK():
    m_output( nullptr ),
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
    m_number_of_points( 0 ),
    m_cell_type(0)
{

}

void FilterVTK::readVTKFile(std::string input_vtk_file)
{
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName(input_vtk_file.c_str());
    reader->Update();
    check_vtk_data_set_type(reader);
}

void FilterVTK::setCoordArray()
{
    for( int i = 0; i < m_number_of_nodes; i++ )
    {
        double* point = m_output->GetPoint(i);
        m_coord_array[i * 3] = point[0];
        m_coord_array[i * 3 + 1] = point[1];
        m_coord_array[i * 3 + 2] = point[2];
//        std::cout << m_coord_array[i * 3] << "," << m_coord_array[i * 3 + 1] << "," << m_coord_array[i * 3 + 2] << std::endl;
    }
}

void FilterVTK::setValueArray()
{
    vtkDataArray* point_data_array = NULL;
    double* point_components = NULL;
    for(int i = 0; i < m_number_of_point_data_arrays; i++ )
    {
        point_data_array = m_point_data->GetArray(i);
        for(int j = 0; j < m_number_of_point_data_tuples; j++)
        {
            point_components = point_data_array->GetTuple(j);
            m_value_array[j] = point_components[0];
            std::cout << m_value_array[j] << std::endl;
        }
    }

//    vtkDataArray* cell_data_array = NULL;
//    double* cell_components = NULL;
//    for(int i = 0; i < m_number_of_point_data_arrays; i++ )
//    {
//        cell_data_array = m_cell_data->GetArray(i);
//        for(int j = 0; j < m_number_of_cell_data_tuples; j++)
//        {
//            cell_components = cell_data_array->GetTuple(j);
//            m_value_array[j] = cell_components[0];
//            std::cout << m_value_array[j] << std::endl;
//        }
//    }
}

void FilterVTK::setConnectionArray()
{
    int new_id;
    m_cell_type;
    vtkNew<vtkIdList> included_points;
    int connection_index = 0;
    for(int i = 0; i < m_number_of_elements; i++)
    {
        vtkCell* element = m_output->GetCell(i);
        m_cell_type = element->GetCellType();
        int n_points = element->GetNumberOfPoints();
        for(int j = 0; j < n_points; j++)
        {
            int id1= element->GetPointId(j);
            new_id = 1 + included_points->InsertNextId(id1);
            m_connection_array[ connection_index ] = id1;
//            std::cout << "ConnectionArray[" << connection_index << "]"<< m_connection_array[j] << std::endl;
            connection_index++;
        }
    }
}


void FilterVTK::check_vtk_data_set_type(vtkGenericDataObjectReader *reader)
{
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
//    auto output = reader->GetUnstructuredGridOutput();
//    vtkDataSet* output = reader->GetUnstructuredGridOutput();

    m_output                          = reader->GetUnstructuredGridOutput();
    m_number_of_field_data_in_file    = reader->GetNumberOfFieldDataInFile();
    m_number_of_scalars_in_file       = reader->GetNumberOfScalarsInFile();
    m_point_data                      = m_output->GetPointData();
    m_cell_data                       = m_output->GetCellData();
    m_number_of_point_data_arrays     = m_point_data->GetNumberOfArrays();
    m_number_of_point_data_components = m_point_data->GetNumberOfComponents();
    m_number_of_point_data_tuples     = m_point_data->GetNumberOfTuples();
    m_number_of_cell_data_arrays      = m_cell_data->GetNumberOfArrays();
    m_number_of_cell_data_components  = m_cell_data->GetNumberOfComponents();
    m_number_of_cell_data_tuples      = m_cell_data->GetNumberOfTuples();
    m_number_of_nodes                 = m_output->GetNumberOfPoints();
    m_number_of_elements              = m_output->GetNumberOfCells();
    m_number_of_kinds                 = m_number_of_point_data_components + m_number_of_cell_data_components;
    m_number_of_points                = m_output->GetCell( 0 )->GetNumberOfPoints();
    m_coord_array.allocate(m_number_of_nodes * 3);
    m_value_array.allocate(m_number_of_nodes * m_number_of_kinds);
    m_connection_array.allocate(m_number_of_elements * m_number_of_points);
    this->setCoordArray();
    this->setValueArray();
    this->setConnectionArray();

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
}
