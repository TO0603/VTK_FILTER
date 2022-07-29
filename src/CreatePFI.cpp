#include "CreatePFI.h"

CreatePFI::CreatePFI( std::string fileName, VolumeObjectImporter volumeObjectImporter ):
    m_volume_object_importer( volumeObjectImporter ),
    m_base_name( fileName )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
}

int CreatePFI::get_pfi_unstructured_cell_type( kvs::UnstructuredVolumeObject::CellType kvs_cellType )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    switch( kvs_cellType )
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

void CreatePFI::write( kvs::UnstructuredVolumeObject* volume )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    FILE *pfi = NULL;
    int itmp;
    float ftmp[6];
    float oftmp;
    std::string pfiFileName = "./out/" + m_base_name + ".pfi";

#ifdef VALUE_DEBUG
    std::cout << "volume->minObjectCoord() = " << volume->minObjectCoord()  << std::endl;
    std::cout << "volume->maxObjectCoord() = " << volume->maxObjectCoord()  << std::endl;
#endif

    pfi = fopen(pfiFileName.c_str(), "wb");
    //頂点数
    itmp = m_volume_object_importer.getNumberOfNodes();

#ifdef VALUE_DEBUG
    std::cout << "nnode = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //要素数
    itmp = m_volume_object_importer.getNumberOfCells();

#ifdef VALUE_DEBUG
    std::cout << "ncell = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //要素タイプ
    itmp = get_pfi_unstructured_cell_type(volume->cellType());

#ifdef VALUE_DEBUG
    std::cout << "element_type = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //ファイルタイプ
    itmp = 0;

#ifdef VALUE_DEBUG
    std::cout << "file_type = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //ファイル数
    itmp = 0;//

#ifdef VALUE_DEBUG
    std::cout << "nfile = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //成分数(ベクトル?)
    itmp = m_volume_object_importer.getNumberOfKinds();

#ifdef VALUE_DEBUG
    std::cout << "nveclen = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //開始ステップ
    itmp = 0;

#ifdef VALUE_DEBUG
    std::cout << "first_step = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //終了ステップ
    itmp = 0;

#ifdef VALUE_DEBUG
    std::cout << "end step = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //サブボリューム数
    itmp = 1;

#ifdef VALUE_DEBUG
    std::cout << "nsubvolume = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //座標の最大最小値
    ftmp[0] = volume->minObjectCoord().x();
    ftmp[1] = volume->minObjectCoord().y();
    ftmp[2] = volume->minObjectCoord().z();
    ftmp[3] = volume->maxObjectCoord().x();
    ftmp[4] = volume->maxObjectCoord().y();
    ftmp[5] = volume->maxObjectCoord().z();

#ifdef VALUE_DEBUG
    std::cout << "min_x = " << ftmp[0] << std::endl;
    std::cout << "min_y = " << ftmp[1] << std::endl;
    std::cout << "min_z = " << ftmp[2] << std::endl;
    std::cout << "max_x = " << ftmp[3] << std::endl;
    std::cout << "max_y = " << ftmp[4] << std::endl;
    std::cout << "max_z = " << ftmp[5] << std::endl;
#endif

    fwrite(&ftmp, 4, 6, pfi);
    //サブボリュームの頂点数
    itmp = m_volume_object_importer.getNumberOfNodes();

#ifdef VALUE_DEBUG
    std::cout << "subvolume_nnode = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの要素数
    itmp = m_volume_object_importer.getNumberOfCells();

#ifdef VALUE_DEBUG
    std::cout << "subvolume_ncell = " << itmp << std::endl;
#endif

    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの座標の最大最小値
    fwrite(&ftmp, 4, 6, pfi);

#ifdef VALUE_DEBUG
    std::cout << "subvolume_min_x = " << ftmp[0] << std::endl;
    std::cout << "subvolume_min_y = " << ftmp[1] << std::endl;
    std::cout << "subvolume_min_z = " << ftmp[2] << std::endl;
    std::cout << "subvolume_max_x = " << ftmp[3] << std::endl;
    std::cout << "subvolume_max_y = " << ftmp[4] << std::endl;
    std::cout << "subvolume_max_z = " << ftmp[5] << std::endl;
#endif

    for(int i = 0; i < m_volume_object_importer.getNumberOfKinds(); i++)
    {
        //ステップiの成分1最小値
        oftmp = m_volume_object_importer.getMin().at(i);

#ifdef VALUE_DEBUG
        std::cout << "step[" << i << "] min_veclen = " << oftmp << std::endl;
#endif

        fwrite(&oftmp, 4, 1, pfi);
        //ステップiの成分1最大値
        oftmp = m_volume_object_importer.getMax().at(i);

#ifdef VALUE_DEBUG
        std::cout << "step[" << i << "] max_veclen = " << oftmp << std::endl;
#endif

        fwrite(&oftmp, 4, 1, pfi);
    }    

    fclose(pfi);
}
