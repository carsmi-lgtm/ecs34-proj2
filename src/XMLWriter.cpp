#include "XMLWriter.h"

struct CXMLWriter::SImplementation {
    std::shared_ptr<CDataSink> DSink;
};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink) : DImplementation(std::make_unique<SImplementation>()) {
    DImplementation->DSink = sink;
}

CXMLWriter::~CXMLWriter() = default;

bool CXMLWriter::Flush() {
    return false;
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
    return false;
}
