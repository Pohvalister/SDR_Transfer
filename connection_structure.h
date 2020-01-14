#ifndef CONNECTION_STRUCTURE_H
#define CONNECTION_STRUCTURE_H

/* File defining request type from client to server,
 * data sent type is based on the int16 value in the begining of request
 * from client to server: if value == -1 then it is ping request for server to confirm connection
 *                        if value > 0 then it is basis request via sdr_request structure, value defines size of it
 * from server to client: if value > 0 then it defines size of raw bytedata as answer to request
 *                        if value < 0 then there is device error, so data is error of std::string type with size as -(value)
*/

#pragma pack(push, 4)
struct sdr_request{
    sdr_request(int cf, int sr, int fw)
                : center_frequency(cf)
                , sample_rate(sr)
                , frequency_width(fw)
                {

    }
    int center_frequency;
    int sample_rate;
    int frequency_width;
};
#pragma pack(pop)

#endif //CONNECTION_STRUCTURE_H
