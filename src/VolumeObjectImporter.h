#ifndef CREATEVOLUMEOBJECT_H
#define CREATEVOLUMEOBJECT_H

#include <kvs/UnstructuredVolumeObject>
#include <VTKFormat.h>

class VolumeObjectImporter : public kvs::UnstructuredVolumeObject
{
private:
    VTKFormat* m_vtk_format;
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
    kvs::ValueArray<float> m_min;
    kvs::ValueArray<float> m_max;

public:
    VolumeObjectImporter( VTKFormat vtkFormat );
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
    kvs::ValueArray<float> getMin() { return m_min; }
    kvs::ValueArray<float> getMax() { return m_max; }

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
//    void setMin(float min) { m_min = min; }
//    void setMax(float max) { m_max = max; }

private:
    kvs::UnstructuredVolumeObject::CellType convert_vtk_cell_type_to_kvs_cell_type( int vtk_cell_type );
    void create_unstructured_volume_object();
    void check_vtk_data_set_type( vtkGenericDataObjectReader* reader );
    void vtk_file_parameter( vtkGenericDataObjectReader* reader ); //

};

#endif // CREATEVOLUMEOBJECT_H
