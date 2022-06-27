#include "SetVolumeObject.h"

SetVolumeObject::SetVolumeObject( VTKFormat vtkFormat ):
    m_vtk_format( vtkFormat )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    create_unstructured_volume_object();
}

kvs::UnstructuredVolumeObject::CellType SetVolumeObject::convert_vtk_cell_type_to_kvs_cell_type( int vtk_cellType )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    VTKCellType vtkCellType;
    vtkCellType = static_cast<VTKCellType>( vtk_cellType );
    switch( vtkCellType )
    {
    case VTK_EMPTY_CELL:
        return kvs::UnstructuredVolumeObject::UnknownCellType;

    case VTK_TETRA:
        return kvs::UnstructuredVolumeObject::Tetrahedra;

    case VTK_HEXAHEDRON:
        return kvs::UnstructuredVolumeObject::Hexahedra;

    case VTK_QUADRATIC_TETRA:
        return kvs::UnstructuredVolumeObject::QuadraticTetrahedra;

    case VTK_QUADRATIC_HEXAHEDRON:
        return kvs::UnstructuredVolumeObject::QuadraticHexahedra;

    case VTK_PYRAMID:
        return kvs::UnstructuredVolumeObject::Pyramid;

    case VTK_VERTEX:
        return kvs::UnstructuredVolumeObject::Point;

    case VTK_WEDGE:
        return kvs::UnstructuredVolumeObject::Prism;

    default:
        return kvs::UnstructuredVolumeObject::UnknownCellType;
    }
}

void SetVolumeObject::create_unstructured_volume_object()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    this->setCellType( convert_vtk_cell_type_to_kvs_cell_type( m_vtk_format.getCellType() ) );
    this->setVeclen( m_vtk_format.getNumberOfKinds() );
    this->setNumberOfNodes( m_vtk_format.getNumberOfNodes() );
    this->setNumberOfCells( m_vtk_format.getNumberOfCells() );
    this->setCoords( m_vtk_format.getCoordArray() );
    this->setConnections( m_vtk_format.getConnectionArray() );

    int values_index = 0;

    for( int i = 0; i < m_vtk_format.getNumberOfKinds(); i++ )
    {
        m_vtk_format.getMin().at(i) = m_vtk_format.getValuewArray().at(i * m_vtk_format.getNumberOfNodes());
        m_vtk_format.getMax().at(i) = m_vtk_format.getValuewArray().at(i * m_vtk_format.getNumberOfNodes());
        for( int j = 0; j < m_vtk_format.getNumberOfNodes(); j++ )
        {
            float tmp = m_vtk_format.getValuewArray().at(values_index);
            m_vtk_format.getMin().at(i) = kvs::Math::Min<float>(m_vtk_format.getMin().at(i),tmp);
            m_vtk_format.getMax().at(i) = kvs::Math::Max<float>(m_vtk_format.getMin().at(i),tmp);
            values_index++;
        }
    }

    this->setValues( m_vtk_format.getValuewArray() );
    this->updateMinMaxCoords();
    this->updateMinMaxValues();
    this->updateNormalizeParameters();
#ifdef VALUE_DEBUG
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    std::cout << "m_vtk_format.getCellType()        = " << m_vtk_format.getCellType()        << std::endl;
    std::cout << "m_vtk_format.getNumberOfKinds()   = " << m_vtk_format.getNumberOfKinds()   << std::endl;
    std::cout << "m_vtk_format.getNumberOfNodes()   = " << m_vtk_format.getNumberOfNodes()   << std::endl;
    std::cout << "m_vtk_format.getNumberOfCells()   = " << m_vtk_format.getNumberOfCells()   << std::endl;
    std::cout << "m_vtk_format.getCoordArray()      = " << m_vtk_format.getCoordArray()      << std::endl;
    std::cout << "m_vtk_format.getConnectionArray() = " << m_vtk_format.getConnectionArray() << std::endl;
    std::cout << "m_vtk_format.getValuewArray()     = " << m_vtk_format.getValuewArray()     << std::endl;
#endif
}
