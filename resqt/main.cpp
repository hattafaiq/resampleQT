#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <chrono>
#include "resample.h"
#include <QDebug>
//dia minta c++17 bro
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int derajat = 720;
    float jum_data_derajat = 5;
    vector<float> len_data = {8021,8061,8071,8141,8141,8181,8221,8261,8301,8381};
    int pengali_faktor = 1000;
    int pendekatan_jumlah = derajat*jum_data_derajat;
    for(int i=0; i<len_data.size(); i++){
        float faktor_sample = (len_data[i]/pendekatan_jumlah);//*pengali_faktor;
        QString pembulatan;
        pembulatan = QString::number(faktor_sample,'f',3);
        float faktor_proses_desimal = pembulatan.toFloat() *pengali_faktor;
        int faktor_to_interger = (int)faktor_proses_desimal;
        qDebug()<<"cek:"<<pembulatan <<" = "<<faktor_proses_desimal;
        cout<<"faktor :"<<faktor_to_interger << " float:"<<faktor_sample <<"\n";

        vector<double> input(len_data[i]), output;
        std::iota(input.begin(), input.end(), 1.0);
        auto start = std::chrono::high_resolution_clock::now();
        resample<double> ( pengali_faktor, faktor_to_interger, input, output );
        auto stop = std::chrono::high_resolution_clock::now();

        auto dur_d = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
        cout<<"data ke:"<<i<<" in:"<<input.size() <<" out:"<<output.size()<<"\n double elapsed: "<< dur_d.count()/1e9l<<" secs";
        cout<<endl<<endl;
    }













//    vector<float> input_f(len_data), output_f;
//    std::iota(input_f.begin(), input_f.end(), 1.0);
//    start = std::chrono::high_resolution_clock::now();
//    resample<float> ( pengali_faktor, faktor_to_interger, input_f, output_f );
//    stop = std::chrono::high_resolution_clock::now();
//    auto dur_f = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
//    cout<<"in:"<<input_f.size() <<" out:"<<output_f.size()<<"\n float  elapsed: "<< dur_f.count()/1e9l<<" secs";
//      cout<<endl<<endl;

//   //   return 0;
    return a.exec();
}
