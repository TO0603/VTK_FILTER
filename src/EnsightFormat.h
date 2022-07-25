#ifndef FILTERVTK_H
#define FILTERVTK_H
#include <string>
#include <vtkGenericDataObjectReader.h>
#include <vtkDataReader.h>
#include <vtkDataSet.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkCell.h>
#include <vtkDataArray.h>
#include <vtkIdList.h>
#include <vtkCellDataToPointData.h>
#include <vtkInformation.h>

#include <vtkGenericEnSightReader.h>
#include <vtkEnSightGoldBinaryReader.h>  
#include <vtkEnSightGoldReader.h>  
#include <vtkAppendFilter.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkUnstructuredGridAlgorithm.h>

#include <kvs/ValueArray>

class EnsightFormat
{

private:
    //vtkGenericDataObjectReader* m_reader;
    vtkUnstructuredGrid* m_reader;
    //vtkDataSet* m_output;
    vtkMultiBlockDataSet* m_MultiBlockDataSet; 
    vtkPointData* m_point_data;
    vtkCellData* m_cell_data;
    vtkDataArrayCollection * m_DataArrayCollection;
    vtkDataArray * m_DataArray;
    float* m_time;
    int m_npoint_data_arrays;//m_npoint_data_arrays
    int m_npoint_data_components;
    int m_npoint_data_tuples;
    int m_ncell_data_arrays;
    int m_ncell_data_components;
    int m_ncell_data_tuples;
    long long m_nnodes;
    long long m_nelements;
    int m_nkinds;
    int m_npoints;
    int m_cell_type;
    kvs::ValueArray<int> m_numarray_celltype; 
    kvs::ValueArray<int> id_numarray_celltype; 
    //int m_numarray_celltype[15];
    int m_block_number;
    int m_total_nodes;
    int m_total_cells;
    double m_total_bounds[6];
    kvs::ValueArray<kvs::Real32> m_coord_array;//m_coords
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;
    kvs::ValueArray<float> m_max;
    kvs::ValueArray<float> m_min;

public:
    EnsightFormat();
    void setNumberOfBlock(std::string input_vtk_file);
    void read(std::string input_vtk_file, const int i);
    void generate();
    void show_memory();
    void count_numarray_celltype();
    long long getNumberOfNodes() { return m_nnodes; }
    long long getNumberOfElements() { return m_nelements; }
    int getNumberOfKinds() { return m_nkinds; }
    int getNumberOfPoints() { return m_npoints; }
    int getCellType() { return m_cell_type; }
    kvs::ValueArray<int> getNumArrayCellType() { return m_numarray_celltype; }
    kvs::ValueArray<int> getIdNumArrayCellType() { return id_numarray_celltype; }
    int getBlockNumber() { return m_block_number; }
    int getTotalNodes() { return m_total_nodes; }
    int getTotalCells() { return m_total_cells; }
    double* getTotalBounds() { return m_total_bounds;}
    kvs::ValueArray<kvs::Real32> getValueArray() { return m_value_array; }
    kvs::ValueArray<float> getMax(){ return m_max;}
    kvs::ValueArray<float> getMin(){ return m_min;}
    vtkMultiBlockDataSet* getMultiBlockDataSet() { return m_MultiBlockDataSet; }
    vtkUnstructuredGrid* getUnstructuredGrid() {return m_reader;}

    void setNumberOfNodes(long long nnodes) { m_nnodes = nnodes; }
    void setNumberOfElements(long long nelements) { m_nelements = nelements; }
    void setNumberOfKinds(int nkinds) { m_nkinds = nkinds; }
    void setNumberOfPoints(int npoints) {  m_npoints = npoints; }
    void setCellType(int cell_type) {  m_cell_type = cell_type; }
    void count_id_celltype();

    kvs::ValueArray<kvs::Real32> getCoordArray() { return m_coord_array; }
    kvs::ValueArray<kvs::Real32> getValuewArray() { return m_value_array; }
    kvs::ValueArray<kvs::UInt32> getConnectionArray() { return m_connection_array; }
    void setCoordArray(); //名前変?そもそもpublicであってるんだろうか。
    void setValueArray();
    void setConnectionArray();

private:
    int convert_celltype(int cell_type);
    void check_vtk_data_set_type(vtkUnstructuredGrid* reader);
    void read_vtk_file_parameter(vtkUnstructuredGrid* reader);
};

#endif // FILTERVTK_H
