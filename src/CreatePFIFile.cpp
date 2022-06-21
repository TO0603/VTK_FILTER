#include "CreatePFIFile.h"

CreatePFIFile::CreatePFIFile( std::string fileName, VTKFormat vtkFormat ):
    m_vtk_format( vtkFormat ),
    m_file_name( fileName )
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
}

int CreatePFIFile::get_pfi_unstructured_cell_type( kvs::UnstructuredVolumeObject::CellType kvs_cellType )
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

void CreatePFIFile::createPFIFile( kvs::UnstructuredVolumeObject* volume )
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
    fwrite(&itmp, 4, 1, pfi);
    //要素数
    itmp = m_vtk_format.getNumberOfCells();
    fwrite(&itmp, 4, 1, pfi);
    //要素タイプ
    itmp = get_pfi_unstructured_cell_type(volume->cellType());
    fwrite(&itmp, 4, 1, pfi);
    //ファイルタイプ
    itmp = 0;
    fwrite(&itmp, 4, 1, pfi);
    //ファイル数
    itmp = 1;//
    fwrite(&itmp, 4, 1, pfi);
    //成分数(ベクトル?)
    itmp = m_vtk_format.getNumberOfKinds();
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
    itmp = m_vtk_format.getNumberOfNodes();
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの要素数
    itmp = m_vtk_format.getNumberOfCells();
    fwrite(&itmp, 4, 1, pfi);
    //サブボリュームの座標の最大最小値
    fwrite(&ftmp, 4, 6, pfi);

    for(int i = 0; i < m_vtk_format.getNumberOfKinds(); i++)
    {
        //ステップ0の成分1最小値
        oftmp = m_vtk_format.getMin().at(i);
        fwrite(&oftmp, 4, 1, pfi);
        //ステップ0の成分1最大値
        oftmp = m_vtk_format.getMax().at(i);
        fwrite(&oftmp, 4, 1, pfi);
    }    

    fwrite(&oftmp, 4, 1, pfi);
    fclose(pfi);
}
