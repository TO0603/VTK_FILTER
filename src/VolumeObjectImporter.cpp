#include "VolumeObjectImporter.h"

VolumeObjectImporter::VolumeObjectImporter( VTKFormat vtkFormat ):
    m_reader_output( nullptr ),
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
    m_ncells( 0 ),
    m_nkinds( 0 ),
    m_npoints( 0 ),
    m_cell_type( 0 ),
    m_vtk_format( &vtkFormat )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    generate();
    create_unstructured_volume_object();
}

kvs::UnstructuredVolumeObject::CellType VolumeObjectImporter::convert_vtk_cell_type_to_kvs_cell_type( int vtk_cellType )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    VTKCellType vtkCellType;
    vtkCellType = static_cast<VTKCellType>( vtk_cellType );
    switch( vtkCellType )
    {
    case VTK_EMPTY_CELL:
        std::cout << "VTK UnkownCellType" << std::endl;
        return kvs::UnstructuredVolumeObject::UnknownCellType;

    case VTK_TETRA:
        std::cout << "VTK_TETRA" << std::endl;
        return kvs::UnstructuredVolumeObject::Tetrahedra;

    case VTK_HEXAHEDRON:
        std::cout << "VTK_HEXAHEDRON" << std::endl;
        return kvs::UnstructuredVolumeObject::Hexahedra;

    case VTK_QUADRATIC_TETRA:
        std::cout << "VTK_QUADRATIC_TETRA" << std::endl;
        return kvs::UnstructuredVolumeObject::QuadraticTetrahedra;

    case VTK_QUADRATIC_HEXAHEDRON:
        std::cout << "VTK_QUADRATIC_HEXAHEDRON" << std::endl;
        return kvs::UnstructuredVolumeObject::QuadraticHexahedra;

    case VTK_PYRAMID:
        std::cout << "VTK_PYRAMID" << std::endl;
        return kvs::UnstructuredVolumeObject::Pyramid;

    case VTK_VERTEX:
        std::cout << "VTK_VERTEX" << std::endl;
        return kvs::UnstructuredVolumeObject::Point;

    case VTK_WEDGE:
        std::cout << "VTK_WEDGE" << std::endl;
        return kvs::UnstructuredVolumeObject::Prism;

    default:
        std::cout << "VTK UnkownCellType" << std::endl;
        return kvs::UnstructuredVolumeObject::UnknownCellType;
    }
}

void VolumeObjectImporter::create_unstructured_volume_object()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    this->setCellType( convert_vtk_cell_type_to_kvs_cell_type( getCellType() ) );
    this->setVeclen( getNumberOfKinds() );
    this->setNumberOfNodes( getNumberOfNodes() );
    this->setNumberOfCells( getNumberOfCells() );
    this->setCoords( getCoordArray() );
    this->setConnections( getConnectionArray() );

    std::cout << "getCellType()        : " << getCellType() << std::endl;
    std::cout << "getNumberOfKinds()   : " << getNumberOfKinds()   << std::endl;
    std::cout << "getNumberOfNodes()   : " << getNumberOfNodes()   << std::endl;
    std::cout << "getNumberOfCells()   : " << getNumberOfCells()   << std::endl;
    std::cout << "getCoordArray()      : " << getCoordArray()      << std::endl;
    std::cout << "getConnectionArray() : " << getConnectionArray() << std::endl;

    int values_index = 0;

    for( int i = 0; i < getNumberOfKinds(); i++ )
    {
        getMin().at(i) = getValuewArray().at(i * getNumberOfNodes());
        getMax().at(i) = getValuewArray().at(i * getNumberOfNodes());
        for( int j = 0; j < getNumberOfNodes(); j++ )
        {
            float tmp = getValuewArray().at(values_index);
            getMin().at(i) = kvs::Math::Min<float>(getMin().at(i),tmp);
            getMax().at(i) = kvs::Math::Max<float>(getMin().at(i),tmp);
            values_index++;
        }
    }

    this->setValues( getValuewArray() );
    this->updateMinMaxCoords();
    this->updateMinMaxValues();
    this->updateNormalizeParameters();
#ifdef VALUE_DEBUG
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    std::cout << "m_vtk_format.getCellType()        = " << getCellType()        << std::endl;
    std::cout << "m_vtk_format.getNumberOfKinds()   = " << getNumberOfKinds()   << std::endl;
    std::cout << "m_vtk_format.getNumberOfNodes()   = " << getNumberOfNodes()   << std::endl;
    std::cout << "m_vtk_format.getNumberOfCells()   = " << getNumberOfCells()   << std::endl;
    std::cout << "m_vtk_format.getCoordArray()      = " << getCoordArray()      << std::endl;
    std::cout << "m_vtk_format.getConnectionArray() = " << getConnectionArray() << std::endl;
    std::cout << "m_vtk_format.getValuewArray()     = " << getValuewArray()     << std::endl;
#endif
}

void VolumeObjectImporter::generate()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    check_vtk_data_set_type( m_vtk_format->getReader() );
}

void VolumeObjectImporter::setCoordArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    for( int i = 0; i < m_nnodes; i++ )
    {
        double* point = m_reader_output->GetPoint( i );
        m_coord_array[i * 3] = point[0];
        m_coord_array[i * 3 + 1] = point[1];
        m_coord_array[i * 3 + 2] = point[2];
#ifdef VALUE_DEBUG
        std::cout << "m_coord_array[" << i << "] = " << m_coord_array[i * 3] << "," << m_coord_array[i * 3 + 1] << "," << m_coord_array[i * 3 + 2] << std::endl;
#endif
    }
}

