#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

TEST(XMLReader, Construction){
    std::shared_ptr<CDataSource> DataSource = std::make_shared<CStringDataSource>("<hello></hello>");
    CXMLReader reader(DataSource);

    EXPECT_FALSE(reader.End());
}

TEST(XMLReader, ReadEntity){
    std::shared_ptr<CDataSource> DataSource = std::make_shared<CStringDataSource>("<hello></hello>");
    CXMLReader reader(DataSource);

    SXMLEntity entity;
    EXPECT_FALSE(reader.ReadEntity(entity, false));
}

TEST(XMLReader, ReadEntitySkipCData){
    std::shared_ptr<CDataSource> DataSource = std::make_shared<CStringDataSource>("<hello></hello>");
    CXMLReader reader(DataSource);

    SXMLEntity entity;
    EXPECT_FALSE(reader.ReadEntity(entity, true));
}

TEST(XMLWriter, Construction){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter writer(DataSink);

    EXPECT_TRUE(DataSink->String().empty());
    EXPECT_EQ(DataSink->String(), "");
}

TEST(XMLWriter, WriteEntity){
    std::shared_ptr<CStringDataSink> DataSink  = std::make_shared<CStringDataSink>();
    CXMLWriter writer(DataSink);

    SXMLEntity entity;
    EXPECT_FALSE(writer.WriteEntity(entity));
    EXPECT_EQ(DataSink->String(), "");
}

TEST(XMLWriter, Flush){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter writer(DataSink);

    SXMLEntity entity;
    EXPECT_FALSE(writer.Flush());
    EXPECT_EQ(DataSink->String(), "");
}
