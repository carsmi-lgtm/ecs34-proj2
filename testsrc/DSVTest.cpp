#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

TEST(DSVReader, InitConstruction){
    auto src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');
    EXPECT_FALSE(reader1.End());
}

TEST(DSVReader, TestReadRow){
    auto src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');

    std::vector<std::string> row;
    ASSERT_TRUE(reader1.ReadRow(row));
    EXPECT_EQ(row[0], "Hello");
    EXPECT_EQ(row[1], "World");
    EXPECT_EQ(row[2], "!");
    EXPECT_EQ(row.size(), 3);
    
}

TEST(DSVReader, End){
    auto src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');

    EXPECT_FALSE(reader1.End());
}

TEST(DSVWriter, InitConstruction){
    auto sink = std::make_shared< CStringDataSink >();
    CDSVWriter writer1(sink, ',', false);

    EXPECT_EQ(sink->String(), "");
}

TEST(DSVWriter, TestWriteRow){
    auto sink = std::make_shared< CStringDataSink >();
    CDSVWriter writer1(sink, ',', false);

    std::vector<std::string> row = {"Hello", "World", "!"};
    ASSERT_TRUE(writer1.WriteRow(row));
    EXPECT_EQ(sink->String(), "Hello,World,!");
}