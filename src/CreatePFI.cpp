#include "CreatePFI.h"

//CreatePFI::CreatePFI(long long number_of_nodes,long long number_of_cells, int number_of_veclens, int number_of_points):
CreatePFI::CreatePFI(FilterVTK filterVTK):
    m_number_of_nodes(filterVTK.getNumberOfNodes()),
    m_number_of_cells(filterVTK.getNumberOfElements()),
    m_number_of_veclen(filterVTK.getNumberOfKinds()),
    m_coord_array(m_number_of_nodes * 3),
    m_value_array(m_number_of_nodes * m_number_of_veclen),
    m_connection_array(m_number_of_cells * filterVTK.getNumberOfPoints())
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    std::cout << "m_number_of_nodes         = " << m_number_of_nodes         << std::endl;
    std::cout << "m_number_of_cells         = " << m_number_of_cells         << std::endl;
    std::cout << "m_number_of_veclen        = " << m_number_of_veclen        << std::endl;
    std::cout << "m_coord_array.size()      = " << m_coord_array.size()      << std::endl;
    std::cout << "m_value_array.size()      = " << m_value_array.size()      << std::endl;
    std::cout << "m_connection_array.size() = " << m_connection_array.size() << std::endl;
}

void CreatePFI::setCoordArray()
{
    for(int i = 0; i < m_number_of_nodes; i++ )
    {
        std::cout << i << std::endl;
//        std::cout << m_filterVTK.getNumberOfNodes() << std::endl;
//        std::cout << m_filterVTK.getPoint(i) << std::endl;
//        double* point = output->GetPoint(
//        m_coord_array[i * 3]     = point[0];
//        m_coord_array[i * 3 + 1] = point[1];
//        m_coord_array[i * 3 + 2] = point[2];
//        std::cout << m_coord_array[i * 3]     << std::endl;
//        std::cout << m_coord_array[i * 3 + 1] << std::endl;
//        std::cout << m_coord_array[i * 3 + 2] << std::endl;
    }
}

void CreatePFI::setValueArray(double tmp)
{
//    vtkDataArray* pointData_array = NULL;
//    double* pointComponents = NULL;
//    for(int i = 0; i < n_pointData_arrays; i++ )
//    {
//        pointData_array = point_data->GetArray(i);
//        for(int j = 0; j < n_pointData_tuples; j++)
//        {
//            pointComponents = pointData_array->GetTuple(j);
//            ValueArray[j] = pointComponents[0];
//        }
//    }
}

void CreatePFI::setConnectionArray(double tmp)
{
//    int new_id;
//    int cellType;
//    vtkNew<vtkIdList> included_points;
//    int connection_index = 0;
//    for(int i = 0; i < m_nelements; i++)
//    {
//        vtkCell* element = output->GetCell(i);
//        cellType = element->GetCellType();
//        int n_points = element->GetNumberOfPoints();
//        for(int j = 0; j < n_points; j++)
//        {
//            int id1= element->GetPointId(j);
//            new_id = 1 + included_points->InsertNextId(id1);
//            ConnectionArray[ connection_index ] = id1;
//            std::cout << "ConnectionArray[" << connection_index << "]"<< ConnectionArray[j] << std::endl;
//            connection_index++;

//        }
//    }
}

kvs::UnstructuredVolumeObject* create_unstructured_volume_object(int vtk_cellType,
                                                                 const size_t nnodes,
                                                                 const size_t ncells,
                                                                 const size_t veclen,
                                                                 kvs::ValueArray<kvs::Real32> coords,
                                                                 kvs::ValueArray<kvs::Real32> values,
                                                                 kvs::ValueArray<kvs::UInt32> connections)
{
//    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeObject();
//    object->setCellType( GetKVSUnstructuredCellType(vtk_cellType)); //convertVTKCellTypetoKVSCellTYpe(celltype)
//    object->setVeclen( veclen );
//    object->setNumberOfNodes( nnodes );
//    object->setNumberOfCells( ncells );
//    object->setCoords( coords );
//    object->setConnections( connections );
//    object->setValues( values );
//    object->updateMinMaxCoords();
//    object->updateMinMaxValues();
//    object->updateNormalizeParameters();
//    return object;
}
