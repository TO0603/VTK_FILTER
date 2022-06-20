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

kvs::UnstructuredVolumeObject* SetVolumeObject::create_unstructured_volume_object()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeObject();
    this->setCellType( convert_vtk_cell_type_to_kvs_cell_type( m_vtk_format.getCellType() ) );
    this->setVeclen( m_vtk_format.getNumberOfKinds() );
    this->setNumberOfNodes( m_vtk_format.getNumberOfNodes() );
    this->setNumberOfCells( m_vtk_format.getNumberOfCells() );
    this->setCoords( m_vtk_format.getCoordArray() );
    this->setConnections( m_vtk_format.getConnectionArray() );
    this->setValues( m_vtk_format.getValuewArray() );
    this->updateMinMaxCoords();
    this->updateMinMaxValues();
    this->updateNormalizeParameters();
    return object;
}
