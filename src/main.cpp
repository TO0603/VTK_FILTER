#include <string>
#include <iostream>

#include "EnsightFormat.h"
#include "CreatePFIFile.h"
#include "SetVolumeObject.h"
#include "filter_write.h"
int main(int argc, char* argv[])
{
    //    //コマンドライン引数に何か入力されているかを判別
    //    if (argc != 2)
    //    {
    //        std::cerr << "Usage: " << argv[0] << " InputFilename e.g. hoge.vtk" << std::endl;
    //        return EXIT_FAILURE;
    //    }

    //コマンドライン引数からファイル名を取得
    //std::string inputFilename = argv[1];
    //std::string inputFilename = "/Users/shimomurakazuya/SGI/EnsightGold/hex_vtk/hex.case";
    //std::string inputFilename = "/Users/shimomurakazuya/SGI/EnsightGold/SHRT45R_TR_PSSP.case";
    //std::string inputFilename = "/Users/shimomurakazuya/SGI/EnsightGold/hex_vtk/TestTetra.case";
    std::string inputFilename = "/Users/shimomurakazuya/SGI/EnsightGold/time/TestTetraTime.case";
    int path_i = inputFilename.find_last_of("/") + 1;
    int ext_i = inputFilename.find_last_of(".");
    std::string fileName = inputFilename.substr(path_i,ext_i-path_i);

    EnsightFormat *ens = new EnsightFormat();
    ens->setNumberOfBlock(inputFilename);
    int block_number = ens ->getBlockNumber();
    int time_step = ens ->getTimeStep();
    //int block_number = 1;

    for (int i_block = 0; i_block < block_number ; i_block++)
    {
        ens->read(inputFilename, i_block, 0);
        //ens->generate();
        //ens->count_numarray_celltype(); 
        ens->check_ensight_data_cell_type(); 
    }

    CreatePFIFile *createPFI = new CreatePFIFile(fileName, *ens);
    createPFI-> update_member_function(*ens);  

    for (int i_step = 0; i_step < time_step ; i_step++)
    {
        for (int i_block = 0; i_block < block_number ; i_block++)
        {
            ens->read(inputFilename, i_block, i_step);
            ens->generate();
            ens->count_id_celltype();

            Filter_write* filter_write = new Filter_write(fileName, *ens, i_block, i_step); 
            filter_write->write_kvsml_xmls_single();
            filter_write->write_kvsml_value_single();
            if (i_step == 0)
            {
                filter_write->write_kvsml_geom();
            }

            createPFI -> update_subvolume(*ens, i_block, i_step);

            delete filter_write;
        } // ens loop block_num
    } // end loop timestep

    createPFI->write_pfi();
    createPFI->write_pfl(); 
    delete createPFI;

    std::cout << "EXIT" << std::endl;
    return EXIT_SUCCESS;
}