void VolumeObjectImporter::setValueArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
#ifdef VALUE_DEBUG
    std::cout << "m_value_array( points )" << std::endl;
#endif
    vtkDataArray* point_data_array = NULL;
    double* point_components = NULL;
    int value_index = 0;
    for( int i = 0; i < m_npoint_data_arrays; i++ )
    {
        point_data_array = m_point_data->GetArray( i );
        for( int j = 0; j < m_npoint_data_tuples; j++ )
        {
            point_components = point_data_array->GetTuple( j );
            m_value_array[value_index] = point_components[0];
#ifdef VALUE_DEBUG
            std::cout << "m_value_array[" << value_index << "] = "<< m_value_array[value_index] << std::endl;
#endif
            value_index++;
        }
    }

}

void VolumeObjectImporter::setConnectionArray()
{
    int new_id;
    m_cell_type;
    vtkNew<vtkIdList> included_points;
    int connection_index = 0;
    for( int i = 0; i < m_ncells; i++ )
    {
        vtkCell* element = m_reader_output->GetCell( i );
        m_cell_type = element->GetCellType();
        std::cout << "m_cell_type = " << m_cell_type << std::endl;
        int n_points = element->GetNumberOfPoints();
        for( int j = 0; j < n_points; j++ )
        {
            int id1= element->GetPointId( j );
            new_id = 1 + included_points->InsertNextId( id1 );
            m_connection_array[ connection_index ] = id1;

//#ifdef VALUE_DEBUG
//            std::cout << "m_connection_array[" << connection_index << "] = "<< m_connection_array[j] << std::endl;
//#endif
            connection_index++;
        }
    }

//    for(int i = 0; i < 1; i++)
//    {
//        std::cout << "i:" << i << std::endl;
//        for(int j = 3; j > 0; j--)
//        {
//            std::cout << "j:" << j << std::endl;
//        }
//    }

//    for(int i = 4; i < 5; i++)
//    {
//        std::cout << "i:" << i << std::endl;
//        for(int j = 7; j > 4; j--)
//        {
//            std::cout << "j:" << j << std::endl;
//        }
//    }

//    for(int i = 0; i < 24; i++)
//    {
//        if(i%4 == 0)
//        {
//            std::cout << "m_connection_array[" << i << "] = "<< m_connection_array[i] << std::endl;
//            continue;
//        }else
//        {
//            for(int j = i+2; j > 0+; j--)
//            {
//                std::cout << "m_connection_array[" << j << "] = "<< m_connection_array[j] << std::endl;
//            }
//        }
//    }
    kvs::ValueArray<kvs::UInt32> tmp;
    tmp.allocate(m_ncells * m_npoints);
    int index = 0;
    for(int i = 0; i < m_ncells * m_npoints; i+=4)
    {
        if(i%4 == 0)
        {

//            std::cout  << index << std::endl;
            tmp[index] = m_connection_array[i];
            index++;
//            std::cout << "m_connection_array[" << i << "] = "<< m_connection_array[i] << std::endl;
            for(int j = i+3; j > i;j--)
            {
//                std::cout << "m_connection_array[" << j << "] = "<< m_connection_array[j] << std::endl;

                tmp[index] = m_connection_array[j];
                index++;
            }
        }
    }
#ifdef VALUE_DEBUG
    for(int i = 0; i < m_ncells * m_npoints; i++)
    {
        std::cout << "[" << i << "]" << tmp[i]  << std::endl;
    }
#endif
    m_connection_array = tmp;
}

void VolumeObjectImporter::check_vtk_data_set_type( vtkGenericDataObjectReader *reader )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    if( reader->IsFilePolyData() )
    {
        std::cout << "[not implemented!]" << std::endl;
    }
    if( reader->IsFileUnstructuredGrid() )
    {
        std::cout << "[VTK DATASET TYPE IS UnstructuredGrid]" << std::endl;
        vtk_file_parameter( reader );
    }
}

void VolumeObjectImporter::vtk_file_parameter( vtkGenericDataObjectReader *reader )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    vtkSmartPointer<vtkCellDataToPointData> cell_to_point = vtkSmartPointer<vtkCellDataToPointData>::New();
    cell_to_point->SetProcessAllArrays( true );
    cell_to_point->SetInputData( reader->GetUnstructuredGridOutput() );
    cell_to_point->Update();

    m_reader_output                   = reader->GetUnstructuredGridOutput();
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
    m_ncells                          = cell_to_point->GetOutput()->GetNumberOfCells();
    m_nkinds                          = m_nscalars_in_file;
    m_npoints                         = cell_to_point->GetOutput()->GetCell( 0 )->GetNumberOfPoints();
    m_coord_array.allocate( m_nnodes * 3 );
    m_value_array.allocate( m_nnodes * m_nkinds );
    m_connection_array.allocate( m_ncells * m_npoints );
    m_min.allocate( m_nkinds );
    m_max.allocate( m_nkinds );
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
    std::cout << "m_ncells              = " << m_ncells              << std::endl;
    std::cout << "m_nkinds                 = " << m_nkinds                 << std::endl;
    std::cout << "m_npoints                = " << m_npoints                << std::endl;
#endif

    this->setCoordArray();
    this->setValueArray();
    this->setConnectionArray();
}
