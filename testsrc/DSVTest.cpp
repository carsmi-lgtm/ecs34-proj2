#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

// DSV READER TESTS

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

TEST(DSVReader, TestReadRow_emptyrow){
    auto src = std::make_shared< CStringDataSource >("\n");
    CDSVReader reader1(src, ',');

    std::vector<std::string> row;
    ASSERT_TRUE(reader1.ReadRow(row));
    EXPECT_TRUE(row.empty());
    EXPECT_EQ(row.size(), 0);
}

TEST(DSVReader, TestReadRow_emptycells){
    auto src = std::make_shared< CStringDataSource >(",\n");
    CDSVReader reader1(src, ',');

    std::vector<std::string> row;
    ASSERT_TRUE(reader1.ReadRow(row));
    EXPECT_EQ(row[0], "");
    EXPECT_EQ(row[1], "");
    EXPECT_EQ(row.size(), 2);
}

/* figure this out

TEST(DSVReader, TestReadRow_doublequoteincell){
    auto src = std::make_shared< CStringDataSource >("\"Say ""Hello""\", \"World!\n\"");
    CDSVReader reader1(src, ',');

    std::vector<std::string> row;
    ASSERT_TRUE(reader1.ReadRow(row));
    EXPECT_EQ(row[0], "Say \"Hello\"");
    EXPECT_EQ(row[1], "World!");
    EXPECT_EQ(row.size(), 2);
    
}*/

TEST(DSVReader, End){
    auto src = std::make_shared< CStringDataSource >("Hello,World,!\n");
    CDSVReader reader1(src, ',');

    EXPECT_FALSE(reader1.End());
}


// DSV WRITER TESTS

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
    EXPECT_EQ(sink->String(), "Hello,World,!\n");
}

TEST(DSVWriter, TestWriteRow_emptyrow){
    auto sink = std::make_shared< CStringDataSink >();
    CDSVWriter writer1(sink, ',', false);

    std::vector<std::string> row = {};
    ASSERT_TRUE(writer1.WriteRow(row));
    EXPECT_EQ(sink->String(), "\n");
}

TEST(DSVWriter, TestWriteRow_doublequotedelim){
    auto sink = std::make_shared< CStringDataSink >();
    CDSVWriter writer1(sink, '"', false);

    std::vector<std::string> row = {"a", "b", "c", "d"};
    ASSERT_TRUE(writer1.WriteRow(row));
    EXPECT_EQ(sink->String(), "a,b,c,d\n");
}