#include "hdf_wrapper.hpp"
#include <sstream>
#include <vector>
int main1()
{
        auto WriteToHdfReal = [](h5cpp::Group &gr, auto &data, std::string name,int dim=1) {
            h5cpp::create_dataset(gr, name,
                                  h5cpp::Dataspace::simple_dims(int(data.size()/dim), dim),
                                  reinterpret_cast<double *>(&data[0]));
        };
        auto WriteToHdfInt = [](h5cpp::Group &gr, auto &data, std::string name,int dim=1) {
            h5cpp::create_dataset(gr, name,
                                  h5cpp::Dataspace::simple_dims(int(data.size()/dim), dim),
                                  reinterpret_cast<unsigned int *>(&data[0]));
        };
        h5cpp::File file("test.h5", "w");
        auto group = file.root().create_group("VTKHDF"); //.create_group(str.str());

        /// writing time information
        int version[]={2,0};
        //group.attrs().create<int*>("STEP", version);
        group.attrs().create<double>("TIME", 0);
        std::vector<int> dataInt;
        dataInt.resize(10,1);
        std::vector<double> dataReal;
        dataReal.resize(10,2.0);
        WriteToHdfReal(group, dataReal, "RADIUS");
/*
        COPY_VECTOR(simData->PARTICLES.POSITIONS_R,POSITIONS_R);
        COPY_VECTOR(simData->PARTICLES.VELOCITY_MASS,VELOCITY_MASS);
        COPY_VECTOR(simData->PARTICLES.ANGULAR_VELOCITY_INERTIA,ANGULAR_VELOCITY_INERTIA);
        COPY_VECTOR(simData->PARTICLES.FORCE,FORCE);
        COPY_VECTOR(simData->PARTICLES.TORQUE,TORQUE);
        COPY_VECTOR(simData->PARTICLES.BASE_RADIUS,BASE_RADIUS);
        COPY_VECTOR(simData->PARTICLES.NN_COUNT,NN_COUNT);


        std::transform(POSITIONS_R.begin(),POSITIONS_R.end(),RADIUS.begin(),[](REAL4 x) -> REAL { return x[3];});
        std::transform(VELOCITY_MASS.begin(),VELOCITY_MASS.end(),MASS.begin(),[](REAL4 x) -> REAL { return x[3];});



        WriteToHdfReal(group, RADIUS, "RADIUS");
        WriteToHdfInt(group, PARTICLE_FIX, "PARTICLE_FIX");
        WriteToHdfInt(group, PARTICLE_MATERIAL, "PARTICLE_MATERIAL");
        WriteToHdfReal(group, MASS, "MASS");
        WriteToHdfReal4(group, POSITIONS_R, "POSITIONS");
        WriteToHdfReal4(group, FORCE, "FORCE");
        WriteToHdfReal4(group, VELOCITY_MASS, "VELOCITY");
        WriteToHdfReal4(group, ANGULAR_VELOCITY_INERTIA, "ANGULAR_VELOCITY");
        WriteToHdfReal4(group, TORQUE, "TORQUE");*/
        file.close();
}




      #include <stdio.h>
#include <stdlib.h>

#include "hdf5_hl.h"

int main(int argc, char** argv){
  /* example of VTK HDF5 file format
This is a de facto HDF5 file template using specific group names and dataset hierarchy.
ParaView can also read these VTK HDF5 files.

Build: use the HDF5 compiler wrapper for convenience:

    h5cc vtk_write.c -o vtk_demo

    ./vtk_demo hi.h5

Examine HDF5 file contents:

    h5dump hi.h5

References:
https://kitware.github.io/vtk-examples/site/VTKFileFormats/#hdf-file-formats
https://www.kitware.com/vtk-hdf-reader/
https://gitlab.kitware.com/danlipsa/vtkxml-to-vtkhdf
https://gitlab.kitware.com/vtk/vtk/-/blob/master/IO/HDF/Testing/Cxx/TestHDFReader.cxx

*/






int ierr;

char vtkhdf[8] = "/VTKHDF";
char pointdata[18] = "/VTKHDF/PointData";

if(argc < 2){
  fprintf(stderr, "usage: %s <filename>\n", argv[0]);
  return EXIT_FAILURE;
}

/* create HDF5 file */
hid_t fid = H5Fcreate(argv[1], H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

hid_t gid1 = H5Gcreate2(fid, vtkhdf, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
/* avoid resource leaks by closing */
H5Gclose(gid1);

int vtk_version[2] = {1, 0};
H5LTset_attribute_int(fid, vtkhdf, "Version", vtk_version, 2);

/* ImageData example */
int direction[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
H5LTset_attribute_int(fid, vtkhdf, "Direction", direction, 9);

float origin[3] = {-1.75, -1.25, 0.};
H5LTset_attribute_float(fid, vtkhdf, "Origin", origin, 3);

float spacing[3] = {0.131579, 0.125, 0.0952381};
H5LTset_attribute_float(fid, vtkhdf, "Spacing", spacing, 3);

int whole_extent[6] = {0, 19, 0, 20, 0, 21};
H5LTset_attribute_int(fid, vtkhdf, "WholeExtent", whole_extent, 6);

H5LTset_attribute_string(fid, vtkhdf, "Type", "ImageData");


gid1 = H5Gcreate2(fid, pointdata, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

H5LTset_attribute_string(fid, pointdata, "Scalars", "IterationsGradient");

/* declare 3D array of test data */
hsize_t dims[3] = {20, 21, 22};
/* malloc array */
float* Iterations = (float*) malloc(dims[0] * dims[1] * dims[2] * sizeof(float));

/* arbitrary array values */
for(int i = 0; i < dims[0] * dims[1] * dims[2]; i++){
  Iterations[i] = (float) rand() / (float) RAND_MAX;
}

H5LTmake_dataset_float(gid1, "/Iterations", 3, dims, Iterations);

H5Gclose(gid1);

/* free memory */
free(Iterations);

H5Fclose(fid);

return EXIT_SUCCESS;


}