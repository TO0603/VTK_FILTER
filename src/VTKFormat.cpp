#include "VTKFormat.h"

VTKFormat::VTKFormat():
    m_output( nullptr ),
    m_nfield_data_in_file( 0 ),
    m_nscalars_in_file( 0 ),
    m_point_data( nullptr ),
    m_cell_data( nullptr ),
    m_npoint_data_arrays( 0 ),
    m_npoint_data_components( 0 ),
    m_npoint_data_tuples( 0 ),
    m_ncell_data_arrays( 0 ),
    m_ncell_data_components( 0 ),
    m_ncell_data_tuples( 0 ),
    m_nnodes( 0 ),
    m_nelements( 0 ),
    m_nkinds( 0 ),
    m_npoints( 0 ),
    m_cell_type(0)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
}

void VTKFormat::read(std::string input_vtk_file)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    vtkSmartPointer<vtkGenericDataObjectReader> reader = vtkGenericDataObjectReader::New();

    reader->SetFileName(input_vtk_file.c_str());
    reader->Update();

    m_reader = reader;
}

void VTKFormat::generate()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    check_vtk_data_set_type(m_reader);
}

void VTKFormat::setCoordArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    for( int i = 0; i < m_nnodes; i++ )
    {
        double* point = m_output->GetPoint(i);
        m_coord_array[i * 3] = point[0];
        m_coord_array[i * 3 + 1] = point[1];
        m_coord_array[i * 3 + 2] = point[2];
#ifdef VALUE_DEBUG        
        std::cout << "m_coord_array[" << i << "] = " << m_coord_array[i * 3] << "," << m_coord_array[i * 3 + 1] << "," << m_coord_array[i * 3 + 2] << std::endl;
#endif
    }
}

void VTKFormat::setValueArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
#ifdef VALUE_DEBUG
    std::cout << "m_value_array(points)" << std::endl;
#endif
    vtkDataArray* point_data_array = NULL;
    double* point_components = NULL;
    int value_index = 0;
    for(int i = 0; i < m_npoint_data_arrays; i++ )
    {
        point_data_array = m_point_data->GetArray(i);
        for(int j = 0; j < m_npoint_data_tuples; j++)
        {
            point_components = point_data_array->GetTuple(j);
            m_value_array[value_index] = point_components[0];
#ifdef VALUE_DEBUG            
            std::cout << "m_value_array[" << value_index << "] = "<< m_value_array[value_index] << std::endl;
#endif
            value_index++;
        }
    }

}

void VTKFormat::setConnectionArray()
{    
    int new_id;
    m_cell_type;
    vtkNew<vtkIdList> included_points;
    int connection_index = 0;
    for(int i = 0; i < m_nelements; i++)
    {
        vtkCell* element = m_output->GetCell(i);
        m_cell_type = element->GetCellType();
        int n_points = element->GetNumberOfPoints();
        for(int j = 0; j < n_points; j++)
        {
            int id1= element->GetPointId(j);
            new_id = 1 + included_points->InsertNextId(id1);
            m_connection_array[ connection_index ] = id1;

#ifdef VALUE_DEBUG
            std::cout << "m_connection_array[" << connection_index << "] = "<< m_connection_array[j] << std::endl;
#endif
            connection_index++;
        }
    }
}

void VTKFormat::check_vtk_data_set_type(vtkGenericDataObjectReader *reader)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
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

void VTKFormat::read_vtk_file_parameter(vtkGenericDataObjectReader *reader)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    vtkSmartPointer<vtkCellDataToPointData> cell_to_point = vtkSmartPointer<vtkCellDataToPointData>::New();
    cell_to_point->SetProcessAllArrays(true);
    cell_to_point->SetInputData(reader->GetUnstructuredGridOutput());
    cell_to_point->Update();

    m_output                          = reader->GetUnstructuredGridOutput();
    m_nfield_data_in_file             = reader->GetNumberOfFieldDataInFile();
    m_nscalars_in_file                = reader->GetNumberOfScalarsInFile();
    m_point_data                      = cell_to_point->GetOutput()->GetPointData();
    m_cell_data                       = cell_to_point->GetOutput()->GetCellData();
    m_npoint_data_arrays              = m_point_data->GetNumberOfArrays();
    m_npoint_data_components          = m_point_data->GetNumberOfComponents();
    m_npoint_data_tuples              = m_point_data->GetNumberOfTuples();
    m_ncell_data_arrays               = m_cell_data->GetNumberOfArrays();
    m_ncell_data_components           = m_cell_data->GetNumberOfComponents();
    m_ncell_data_tuples               = m_cell_data->GetNumberOfTuples();
    m_nnodes                          = cell_to_point->GetOutput()->GetNumberOfPoints();
    m_nelements                       = cell_to_point->GetOutput()->GetNumberOfCells();
    m_nkinds                          = m_nscalars_in_file;
    m_npoints                         = cell_to_point->GetOutput()->GetCell( 0 )->GetNumberOfPoints();
    m_coord_array.allocate(m_nnodes * 3);
    m_value_array.allocate(m_nnodes * m_nkinds);
    m_connection_array.allocate(m_nelements * m_npoints);

#ifdef VALUE_DEBUG
    std::cout << "m_nfield_data_in_file    = " << m_nfield_data_in_file    << std::endl;
    std::cout << "m_nscalars_in_file       = " << m_nscalars_in_file       << std::endl;
    //    std::cout << "m_point_data                      = " << m_point_data                      << std::endl;
    //    std::cout << "m_cell_data                       = " << m_cell_data                       << std::endl;
    std::cout << "m_npoint_data_arrays     = " << m_npoint_data_arrays     << std::endl;
    std::cout << "m_npoint_data_components = " << m_npoint_data_components << std::endl;
    std::cout << "m_npoint_data_tuples     = " << m_npoint_data_tuples     << std::endl;
    std::cout << "m_ncell_data_arrays      = " << m_ncell_data_arrays      << std::endl;
    std::cout << "m_ncell_data_components  = " << m_ncell_data_components  << std::endl;
    std::cout << "m_ncell_data_tuples      = " << m_ncell_data_tuples      << std::endl;
    std::cout << "m_nnodes                 = " << m_nnodes                 << std::endl;
    std::cout << "m_nelements              = " << m_nelements              << std::endl;
    std::cout << "m_nkinds                 = " << m_nkinds                 << std::endl;
    std::cout << "m_npoints                = " << m_npoints                << std::endl;
#endif

    this->setCoordArray();
    this->setValueArray();
    this->setConnectionArray();
}
