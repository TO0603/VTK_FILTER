#include "EnsightFormat.h"
#include <sys/resource.h>
#include <kvs/Math>

EnsightFormat::EnsightFormat():
    m_point_data( nullptr ),
    m_cell_data( nullptr ),
    m_npoint_data_arrays( 0 ),
    m_npoint_data_components( 0 ),
    m_npoint_data_tuples( 0 ),
    m_ncell_data_arrays( 0 ),
    m_ncell_data_components( 0 ),
    m_nnodes( 0 ),
    m_nelements( 0 ),
    m_nkinds( 0 ),
    m_npoints( 0 ),
    m_cell_type(0),
    m_block_number(0)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
}

void EnsightFormat::show_memory()
{
    // Print CPU memory info
    struct rusage usage;
    int getrusage_ret = getrusage(RUSAGE_SELF, &usage);
    // runtime_assert(getrusage_ret == 0, "InternalError");
    std::cout << "CPU mem usage: ru_maxrss = " << (double)usage.ru_maxrss/1024./1024. << " MB" << std::endl; // ru_maxrss is in unit KB
}

void EnsightFormat::setNumberOfBlock(std::string input_vtk_file)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    vtkSmartPointer<vtkEnSightGoldBinaryReader> reader = vtkEnSightGoldBinaryReader::New();

    reader->SetCaseFileName(input_vtk_file.c_str());
    reader->ReadAllVariablesOn(); 
    show_memory();
    reader->Update();
    show_memory();
    vtkMultiBlockDataSet*  output = reader->GetOutput(); 
    m_block_number =  output -> GetNumberOfBlocks(); 
    m_total_nodes  =  output -> GetNumberOfPoints();
    m_total_cells  =  output -> GetNumberOfCells(); 
    reader->PrintSelf(std::cout, vtkIndent(2));
    //reader->PrintSelf(std::cout, vtkIndent(2));
    //output->PrintSelf(std::cout, vtkIndent(2));

    //double bounds[6];
    output -> GetBounds(m_total_bounds);
    for (auto i: m_total_bounds)
    {
        std::cout << " bounds =  " << i <<std::endl;
    }

    //m_MultiBlockDataSet = vtkMultiBlockDataSet::New();
    m_MultiBlockDataSet = output;
    //m_MultiBlockDataSet -> ShallowCopy(output);
    std::cout << "num_blocks = " << m_block_number << std::endl; 

    //// get time
    //m_DataArray -> reader -> GetTimeSets() -> GetItem(0);
    //ntime = 
    //reader -> SetTimeValue(times -> GetTuple1(ntime))

    
    //debug 
    //std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    //std::cout <<  std::endl;
    //vtkDataObject* block = output ->GetBlock(0);
    //block -> PrintSelf(std::cout, vtkIndent(2));
    //m_point_data         = block->GetPointData();

    //std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    //std::cout <<  std::endl;
    //vtkInformation* info = block -> GetInformation();
    //info -> PrintSelf(std::cout, vtkIndent(2));

    //vtkDataSetAttributes* dataSetPoint = block -> GetAttributes(0); 
    //std::cout << "debug write  DataSetAttributes" << std::endl;
    //std::cout <<  std::endl;
    //dataSetPoint -> PrintSelf(std::cout, vtkIndent(2));

    //vtkFieldData* field = block -> GetFieldData();
    //std::cout << "debug write field " << std::endl;
    //std::cout <<  std::endl;
    //field -> PrintSelf(std::cout, vtkIndent(2));

    //std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    //std::cout << "append"  << std::endl;
    //vtkNew<vtkAppendFilter> append;   
    //append -> PrintSelf(std::cout, vtkIndent(2));
    //append->AddInputData(block);
    //append->Update();
    //
    //std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    //std::cout << "ugalg"  << std::endl;
    //vtkSmartPointer<vtkUnstructuredGridAlgorithm> ugAlgorithm = vtkUnstructuredGridAlgorithm::New();   
    //vtkNew<vtkUnstructuredGridAlgorithm> ugAlgorithm;
    //ugAlgorithm -> PrintSelf(std::cout, vtkIndent(2));
    //ugAlgorithm->AddInputData(0,block);
    //ugAlgorithm->Update();

    //vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkUnstructuredGrid::New();
    ////unstructuredGrid = unstructuredGrid -> SafeDownCast(block); 
    //unstructuredGrid = dynamic_cast<vtkUnstructuredGrid *>(block);
    ////m_reader = vtkUnstructuredGrid::New();
    ////unstructuredGrid->ShallowCopy(append->GetOutput());       
    ////unstructuredGrid->ShallowCopy(ugAlgorithm->GetOutput());       
    //m_reader = unstructuredGrid;

    ////debug
    ////std::cout << "debug write unstructuredGrid " << std::endl;
    //m_coord_array.allocate(24);
    //m_value_array.allocate(24);
    //m_connection_array.allocate(20);
    ////read_vtk_file_parameter(unstructuredGrid);
    ////read_vtk_file_parameter(m_reader);
}

