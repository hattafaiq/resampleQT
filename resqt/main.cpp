#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <chrono>
#include "resample.h"
#include <QDebug>
//dia minta c++17 bro
using namespace std;

int hcf(int n1, int n2){ //GCF = Greates common Factor, untuk menghitung ratio
    if(n2!=0) return hcf(n2,n1%n2);
    else return n1;
}

void cari(){

    int derajat = 720;
    int jum_data_derajat = 5;
    vector<int> len_data = {8021,8061,8071,8141,8141,8181,8221,8261,8301,9381};

    for(int i=0; i<(int)len_data.size(); i++){
        int n_asli = (int) len_data[i];
        int n_ingin =derajat * jum_data_derajat;//3600
        int hcfr = hcf(n_asli,n_ingin);
        int perbandingan_in = n_asli/hcfr;
        int perbandingan_out = n_ingin/hcfr;

        vector<double> input(len_data[i]), output;
        auto start = std::chrono::high_resolution_clock::now();
        resample<double> ( perbandingan_out,perbandingan_in, input, output );
        auto stop = std::chrono::high_resolution_clock::now();

        auto dur_d = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
        cout<<"RASIO_> in:" << perbandingan_in <<" && "<<" out:"<<perbandingan_out <<endl;
        cout<<"data ke:"<<i<<" in:"<<input.size() <<" out:"<<output.size()<<"\n double elapsed: "<< dur_d.count()/1e9l<<" secs";
        cout<<endl<<endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cari();
    return a.exec();
}
