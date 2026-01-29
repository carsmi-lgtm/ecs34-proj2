#include "XMLReader.h"

struct CXMLReader::SImplementation {
    std::shared_ptr<CDataSource> DSource;
    bool DEnd;
};

CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) : DImplementation(std::make_unique<SImplementation>()) {
    DImplementation->DSource = src;
    DImplementation->DEnd = false;
}

CXMLReader::~CXMLReader() = default;

bool CXMLReader::End() const {
    return DImplementation->DEnd;
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    return false;
}
