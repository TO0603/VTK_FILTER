#include <string>
#include <iostream>

#include "EnsightFormat.h"
#include "CreatePFIFile.h"
#include "SetVolumeObject.h"
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
    std::string inputFilename = "/Users/shimomurakazuya/SGI/EnsightGold/hex_vtk/hex.case";
    int path_i = inputFilename.find_last_of("/") + 1;
    int ext_i = inputFilename.find_last_of(".");
    std::string fileName = inputFilename.substr(path_i,ext_i-path_i);

    EnsightFormat *vtk = new EnsightFormat();
    vtk->read(inputFilename);
    vtk->generate();

    CreatePFIFile *createPFI = new CreatePFIFile(fileName,*vtk);
    std::string kvsml_filename = createPFI->KVSMLFileName();

    kvs::UnstructuredVolumeObject* volume = new SetVolumeObject(*vtk);
    createPFI->createPFIFile(volume);

    kvs::KVSMLUnstructuredVolumeObject* kvsml =
            new kvs::UnstructuredVolumeExporter<kvs::KVSMLUnstructuredVolumeObject>( volume );
    kvsml->setWritingDataType( kvs::KVSMLUnstructuredVolumeObject::ExternalBinary );
    kvsml->write(kvsml_filename);

    std::cout << "EXIT" << std::endl;
    return EXIT_SUCCESS;
}