void EnsightFormat::read(std::string input_vtk_file, const int i_block)
//void EnsightFormat::read(std::string input_vtk_file)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;

    //vtkDataObject* block[m_block_number];
    //vtkUnstructuredGrid* block[num_blocks];
    //vtkUnstructuredGridAlgorithm* block[num_blocks];
    //for (int i = 0; i < m_block_number; i ++)
    //{
    //block[i] = output->GetBlock(i);
    //}

    vtkDataObject* block = m_MultiBlockDataSet->GetBlock(i_block);

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkUnstructuredGrid::New();
    unstructuredGrid = dynamic_cast<vtkUnstructuredGrid *>(block);
    //m_reader = vtkUnstructuredGrid::New();
    //unstructuredGrid->ShallowCopy(append->GetOutput());       
    m_reader = unstructuredGrid;

}

void EnsightFormat::generate()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    read_vtk_file_parameter(m_reader);
}

void EnsightFormat::setCoordArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    for( int i = 0; i < m_nnodes; i++ )
    {
        //double* point = m_output->GetPoint(i);
        double* point = m_reader->GetPoint(i);
        m_coord_array[i * 3] = point[0];
        m_coord_array[i * 3 + 1] = point[1];
        m_coord_array[i * 3 + 2] = point[2];
#ifdef VALUE_DEBUG
        std::cout << "m_coord_array[" << i << "] = " << m_coord_array[i * 3] << "," << m_coord_array[i * 3 + 1] << "," << m_coord_array[i * 3 + 2] << std::endl;
#endif
    }
}

void EnsightFormat::setValueArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
#ifdef VALUE_DEBUG
    std::cout << "m_value_array( points )" << std::endl;
#endif
    vtkDataArray* point_data_array = NULL;
    double* point_components = NULL;
    int value_index = 0;
    for( int i = 0; i < m_npoint_data_arrays; i++ )
    {
        point_data_array = m_point_data->GetArray( i );
        for( int j = 0; j < m_npoint_data_tuples; j++ )
        {
            point_components = point_data_array->GetTuple( j );
            m_value_array[value_index] = point_components[0];
#ifdef VALUE_DEBUG            
            std::cout << "m_value_array[" << value_index << "] = "<< m_value_array[value_index] << std::endl;
#endif
            value_index++;
        }
    }
}

