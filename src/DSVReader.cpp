#include "DSVReader.h"

struct CDSVReader::SImplementation{
    std::shared_ptr<CDataSource> DSource;
    char DDelimiter;
    bool DEnd;
};


CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter) : DImplementation(std::make_unique<SImplementation>()){
    DImplementation->DSource = src;
    DImplementation->DDelimiter = delimiter;
    DImplementation->DEnd = false;
}

CDSVReader::~CDSVReader() = default;

bool CDSVReader::End() const{
    return false;
}

bool CDSVReader::ReadRow(std::vector<std::string> &row){
    return false;
}