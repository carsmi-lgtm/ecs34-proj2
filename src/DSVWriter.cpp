#include "DSVWriter.h"

struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> DSink;
    char DDelimiter;
    bool DQuoteAll;
};

CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) : DImplementation(std::make_unique<SImplementation>()){
    DImplementation->DSink = sink;
    DImplementation->DDelimiter = delimiter;
    DImplementation->DQuoteAll = quoteall;
}

CDSVWriter::~CDSVWriter() = default;

bool CDSVWriter::WriteRow(const std::vector<std::string> &row){

    char delim = DImplementation->DDelimiter;
    
    // delimiter specified as double quote becomes a comma
    if (delim == '"'){
        delim = ',';
    }

    for (size_t i = 0; i < row.size(); ++i){
        std::string Str = row[i];

        bool UseQuotes = false;

        // flip UseQuotes to true if encounter delimeter or quote or newline
        for (char c : Str){
            if (c == delim || c == '"' || c == '\n'){
                UseQuotes = true;
                break;
            }
        }
        
        // start quotes
        if (UseQuotes == true){
            DImplementation->DSink->Put('"');
        }

        // write characters to cell
        for (char c : Str){
            if (c == '"'){
                DImplementation->DSink->Put('"'); // escape quotes by adding extra quote
            }
            DImplementation->DSink->Put(c);
        }

        // end quotes
        if (UseQuotes == true){
            DImplementation->DSink->Put('"');
        }

        // delimiter between cells
        if (i != row.size()){
            DImplementation->DSink->Put(delim);
        }

        return DImplementation->DSink->Put('\n');

    }

    return false;
}