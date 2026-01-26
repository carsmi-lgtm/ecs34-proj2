#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

TEST(XMLReader, InitConstruction){
    std::shared_ptr<CDataSource> DataSource = std::make_shared<CStringDataSource>("<hello></hello>");
    CXMLReader reader(DataSource);

    EXPECT_FALSE(reader.End());
}

TEST(XMLReader, ReadEntity){
    std::shared_ptr<CDataSource> DataSource = std::make_shared<CStringDataSource>("<hello></hello>");
    CXMLReader reader(DataSource);

    SXMLEntity entity;
    ASSERT_TRUE(reader.ReadEntity(entity, false));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(entity.DNameData, "hello");

    ASSERT_TRUE(reader.ReadEntity(entity,false));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(entity.DNameData, "hello");
}

TEST(XMLReader, ReadEntitySkipCData){
    std::shared_ptr<CDataSource> DataSource = std::make_shared<CStringDataSource>("<hello>world</hello>");
    CXMLReader reader(DataSource);

    SXMLEntity entity;
    ASSERT_TRUE(reader.ReadEntity(entity, true));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::StartElement);
    
    ASSERT_TRUE(reader.ReadEntity(entity, true));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLWriter, InitConstruction){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter writer(DataSink);

    EXPECT_EQ(DataSink->String(), "");
}

TEST(XMLWriter, StartAndEndElement){
    std::shared_ptr<CStringDataSink> DataSink  = std::make_shared<CStringDataSink>();
    CXMLWriter writer(DataSink);

    SXMLEntity start;
    start.DType = SXMLEntity::EType::StartElement;
    start.DNameData = "hello";

    SXMLEntity end;
    end.DType = SXMLEntity::EType::EndElement;
    end.DNameData = "hello";

    ASSERT_TRUE(writer.WriteEntity(start));
    ASSERT_TRUE(writer.WriteEntity(end));
    EXPECT_EQ(DataSink->String(), "<hello></hello>");
}

TEST(XMLWriter, Flush){
    std::shared_ptr<CStringDataSink> DataSink = std::make_shared<CStringDataSink>();
    CXMLWriter writer(DataSink);

    SXMLEntity start;
    start.DType = SXMLEntity::EType::StartElement;
    start.DNameData = "hello";

    ASSERT_TRUE(writer.WriteEntity(start));
    ASSERT_TRUE(writer.Flush());
    EXPECT_EQ(DataSink->String(), "<hello></hello>");
}