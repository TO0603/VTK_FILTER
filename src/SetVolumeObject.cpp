#include "SetVolumeObject.h"

SetVolumeObject::SetVolumeObject(EnsightFormat vtk_parameter_reader):
    m_nnodes(vtk_parameter_reader.getNumberOfNodes()),
    m_ncells(vtk_parameter_reader.getNumberOfElements()),
    m_nveclen(vtk_parameter_reader.getNumberOfKinds()),
    m_coord_array(vtk_parameter_reader.getCoordArray()),
    m_value_array(vtk_parameter_reader.getValuewArray()),
    m_connection_array(vtk_parameter_reader.getConnectionArray()),
    m_vtk_cell_type(vtk_parameter_reader.getCellType())
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
#ifdef VALUE_DEBUG
    std::cout << "m_nnodes           = " << m_nnodes           << std::endl;
    std::cout << "m_ncells           = " << m_ncells           << std::endl;
    std::cout << "m_nveclen          = " << m_nveclen          << std::endl;
    std::cout << "m_coord_array      = " << m_coord_array      << std::endl;
    std::cout << "m_value_array      = " << m_value_array      << std::endl;
    std::cout << "m_connection_array = " << m_connection_array << std::endl;
    std::cout << "m_vtk_cell_type    = " << m_vtk_cell_type    << std::endl;
#endif
    std::cout << "m_vtk_cell_type    = " << m_vtk_cell_type    << std::endl;
    create_unstructured_volume_object();
}

kvs::UnstructuredVolumeObject::CellType SetVolumeObject::convert_vtk_cell_type_to_kvs_cell_type(int vtk_cellType)
//int  SetVolumeObject::convert_vtk_cell_type_to_kvs_cell_type(int vtk_cellType)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    VTKCellType vtkCellType;
    vtkCellType = static_cast<VTKCellType>(vtk_cellType);
    switch(vtkCellType)
    {
    case VTK_EMPTY_CELL:
        return kvs::UnstructuredVolumeObject::UnknownCellType;
        //return 0;

    case VTK_TETRA:
        return kvs::UnstructuredVolumeObject::Tetrahedra;
        //return 10;

    case VTK_HEXAHEDRON:
        return kvs::UnstructuredVolumeObject::Hexahedra;
        //return 12; 

    case VTK_QUADRATIC_TETRA:
        return kvs::UnstructuredVolumeObject::QuadraticTetrahedra;
        //return 14; 

    case VTK_QUADRATIC_HEXAHEDRON:
        return kvs::UnstructuredVolumeObject::QuadraticHexahedra;
        //return 14;

    case VTK_PYRAMID:
        return kvs::UnstructuredVolumeObject::Pyramid;
        //return 14; 

    case VTK_VERTEX:
        return kvs::UnstructuredVolumeObject::Point;
        //return 1;  

    case VTK_WEDGE:
        return kvs::UnstructuredVolumeObject::Prism;
        //return 6;  

//    case VTK_TRIANGLE:
//        return kvs::UnstructuredVolumeObject::Triangle ;
//        //return 5; 

    default:
        return kvs::UnstructuredVolumeObject::UnknownCellType;
        //return 0;
    }
}

//int SetVolumeObject::is_triangle(int vtk_cellType)
//{
//
//}


kvs::UnstructuredVolumeObject* SetVolumeObject::create_unstructured_volume_object()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeObject();
    this->setCellType( convert_vtk_cell_type_to_kvs_cell_type(m_vtk_cell_type));
    this->setVeclen( m_nveclen );
    this->setNumberOfNodes( m_nnodes );
    this->setNumberOfCells( m_ncells );
    this->setCoords( m_coord_array );
    this->setConnections( m_connection_array );
    this->setValues( m_value_array );
    this->updateMinMaxCoords();
    this->updateMinMaxValues();
    this->updateNormalizeParameters();
    return object;
}
