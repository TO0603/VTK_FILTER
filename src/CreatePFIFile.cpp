#include "CreatePFIFile.h"

CreatePFIFile::CreatePFIFile(std::string fileName, EnsightFormat filterEnsight):
    m_Ensight(filterEnsight),
    m_nblocks(filterEnsight.getBlockNumber()),
    m_total_nodes(filterEnsight.getTotalNodes()),
    m_total_cells(filterEnsight.getTotalCells()),
    //m_total_bounds(filterEnsight.getTotalBounds()),
    //m_nnodes(filterEnsight.getNumberOfNodes()),
    //m_ncells(filterEnsight.getNumberOfElements()),
    //m_nveclen(filterEnsight.getNumberOfKinds()),
    //m_coord_array(filterEnsight.getCoordArray()),
    //m_value_array(filterEnsight.getValuewArray()),
    //m_connection_array(filterEnsight.getConnectionArray()),
    //m_cell_type(filterEnsight.getCellType()),
    m_nnodes(0),
    m_ncells(0),
    m_nveclen(0),
    m_coord_array(0),
    m_value_array(0),
    m_connection_array(0),
    m_cell_type(0),
    m_cell_type_index (0),
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
    //std::cout << "m_cell_type = " << m_cell_type << std::endl;
    m_sub_nnodes.allocate(m_nblocks);
    m_sub_ncells.allocate(m_nblocks);
    m_sub_coord_array.allocate(m_nblocks*6);
    filterEnsight.getMultiBlockDataSet() -> GetBounds(m_total_bounds) ; 
    m_cell_type_array.allocate(8);
}

void CreatePFIFile::update_subvolume(EnsightFormat filterEnsight,const int iblock)
{

    if(iblock == 0)
    {
        update_member_function(filterEnsight);
    }

    update_cell_type(filterEnsight);
    m_sub_nnodes.at(iblock) =  filterEnsight.getNumberOfNodes();
    std::cout << " m_sub_nnodes = " << m_sub_nnodes.at(iblock) <<std::endl; 
    m_sub_ncells.at(iblock) =  filterEnsight.getNumberOfElements();
    std::cout << " m_sub_cells = " << m_sub_ncells.at(iblock) <<std::endl; 
    double tmp[6];
    filterEnsight.getUnstructuredGrid() -> GetBounds(tmp);

    //min
    m_sub_coord_array.at(0 + iblock*6) = tmp[0];
    m_sub_coord_array.at(1 + iblock*6) = tmp[2];
    m_sub_coord_array.at(2 + iblock*6) = tmp[4];
    //max
    m_sub_coord_array.at(3 + iblock*6) = tmp[1];
    m_sub_coord_array.at(4 + iblock*6) = tmp[3];
    m_sub_coord_array.at(5 + iblock*6) = tmp[5];

    for (auto i: tmp)
    {
        std::cout << " tmp =  " << i <<std::endl;
    }

    m_min = filterEnsight.getMin();
    m_max = filterEnsight.getMax();

    for (int i = 0; i < m_nveclen; i++ )
    {
        int ii = i * 2;
        m_sub_value_array.at(ii + iblock * m_nveclen *2 )     = m_min[i];
        m_sub_value_array.at(ii + 1 + iblock * m_nveclen *2 ) = m_max[i];
    }
} 

void CreatePFIFile::update_member_function(EnsightFormat filterEnsight)
{
    m_nveclen = filterEnsight.getNumberOfKinds();
    //m_cell_type = filterEnsight.getCellType(); 
    m_sub_value_array.allocate(m_nblocks * m_nveclen * 2) ;
}

