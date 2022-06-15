#include "CreatePFI.h"

//CreatePFI::CreatePFI(long long number_of_nodes,long long number_of_cells, int number_of_veclens, int number_of_points):
CreatePFI::CreatePFI(std::string fileName, FilterVTK filterVTK):
    m_number_of_nodes(filterVTK.getNumberOfNodes()),
    m_number_of_cells(filterVTK.getNumberOfElements()),
    m_number_of_veclen(filterVTK.getNumberOfKinds()),
    m_coord_array(filterVTK.getCoordArray()),
    m_value_array(filterVTK.getValuewArray()),
    m_connection_array(filterVTK.getConnectionArray()),
    m_cell_type(filterVTK.getCellType()),
    m_filename(fileName)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    std::cout << "m_number_of_nodes         = " << m_number_of_nodes         << std::endl;
    std::cout << "m_number_of_cells         = " << m_number_of_cells         << std::endl;
    std::cout << "m_number_of_veclen        = " << m_number_of_veclen        << std::endl;
    std::cout << "m_coord_array.size()      = " << m_coord_array.size()      << std::endl;
    std::cout << "m_value_array.size()      = " << m_value_array.size()      << std::endl;
    std::cout << "m_connection_array.size() = " << m_connection_array.size() << std::endl;
    kvs::UnstructuredVolumeObject* volume = create_unstructured_volume_object(m_cell_type,
                                                                              m_number_of_nodes,
                                                                              m_number_of_cells,
                                                                              m_number_of_veclen,
                                                                              m_coord_array,
                                                                              m_value_array,
                                                                              m_connection_array);
    m_volume_min_max_coord[0] = volume->minObjectCoord().x();
    m_volume_min_max_coord[1] = volume->minObjectCoord().y();
    m_volume_min_max_coord[2] = volume->minObjectCoord().z();
    m_volume_min_max_coord[3] = volume->maxObjectCoord().x();
    m_volume_min_max_coord[4] = volume->maxObjectCoord().y();
    m_volume_min_max_coord[5] = volume->maxObjectCoord().z();
    create_kvsml_files(volume);
    create_pfi_file(volume);
}

//void CreatePFI::setCoordArray()
//{

//}

//void CreatePFI::setValueArray()
//{

//}

//void CreatePFI::setConnectionArray()
//{

//}

kvs::UnstructuredVolumeObject::CellType CreatePFI::convert_vtk_cell_type_to_kvs_cell_type(int vtk_cellType)
{
    VTKCellType vtkCellType;
    vtkCellType = static_cast<VTKCellType>(vtk_cellType);

    switch(vtkCellType)
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

int CreatePFI::get_pfi_unstructured_cell_type(kvs::UnstructuredVolumeObject::CellType kvs_cellType)
{
    switch(kvs_cellType)
    {
    case kvs::UnstructuredVolumeObject::UnknownCellType:
        return 0;
    case kvs::UnstructuredVolumeObject::Tetrahedra:
        return 4;
    case kvs::UnstructuredVolumeObject::Hexahedra:
        return 7;
    case kvs::UnstructuredVolumeObject::QuadraticTetrahedra:
        return 0;
    case kvs::UnstructuredVolumeObject::QuadraticHexahedra:
        return 0;
    case kvs::UnstructuredVolumeObject::Pyramid:
        return 5;
    case kvs::UnstructuredVolumeObject::Point:
        return 0;
    case kvs::UnstructuredVolumeObject::Prism:
        return 6;
    default:
        return 0;
    }
}

kvs::UnstructuredVolumeObject* CreatePFI::create_unstructured_volume_object(int vtk_cellType,
                                                                 const size_t nnodes,
                                                                 const size_t ncells,
                                                                 const size_t veclen,
                                                                 kvs::ValueArray<kvs::Real32> coords,
                                                                 kvs::ValueArray<kvs::Real32> values,
                                                                 kvs::ValueArray<kvs::UInt32> connections)
{
    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeObject();
    object->setCellType( convert_vtk_cell_type_to_kvs_cell_type(vtk_cellType)); //convertVTKCellTypetoKVSCellTYpe(celltype)
    object->setVeclen( veclen );
    object->setNumberOfNodes( nnodes );
    object->setNumberOfCells( ncells );
    object->setCoords( coords );
    object->setConnections( connections );
    object->setValues( values );
    object->updateMinMaxCoords();
    object->updateMinMaxValues();
    object->updateNormalizeParameters();
    return object;
}

void CreatePFI::create_kvsml_files(kvs::UnstructuredVolumeObject* volume)
{
    kvs::KVSMLUnstructuredVolumeObject* kvsml =
            new kvs::UnstructuredVolumeExporter<kvs::KVSMLUnstructuredVolumeObject>( volume );
    kvsml->setWritingDataType( kvs::KVSMLUnstructuredVolumeObject::ExternalBinary );
    kvsml->write("./out/" + m_filename + "_00000_0000001_0000001.kvsml");
    delete kvsml;
}

void CreatePFI::create_pfi_file(kvs::UnstructuredVolumeObject* volume)
{
    FILE *pfi = NULL;
    int itmp;
    float ftmp[6];
    std::string pfiFileName = "./out/" + m_filename + ".pfi";
    //            pfi = fopen("./out/tetrahedra.pfi", "wb");
    pfi = fopen(pfiFileName.c_str(), "wb");
    //頂点数
    itmp = m_number_of_nodes;
    fwrite(&itmp, 4, 1, pfi);
    //要素数
    itmp = m_number_of_cells;
    fwrite(&itmp, 4, 1, pfi);
    //要素タイプ
    itmp = get_pfi_unstructured_cell_type(volume->cellType());
    fwrite(&itmp, 4, 1, pfi);
    //ファイルタイプ
    itmp = 0;
    fwrite(&itmp, 4, 1, pfi);
    //ファイル数
    itmp = 0;
    fwrite(&itmp, 4, 1, pfi);
    //成分数(ベクトル?)
    itmp = m_number_of_veclen;
    fwrite(&itmp, 4, 1, pfi);
    //開始ステップ
    itmp = 0;
    fwrite(&itmp, 4, 1, pfi);
    //終了ステップ
    itmp = 0;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリューム数
    itmp = 1;
    fwrite(&itmp, 4, 1, pfi);
    //座標の最大最小値
    ftmp[0] = m_volume_min_max_coord[0];
    ftmp[1] = m_volume_min_max_coord[1];
    ftmp[2] = m_volume_min_max_coord[2];
    ftmp[3] = m_volume_min_max_coord[3];
    ftmp[4] = m_volume_min_max_coord[4];
    ftmp[5] = m_volume_min_max_coord[5];
    fwrite(&ftmp, 4, 6, pfi);
    //サブボリュームの頂点数
    itmp = m_number_of_nodes;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの要素数
    itmp = m_number_of_cells;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの座標の最大最小値
    fwrite(&ftmp, 4, 6, pfi);
    //ステップ1の成分最小値
    itmp = 1;
    fwrite(&itmp, 4, 1, pfi);
    //ステップ1の成分最大値
    itmp = 5;
    fwrite(&itmp, 4, 1, pfi);
    fclose(pfi);
}
