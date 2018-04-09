// Created by cuiming on 2018/4/8.


#include "tf_idf.h"
#include <fstream>

using namespace std;

TFIDF::TFIDF() {}

TFIDF::TFIDF(std::string freq_path) {
    this->freq_path_ = freq_path;
    LoadFreq();
}

double TFIDF::ComputeTFIDF(long tf, long n, long N) {
    return 1.0*tf*log(1.0*N/n + 0.01);
}

double TFIDF::ComputeTFC(vector <string> doc,int index) {
    double tfc;
    double normalization_factor = 0.0;
    for(int idx = 0;idx<doc.size();idx++){
        long n = freq_total_[doc[idx].first];
        long tf = doc[idx].second;
        double tf_idf = ComputeTFIDF(tf,n,N_);
        if(index == idx) tfc = tf_idf;
        normalization_factor += tf_idf;
    }
    return tfc/(normalization_factor+1e-8);
}
/*
 * freq file format:
 * first line: total:document count
 * other line: word\tfreq
 */
void TFIDF::LoadFreq() {
    ifstream fs(this->freq_path_.c_str());
    if(!fs.is_open()){
        cout<<"open freq file failed"<<endl;
        return;
    }
    string line;
    vector<string> arr;
    fs.read(line);
    split(arr,line,boost::is_any_of(":"));
    if(arr.size()<2){
        cout<<"first line of the file should total:count format"<<endl;
        return;
    }
    N_ = boost::lexical_cast<long>(arr[1]);
    while(fs.read(line) != EOF){
        split(arr,line,boost::is_any_of("\t"));
        if(arr.size<2) continue;
        freq_total_[arr[0]] = boost::lexical_cast<long>(arr[1]);
    }
}