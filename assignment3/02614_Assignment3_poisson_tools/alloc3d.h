extern "C" {
    double ***malloc_3d(int m, int n, int k);
    double ***d_malloc_3d(int m, int n, int k, double** data);
    void free_3d(double ***array3D);
    void d_free_3d(double ***array3D, double* data);
}