void CreatePFIFile::update_cell_type(EnsightFormat filterEnsight)
{
    int tmp_cell_type;
    tmp_cell_type = convert_celltype(filterEnsight.getCellType());

    if (!(tmp_cell_type == m_cell_type))
    {
       m_cell_type_array.at(m_cell_type_index) = tmp_cell_type; 
       m_cell_type_index ++;
 
    }
    m_cell_type = tmp_cell_type;

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

void CreatePFIFile::write_pfi()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;

    FILE *pfi = NULL;
    int itmp;
    float ftmp[6];
    //float gtmp[6 * m_nblocks];
    //std::string filename = m_out_dir + "/"+ m_basename + ".pfi"; 
    std::string pfiFileName = "./out/" + m_file_name + ".pfi";

#ifdef VALUE_DEBUG
    std::cout << "m_nnodes                 = " << m_nnodes                  << std::endl;
    std::cout << "m_ncells                 = " << m_ncells                  << std::endl;
    std::cout << "m_nveclen                = " << m_nveclen                 << std::endl;
    std::cout << "volume->minObjectCoord() = " << m_object->minObjectCoord()  << std::endl;
    std::cout << "volume->maxObjectCoord() = " << m_object->maxObjectCoord()  << std::endl;
#endif

    //m_object -> print(std::cout );

    pfi = fopen(pfiFileName.c_str(), "wb");
    //頂点数
    itmp = m_total_nodes;
    std::cout << "nnodes          = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //要素数
    itmp = m_total_cells;
    fwrite(&itmp, 4, 1, pfi);
    std::cout << "ncells          = " << itmp           << std::endl;
    //要素タイプ
    //convert_celltype();
    itmp = m_cell_type;
    std::cout << "m_cell_type     = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //ファイルタイプ
    itmp = 0;
    std::cout << "filetype        = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //ファイル数
    itmp = 1;
    std::cout << "nfile           = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //成分数(ベクトル?)
    itmp = m_nveclen;
    std::cout << "veclen          = " << itmp           <<std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //開始ステップ
    itmp = 0;
    std::cout << "strat_time      = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //終了ステップ
    itmp = 0;
    std::cout << "end_time        = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //サブボリューム数
    itmp = m_nblocks;
    std::cout << "nsubvolume      = " << itmp           << std::endl;
    fwrite(&itmp, 4, 1, pfi);
    //座標の最大最小値
    ftmp[0] = m_total_bounds[0];
    ftmp[1] = m_total_bounds[2];
    ftmp[2] = m_total_bounds[4];
    ftmp[3] = m_total_bounds[1];
    ftmp[4] = m_total_bounds[3];
    ftmp[5] = m_total_bounds[5];
    std::cout << "min_x      = " << ftmp[0]           << std::endl;
    std::cout << "min_y      = " << ftmp[1]           << std::endl;
    std::cout << "min_z      = " << ftmp[2]           << std::endl;
    std::cout << "max_x      = " << ftmp[3]           << std::endl;
    std::cout << "max_y      = " << ftmp[4]           << std::endl;
    std::cout << "max_z      = " << ftmp[5]           << std::endl;
    fwrite(&ftmp, 4, 6, pfi);
    //for ( i = 0; i< m_nblocks; i++)
    //{
    //サブボリュームの頂点数
    //itmp = m_sub_nnodes;
    //itmp = volume -> nnodes() ;
    //std::cout << "subvolume_nodes = " << itmp           << std::endl;
    fwrite(m_sub_nnodes.pointer(), 4, 1 * m_nblocks, pfi);
    //サブボリュームの要素数
    //itmp = m_sub_ncells[i];
    //itmp = volume -> ncells() ;
    //std::cout << "subvolume_ncell = " << itmp           << std::endl;
    fwrite(m_sub_ncells.pointer(), 4, 1 * m_nblocks, pfi);
    //}
    //for ( i = 0; i< m_nblocks; i++)
    //{
    //サブボリュームの座標の最大最小値
    //ftmp[0] = m_object->minObjectCoord().x();
    //ftmp[1] = m_object->minObjectCoord().y();
    //ftmp[2] = m_object->minObjectCoord().z();
    //ftmp[3] = m_object->maxObjectCoord().x();
    //ftmp[4] = m_object->maxObjectCoord().y();
    //ftmp[5] = m_object->maxObjectCoord().z();
    //std::cout << "min_x      = " << ftmp[0]           << std::endl;
    //std::cout << "min_y      = " << ftmp[1]           << std::endl;
    //std::cout << "min_z      = " << ftmp[2]           << std::endl;
    //std::cout << "max_x      = " << ftmp[3]           << std::endl;
    //std::cout << "max_y      = " << ftmp[4]           << std::endl;
    //std::cout << "max_z      = " << ftmp[5]           << std::endl;
    //fwrite(&ftmp, 4, 6, pfi);
    //}
    fwrite(m_sub_coord_array.pointer(), 4, 6*m_nblocks, pfi);
    //ステップ1の成分最小値最大値

    fwrite(m_sub_value_array.pointer(), 4, 1*m_nblocks, pfi);

    //ステップ1の成分最小値
    ////itmp = 1;
    //itmp = m_object -> minValue();
    //fwrite(&itmp, 4, 1, pfi);
    ////ステップ1の成分最大値
    ////itmp = 5;
    //itmp = m_object -> maxValue();
    //std::cout << "max             = " << itmp  <<std::endl;
    //fwrite(&itmp, 4, 1, pfi);
    fclose(pfi);
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

//void CreatePFIFile::convert_celltype()
int  CreatePFIFile::convert_celltype(int cell_type)
{
    kvsCellType conv_cell;
    int type_num;
    if(cell_type == 10) // tetrahedra
    {
        conv_cell = kvsCellType::Tetrahedra;
        type_num = 4;
        std::cout<< "conv_cell = " << conv_cell << std::endl;
    }
    else  if(cell_type == 5)  // triangle
    {
        conv_cell = kvsCellType::Triangle;
        //type_num = 3;
        type_num = 2;
    }
    else if(cell_type == 12) // hexahedra
    {
        conv_cell = kvsCellType::Hexahedra;
        type_num = 8;
    }
    else if(cell_type == 13) // Prism
    {
        conv_cell = kvsCellType::Prism;
        type_num = 6;
    }
    else if(cell_type == 14) // Pyramid
    {
        conv_cell = kvsCellType::Pyramid;
        type_num = 5;
    }
    else 
    {
        conv_cell = kvsCellType::ElementTypeUnknown; 
        type_num = 0;
    }
    //m_cell_type = conv_cell; 
    return conv_cell;
}


