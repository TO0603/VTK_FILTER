#include "CreatePFIFile.h"

CreatePFIFile::CreatePFIFile(std::string fileName, EnsightFormat filterEnsight):
    m_Ensight(filterEnsight),
    m_nblocks(filterEnsight.getBlockNumber()),
    m_timesteps(filterEnsight.getTimeStep()),
    m_total_nodes(filterEnsight.getTotalNodes()),
    m_total_cells(filterEnsight.getTotalCells()),
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
    std::cout << "m_cell_type = " << m_cell_type << std::endl;
    std::cout << "m_timesteps = " << m_timesteps << std::endl;
#endif
    m_sub_nnodes.allocate(m_nblocks);
    m_sub_ncells.allocate(m_nblocks);
    m_sub_coord_array.allocate(m_nblocks * 6);
    filterEnsight.getMultiBlockDataSet() -> GetBounds(m_total_bounds) ; 
    m_numarray_celltype.allocate(15);
    m_numarray_celltype = filterEnsight.getNumArrayCellType();    
    for (int i = 0; i< 15; i++)
    {
        std::cout << "m_numarray_celltype = "<< m_numarray_celltype.at(i) <<std::endl;
    }
}

void CreatePFIFile::update_subvolume(EnsightFormat filterEnsight, const int iblock, const int i_step)
{
    if(i_step == 0)
    { 
        m_sub_nnodes.at(iblock) =  filterEnsight.getNumberOfNodes();
        m_sub_ncells.at(iblock) =  filterEnsight.getNumberOfElements();
        //std::cout << " m_sub_nnodes = " << m_sub_nnodes.at(iblock) <<std::endl; 
        //std::cout << " m_sub_cells = " << m_sub_ncells.at(iblock) <<std::endl; 
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

        //    for (auto i: tmp)
        //    {
        //        std::cout << " tmp =  " << i <<std::endl;
        //    }

    }

    m_min = filterEnsight.getMin();
    m_max = filterEnsight.getMax();

    for (int i = 0; i < m_nveclen; i++ )
    {
        int ii = i * 2 + i_step * m_nveclen * 2;
        m_sub_value_array.at(ii + iblock * m_nveclen *2 )     = m_min[i];
        m_sub_value_array.at(ii + 1 + iblock * m_nveclen *2 ) = m_max[i];
    }
} 

void CreatePFIFile::update_member_function(EnsightFormat filterEnsight)
{
    m_nveclen = filterEnsight.getNumberOfKinds();
    m_sub_value_array.allocate(m_timesteps * m_nblocks * m_nveclen * 2) ;
}

void CreatePFIFile::write_pfi()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;

    FILE *pfi = NULL;
    int itmp;
    float ftmp[6];

//#ifdef VALUE_DEBUG
    for (auto i: m_numarray_celltype)
    {
        std::cout << "m_numarray_celltype = "<< i <<std::endl;
    }
//#endif

    for (int i = 0; i < 15; i++ )
    {
        if ( m_numarray_celltype.at(i) == 0) { continue; }
        std::string pfiFileName = "./out/" + std::to_string(i) + "_" + m_file_name + ".pfi";

#ifdef VALUE_DEBUG
        std::cout << "m_nnodes                 = " << m_nnodes                  << std::endl;
        std::cout << "m_ncells                 = " << m_ncells                  << std::endl;
        std::cout << "m_nveclen                = " << m_nveclen                 << std::endl;
        std::cout << "volume->minObjectCoord() = " << m_object->minObjectCoord()  << std::endl;
        std::cout << "volume->maxObjectCoord() = " << m_object->maxObjectCoord()  << std::endl;
#endif

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
        itmp = i;
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
        itmp = m_timesteps - 1;
        std::cout << "end_time        = " << itmp           << std::endl;
        fwrite(&itmp, 4, 1, pfi);
        //サブボリューム数
        itmp = m_numarray_celltype[i];
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
        //サブボリュームの頂点数
        fwrite(m_sub_nnodes.pointer(), 4, 1 * m_numarray_celltype[i], pfi);
        //サブボリュームの要素数
        fwrite(m_sub_ncells.pointer(), 4, 1 * m_numarray_celltype[i], pfi);
        //サブボリュームの座標の最大最小値
        fwrite(m_sub_coord_array.pointer(), 4, 6*m_numarray_celltype[i], pfi);
        //ステップ1~Nの成分最小値最大値
        //fwrite(m_sub_value_array.pointer(), 4, 1*m_numarray_celltype[i], pfi);
        fwrite(m_sub_value_array.pointer(), 4, m_timesteps*m_numarray_celltype[i], pfi);
        fclose(pfi);
    } //end loop m_numarray_celltype

}

void CreatePFIFile::write_pfl()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    FILE *ifs = NULL;

    std::string filename;    
    std::string pfi_filename;
    filename = "./out/" +  m_file_name + ".pfl"; 

    ifs = fopen(filename.c_str(), "w"); 
    fprintf(ifs, "#PBVR PFI FILES\n");

    for (int i = 0; i < 15; i++ )
    {
        if ( m_numarray_celltype[i] == 0) { continue; }
        std::string pfiFileName =  std::to_string(i) + "_" + m_file_name + ".pfi";

        fprintf(ifs, "%s\n", pfiFileName.c_str() );
    }
    fclose(ifs);
}