void EnsightFormat::setConnectionArray()
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    int new_id;
    //m_cell_type;
    vtkNew<vtkIdList> included_points;
    int connection_index = 0;
    for(int i = 0; i < m_nelements; i++)
    {
        vtkCell* element = m_reader->GetCell(i);
        m_cell_type = element->GetCellType();
        //if (i % 100 ==0)
        //{
        //std::cout << "m_cell_type = " << m_cell_type << std::endl;
        //}
        int n_points = element->GetNumberOfPoints();
        for(int j = 0; j < n_points; j++)
        {
            int id1= element->GetPointId(j);
            new_id = 1 + included_points->InsertNextId(id1);
            m_connection_array[ connection_index ] = id1;
#ifdef VALUE_DEBUG
            std::cout << "m_connection_array[" << connection_index << "] = "<< m_connection_array[j] << std::endl;
#endif
            connection_index++;
        }
    }
}


void EnsightFormat::check_vtk_data_set_type(vtkUnstructuredGrid *reader)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    read_vtk_file_parameter(reader);
}

void EnsightFormat::read_vtk_file_parameter(vtkUnstructuredGrid *reader)
{
    std::cout << __FILE__ << " : " << __func__ << " : " << __LINE__ << std::endl;
    m_point_data                      = reader->GetPointData();
    m_cell_data                       = reader->GetCellData();
    m_npoint_data_arrays              = m_point_data->GetNumberOfArrays();
    m_npoint_data_components          = m_point_data->GetNumberOfComponents();
    m_npoint_data_tuples              = m_point_data->GetNumberOfTuples();
    m_ncell_data_arrays               = m_cell_data->GetNumberOfArrays();
    m_ncell_data_components           = m_cell_data->GetNumberOfComponents();
    m_ncell_data_tuples               = m_cell_data->GetNumberOfTuples();
    m_nnodes                          = reader->GetNumberOfPoints();
    m_nelements                       = reader->GetNumberOfCells();
    m_nkinds                          = m_npoint_data_components + m_ncell_data_components;
    m_npoints                         = reader->GetCell( 0 )->GetNumberOfPoints();
    m_coord_array.allocate(m_nnodes * 3);
    m_value_array.allocate(m_nnodes * m_nkinds);
    m_connection_array.allocate(m_nelements * m_npoints);
    m_min.allocate( m_nkinds );
    m_max.allocate( m_nkinds );

//#ifdef VALUE_DEBUG
    std::cout << "m_npoint_data_arrays     = " << m_npoint_data_arrays     << std::endl;
    std::cout << "m_npoint_data_components = " << m_npoint_data_components << std::endl;
    std::cout << "m_npoint_data_tuples     = " << m_npoint_data_tuples     << std::endl;
    std::cout << "m_ncell_data_arrays      = " << m_ncell_data_arrays      << std::endl;
    std::cout << "m_ncell_data_components  = " << m_ncell_data_components  << std::endl;
    std::cout << "m_ncell_data_tuples      = " << m_ncell_data_tuples      << std::endl;
    std::cout << "m_nnodes                 = " << m_nnodes                 << std::endl;
    std::cout << "m_nelements              = " << m_nelements              << std::endl;
    std::cout << "m_nkinds                 = " << m_nkinds                 << std::endl;
    std::cout << "m_npoints                = " << m_npoints                << std::endl;
    std::cout << "m_value_array.size()      = " << m_value_array.size()      << std::endl;
//#endif

    this->setCoordArray();
    this->setValueArray();
    this->setConnectionArray();

    int values_index = 0;
    for( int i = 0; i < m_nkinds; i++ )
    {
        getMin().at(i) = getValueArray().at(i * m_nnodes);
        getMax().at(i) = getValueArray().at(i * m_nnodes);
        for( int j = 0; j < getNumberOfNodes(); j++ )
        {
            float tmp = getValueArray().at(values_index);
    //std::cout << "tmp_" <<    i   << "_" << j <<  " = " << tmp            << std::endl;
            getMin().at(i) = kvs::Math::Min<float>(getMin().at(i),tmp);
            getMax().at(i) = kvs::Math::Max<float>(getMax().at(i),tmp);
            values_index++;
        }
    std::cout << "m_min                = " << getMin().at(i)                << std::endl;
    std::cout << "m_max                = " << getMax().at(i)                 << std::endl;
    }  

}
