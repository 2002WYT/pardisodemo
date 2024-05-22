#include <iostream>
#include <mkl.h>
#include <head.h>

int main() {
    const int n = 5;  // 矩阵的维度n*n
    const int nnz = 9;  // 非零元素的数量
    // CSR格式的矩阵数据
    // 矩阵长这样：A=[]
    // 1 0 2 2 0
    // 0 1 0 0 3
    // 0 0 1 2 0
    // 0 0 0 1 0
    // 0 0 0 0 2
    // 行指针，表示每行非零元素的起始位置（1-based index）
    int ia[6] = {0, 3, 5, 7, 8, nnz};
    // 列索引（1-based index）
    int ja[nnz] = {0, 2, 3, 1, 4, 2, 3, 3, 4};
    // 非零元素值
    double a[nnz] = {1,2,2,1,3,1,2,1,2};

    // 右手边向量
    double b[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    // 解向量，初始化为0
    double x[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

    // PARDISO求解器内部数据结构指针
    void *pt[64] = {0};

    // 控制参数数组
    MKL_INT iparm[64] = {0};

    // PARDISO求解器的其他参数
    MKL_INT maxfct = 1;  // 求解不同矩阵时设置为1
    MKL_INT mnum = 1;    // 求解单个矩阵时设置为1
    MKL_INT mtype = 11;  // 实数非对称矩阵
    MKL_INT phase = 13;  // 求解阶段，初始化为13
    MKL_INT nrhs = 1;    // 右手边向量数量
    MKL_INT error = 0;   // 错误标志
    MKL_INT msglvl = 0;  // 输出级别

    // 初始化iparm数组，设置PARDISO的默认参数
    iparm[0] = 1;  // 使用默认值
    iparm[1] = 2;  // 并行处理
    iparm[7] = 2;  // 内部填充
    iparm[9] = 13; // 非零对称对角线填充
    iparm[34] = 1; // 自动选择并行策略

    std::cout << "Starting PARDISO..." << std::endl;

    // 调用PARDISO求解器
    pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n, a, ia, ja, nullptr, &nrhs, iparm, &msglvl, b, x, &error);

    // 检查是否有错误
    if (error != 0) {
        std::cerr << "Error during solution: " << error << std::endl;
        return -1;
    }

    // 输出解向量
    std::cout << "Solution:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    // 释放PARDISO内部存储的内存
    phase = -1;  // 释放内存阶段
    pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n, nullptr, ia, ja, nullptr, &nrhs, iparm, &msglvl, nullptr, nullptr, &error);

    std::cout << "PARDISO finished." << std::endl;
    std::cout << "引用head.h库：func(1, 2) = " << func(1, 2) << std::endl;
    return 0;
}
