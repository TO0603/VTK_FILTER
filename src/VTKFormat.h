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
#include <kvs/ValueArray>

class VTKFormat
{

private:
    vtkGenericDataObjectReader* m_reader;//
    vtkDataSet* m_reader_output;//
    int m_nfield_data_in_file;
    int m_nscalars_in_file;
    vtkPointData* m_point_data;//
    vtkCellData* m_cell_data;//
    int m_npoint_data_arrays;
    int m_npoint_data_components;
    int m_npoint_data_tuples;
    int m_ncell_data_arrays;
    int m_ncell_data_components;
    int m_ncell_data_tuples;

    long long m_nnodes;
    long long m_ncells;
    int m_nkinds;
    int m_npoints;
    int m_cell_type;
    kvs::ValueArray<kvs::Real32> m_coord_array;
    kvs::ValueArray<kvs::Real32> m_value_array;
    kvs::ValueArray<kvs::UInt32> m_connection_array;

public:
    VTKFormat();
    void read( std::string input_vtk_file );
    void generate();

    int getNumberOfFieldDataInFile() { return m_nfield_data_in_file; }
    int getNumberOfScalarsDataInFile() { return m_nscalars_in_file; }
    int getNumberOfPointDataArrays() { return m_npoint_data_arrays; }
    int getNumberOfPointDataComponents() { return m_npoint_data_components; }
    int getNumberOfPointDataTuples() { return m_npoint_data_tuples; }
    int getNumberOfCellDataArrays() { return m_ncell_data_arrays; }
    int getNumberOfCellDataComponents() { return m_ncell_data_components; }
    int getNumberOfCellDataTuples() { return m_ncell_data_tuples; }
    long long getNumberOfNodes() { return m_nnodes; }
    long long getNumberOfCells() { return m_ncells; }
    int getNumberOfKinds() { return m_nkinds; }
    int getNumberOfPoints() { return m_npoints; }
    int getCellType() { return m_cell_type; }
    kvs::ValueArray<kvs::Real32> getCoordArray() { return m_coord_array; }
    kvs::ValueArray<kvs::Real32> getValuewArray() { return m_value_array; }
    kvs::ValueArray<kvs::UInt32> getConnectionArray() { return m_connection_array; }

    void setNumberOfFieldDataInFile( int nfield_data_in_file ) { m_nfield_data_in_file = nfield_data_in_file; }
    void setNumberOfScalarsDataInFile (int nscalars_in_file ) { m_nscalars_in_file = nscalars_in_file; }
    void setNumberOfPointDataArrays( int npoint_data_arrays ) { m_npoint_data_arrays = npoint_data_arrays; }
    void setNumberOfPointDataComponents( int npoint_data_components ) { m_npoint_data_components = npoint_data_components; }
    void setNumberOfPointDataTuples( int npoint_data_tuples ) { m_npoint_data_tuples = npoint_data_tuples; }
    void setNumberOfCellDataArrays( int ncell_data_arrays ) { m_ncell_data_arrays = ncell_data_arrays; }
    void setNumberOfCellDataComponents( int ncell_data_components ) { m_ncell_data_components = ncell_data_components; }
    void setNumberOfCellDataTuples( int ncell_data_tuples ) { m_ncell_data_tuples = ncell_data_tuples; }
    void setNumberOfNodes( long long nnodes ) { m_nnodes = nnodes; }
    void setNumberOfCells( long long ncells ) { m_ncells = ncells; }
    void setNumberOfKinds( int nkinds ) { m_nkinds = nkinds; }
    void setNumberOfPoints( int npoints ) { m_npoints = npoints; }
    void setCellType( int cell_type ) { m_cell_type = cell_type; }
    void setCoordArray();
    void setValueArray();
    void setConnectionArray();

private:
    void check_vtk_data_set_type( vtkGenericDataObjectReader* reader );
    void vtk_file_parameter( vtkGenericDataObjectReader* reader ); //
};

#endif // FILTERVTK_H
