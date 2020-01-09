#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H

#include <optional>
#include <QString>

struct connection_info{

    connection_info(QString name, int port_num)
        : hostName (name)
        , port(port_num)
    {
    }

    QString hostName;
    int port;

};

extern std::optional<connection_info> server_info;

#pragma pack(push, 4)
struct data_request{
    data_request(int cf, int sr, int fw)
        : center_frequency(cf)
        , sample_rate(sr)
        , frequency_width(fw)
    {
    }
    data_request(){
    }
    int center_frequency;
    int sample_rate;
    int frequency_width;
};
#pragma pack(pop)

extern data_request sdr_request;

#endif // CONNECTION_INFO_H
