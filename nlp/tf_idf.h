// Created by cuiming on 2018/4/8.

#ifndef MLPACK_TF_IDF_H
#define MLPACK_TF_IDF_H

#include <map>
#include <cmath>
#include <vector>
#include <string>

/*
 * TF     : tf_ij                                       绝对词频
 * IDF    : w_ij = log(N/n_i)                           倒排文档频度,N:总文档个数，n_i:包含词i的文档个数
 * TF-IDF : w_ij = tf_ij*log(N/n_i + 0.01)              与文档词频成正比，与整个语料频次成反比
 * TFC    : w_ij = TF-IDF/sqrt(sum(pow(TF-IDF_ij,2)))   根据文本长度归一化后的TF-IDF
 */

class TFIDF {
public:
    TFIDF();
    TFIDF(std::string freq_path);
    //normalization
    double ComputeTFC(vector<pair<string,long> > doc,int index);
    //un normalization
    double ComputeTFIDF(double tf,long n,long N);

private:
    void LoadFreq();
private:
    std::string freq_path_;
    std::map<std::string,long> freq_total_;
    long N_;
};

#endif //MLPACK_TF_IDF_H
