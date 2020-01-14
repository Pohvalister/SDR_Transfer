#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H

#include <optional>
#include <QString>

#include "../connection_structure.h"

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

extern sdr_request out_request;

#endif // CONNECTION_INFO_H
