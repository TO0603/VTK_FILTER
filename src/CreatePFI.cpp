#include "CreatePFI.h"

CreatePFI::CreatePFI( std::string fileName, VTKFormat vtkFormat ):
    m_vtk_format( vtkFormat ),
    m_file_name( fileName )
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

void CreatePFI::createPFIFile( kvs::UnstructuredVolumeObject* volume )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    FILE *pfi = NULL;
    int itmp;
    float ftmp[6];
    float oftmp;
    std::string pfiFileName = "./out/" + m_file_name + ".pfi";

#ifdef VALUE_DEBUG
    std::cout << "volume->minObjectCoord() = " << volume->minObjectCoord()  << std::endl;
    std::cout << "volume->maxObjectCoord() = " << volume->maxObjectCoord()  << std::endl;
#endif

    pfi = fopen(pfiFileName.c_str(), "wb");
    //頂点数
    itmp = m_vtk_format.getNumberOfNodes();
    std::cout << "nnode = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //要素数
    itmp = m_vtk_format.getNumberOfCells();
    std::cout << "ncell = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //要素タイプ
    itmp = get_pfi_unstructured_cell_type(volume->cellType());
    std::cout << "element_type = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //ファイルタイプ
    itmp = 0;
    std::cout << "file_type = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //ファイル数
    itmp = 0;//
    std::cout << "nfile = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //成分数(ベクトル?)
    itmp = m_vtk_format.getNumberOfKinds();
    std::cout << "nveclen = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //開始ステップ
    itmp = 1;
    std::cout << "first_step = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //終了ステップ
    itmp = 1;
    std::cout << "end step = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリューム数
    itmp = 1;
    std::cout << "nsubvolume = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //座標の最大最小値
    ftmp[0] = volume->minObjectCoord().x();
    ftmp[1] = volume->minObjectCoord().y();
    ftmp[2] = volume->minObjectCoord().z();
    ftmp[3] = volume->maxObjectCoord().x();
    ftmp[4] = volume->maxObjectCoord().y();
    ftmp[5] = volume->maxObjectCoord().z();
    std::cout << "min_x = " << ftmp[0] << std::endl;
    std::cout << "min_y = " << ftmp[1] << std::endl;
    std::cout << "min_z = " << ftmp[2] << std::endl;
    std::cout << "max_x = " << ftmp[3] << std::endl;
    std::cout << "max_y = " << ftmp[4] << std::endl;
    std::cout << "max_z = " << ftmp[5] << std::endl;
    fwrite(&ftmp, 4, 6, pfi);
    //サブボリュームの頂点数
    itmp = m_vtk_format.getNumberOfNodes();
    std::cout << "subvolume_nnode = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの要素数
    itmp = m_vtk_format.getNumberOfCells();
    std::cout << "subvolume_ncell = " << itmp << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの座標の最大最小値
    fwrite(&ftmp, 4, 6, pfi);
    std::cout << "subvolume_min_x = " << ftmp[0] << std::endl;
    std::cout << "subvolume_min_y = " << ftmp[1] << std::endl;
    std::cout << "subvolume_min_z = " << ftmp[2] << std::endl;
    std::cout << "subvolume_max_x = " << ftmp[3] << std::endl;
    std::cout << "subvolume_max_y = " << ftmp[4] << std::endl;
    std::cout << "subvolume_max_z = " << ftmp[5] << std::endl;
    for(int i = 0; i < m_vtk_format.getNumberOfKinds(); i++)
    {
        //ステップiの成分1最小値
        oftmp = m_vtk_format.getMin().at(i);
        std::cout << "step[" << i << "] min_veclen = " << oftmp << std::endl;
        fwrite(&oftmp, 4, 1, pfi);
        //ステップiの成分1最大値
        oftmp = m_vtk_format.getMax().at(i);
        std::cout << "step[" << i << "] max_veclen = " << oftmp << std::endl;
        fwrite(&oftmp, 4, 1, pfi);
    }    

    fclose(pfi);
}
