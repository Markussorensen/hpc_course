
extern "C" {
    void matmult_blk_omp(int M,int N,int K,double **A,double **B,double **C, int bs);
}