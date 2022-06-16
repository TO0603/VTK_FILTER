#include <string>
#include <iostream>

#include <VTKParameterReader.h>
#include <CreatePFIFile.h>
#include <CreateVolumeObject.h>
int main(int argc, char* argv[])
{
    //コマンドライン引数に何か入力されているかを判別
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " InputFilename e.g. hoge.vtk" << std::endl;
        return EXIT_FAILURE;
    }

    //コマンドライン引数からファイル名を取得
    std::string inputFilename = argv[1];
    int path_i = inputFilename.find_last_of("/") + 1;
    int ext_i = inputFilename.find_last_of(".");
    std::string fileName = inputFilename.substr(path_i,ext_i-path_i);

    VTKParameterReader *vtk_parameter_reader = new VTKParameterReader();
    vtk_parameter_reader->read(inputFilename);

    CreatePFIFile *createPFI = new CreatePFIFile(fileName,*vtk_parameter_reader);
    std::string kvsml_filename = createPFI->getKVSMLFileName();

    kvs::UnstructuredVolumeObject* volume = new CreateVolumeObject(*vtk_parameter_reader);
    createPFI->createPFIFile(volume);

    kvs::KVSMLUnstructuredVolumeObject* kvsml =
            new kvs::UnstructuredVolumeExporter<kvs::KVSMLUnstructuredVolumeObject>( volume );
    kvsml->setWritingDataType( kvs::KVSMLUnstructuredVolumeObject::ExternalBinary );
    kvsml->write(kvsml_filename);

    return EXIT_SUCCESS;
}
