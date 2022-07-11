#include "CreatePFIFile.h"

CreatePFIFile::CreatePFIFile(std::string fileName, EnsightFormat filterEnsight):
    m_nnodes(filterEnsight.getNumberOfNodes()),
    m_ncells(filterEnsight.getNumberOfElements()),
    m_nveclen(filterEnsight.getNumberOfKinds()),
    m_coord_array(filterEnsight.getCoordArray()),
    m_value_array(filterEnsight.getValuewArray()),
    m_connection_array(filterEnsight.getConnectionArray()),
    m_cell_type(filterEnsight.getCellType()),
    m_file_name(fileName)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
#ifdef VALUE_DEBUG
    std::cout << "m_nnodes                  = " << m_nnodes                  << std::endl;
    std::cout << "m_ncells                  = " << m_ncells                  << std::endl;
    std::cout << "m_nveclen                 = " << m_nveclen                 << std::endl;
    std::cout << "m_coord_array.size()      = " << m_coord_array.size()      << std::endl;
    std::cout << "m_value_array.size()      = " << m_value_array.size()      << std::endl;
    std::cout << "m_connection_array.size() = " << m_connection_array.size() << std::endl;
#endif
    std::cout << "m_cell_type = " << m_cell_type << std::endl;
}

int CreatePFIFile::get_pfi_unstructured_cell_type(kvs::UnstructuredVolumeObject::CellType kvs_cellType)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
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
    default:
        return 0;
    }
}

void CreatePFIFile::createPFIFile(kvs::UnstructuredVolumeObject* volume)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    FILE *pfi = NULL;
    int itmp;
    float ftmp[6];
    std::string pfiFileName = "./out/" + m_file_name + ".pfi";
    //int 

#ifdef VALUE_DEBUG
    std::cout << "m_nnodes                 = " << m_nnodes                  << std::endl;
    std::cout << "m_ncells                 = " << m_ncells                  << std::endl;
    std::cout << "m_nveclen                = " << m_nveclen                 << std::endl;
    std::cout << "volume->minObjectCoord() = " << volume->minObjectCoord()  << std::endl;
    std::cout << "volume->maxObjectCoord() = " << volume->maxObjectCoord()  << std::endl;
#endif

    pfi = fopen(pfiFileName.c_str(), "wb");
    //頂点数
    itmp = m_nnodes;
    fwrite(&itmp, 4, 1, pfi);
    //要素数
    itmp = m_ncells;
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
    itmp = m_nveclen;
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
    ftmp[0] = volume->minObjectCoord().x();
    ftmp[1] = volume->minObjectCoord().y();
    ftmp[2] = volume->minObjectCoord().z();
    ftmp[3] = volume->maxObjectCoord().x();
    ftmp[4] = volume->maxObjectCoord().y();
    ftmp[5] = volume->maxObjectCoord().z();
    fwrite(&ftmp, 4, 6, pfi);
    //サブボリュームの頂点数
    itmp = m_nnodes;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの要素数
    itmp = m_ncells;
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
