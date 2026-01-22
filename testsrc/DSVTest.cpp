#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

TEST(DSVReader, Construction){
    std::shared_ptr<CDataSource> src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');
    EXPECT_TRUE(true);
}

TEST(DSVReader, TReadRow){
    std::shared_ptr<CDataSource> src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');

    std::vector<std::string> row;
    EXPECT_FALSE(reader1.ReadRow(row));
}

TEST(DSVReader, End){
    std::shared_ptr<CDataSource> src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');

    EXPECT_FALSE(reader1.End());
}

TEST(DSVWriter, Construction){
    std::shared_ptr<CDataSink> sink = std::make_shared< CStringDataSink >();
    CDSVWriter writer1(sink, ',', false);

    EXPECT_TRUE(true);
}

TEST(DSVWriter, TWriteRow){
    std::shared_ptr<CDataSink> sink = std::make_shared< CStringDataSink >();
    CDSVWriter writer1(sink, ',', false);

    std::vector<std::string> row = {"Hello", "World", "!"};
    EXPECT_FALSE(writer1.WriteRow(row));
}