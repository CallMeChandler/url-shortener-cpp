#include "validation.hpp"

bool isValidUrl(const std::string& url) {
    if (url.empty()){
        return false;
    }

    bool hasHttp = url.rfind("http://", 0) == 0;

    bool hasHttps = url.rfind("https://", 0) == 0;

    if (!hasHttp && !hasHttps){
        return false;
    }

    std::size_t protocolEnd = url.find("://");

    if (protocolEnd==std::string::npos){
        return false;
    }

    std::string remaining = url.substr(protocolEnd+3);

    if (remaining.empty()){
        return false;
    }

    if (remaining.find('.')==std::string::npos){
        return false;
    }

    return true;
}