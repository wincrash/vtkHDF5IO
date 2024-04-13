import h5py #Uses UTF-8 by default
import numpy as np

with h5py.File("wtf.hdf",'w') as hdffile:

        # write support data
        vtkhdf_group = hdffile.create_group("VTKHDF")
        vtkhdf_group.attrs.create("Version", [1, 0])

        #vtkhdf_group.attrs.create("Type","ImageData") # UTF-8
        vtkhdf_group.attrs.create("Type",np.string_("ImageData")) # ascii fixed length string
        whole_extent = (0, 3, 0, 1, 0, 0)
        vtkhdf_group.attrs.create("WholeExtent", whole_extent)

        vtkhdf_group.attrs.create("Origin", (0.0, 0.0, 0.0))
        vtkhdf_group.attrs.create("Spacing", (1.0, 1.0, 1.0))
        vtkhdf_group.attrs.create("Direction", (1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0))

        # create the pointdata group and the dataset inside it
        field_data_group = vtkhdf_group.create_group("PointData")
        field_data_group.attrs.create('Scalars', "PNGImage") ## UTF-8 seems to work here
        dset = field_data_group.create_dataset('PNGImage',dtype=np.uint8,shape=(2,4))

        dset[:, :] = np.reshape([1.0,2.3,3.1,4.5,\
                                    1.0,2.3,3.1,4.5],(2, 4))
