#include "libdxfrw.h"
#include "drw_base.h"
#include "drw_classes.h"
#include "drw_entities.h"
#include "drw_header.h"
#include "drw_interface.h"
#include "drw_objects.h"
#include "libdwgr.h"
#include "main_doc.h"

#include <iostream>
#include <memory>

class SimpleWriter : public DRW_Interface {
public:
       void addCircle(double centerX, double centerY, double radius, const std::string& layer = "0") {
        DRW_Circle circle;
        circle.basePoint.x = centerX;
        circle.basePoint.y = centerY;
        circle.basePoint.z = 0.0;
        circle.radious = radius;
        circle.layer = layer;
        //circles.push_back(circle);
    }

    void addLine(double x1, double y1, double x2, double y2, const std::string& layer = "0") {
        DRW_Line line;
        line.basePoint.x = x1;
        line.basePoint.y = y1;
        line.basePoint.z = 0.0;
        line.secPoint.x = x2;
        line.secPoint.y = y2;
        line.secPoint.z = 0.0;
        line.layer = layer;
        //lines.push_back(line);
    }

    void addText(double x, double y, const std::string& text, double height = 10.0, const std::string& layer = "0") {
        DRW_Text dxfText;
        dxfText.basePoint.x = x;
        dxfText.basePoint.y = y;
        dxfText.basePoint.z = 0.0;
        dxfText.height = height;
        dxfText.text = text;
        dxfText.layer = layer;
        //texts.push_back(dxfText);
    }

    // Override all pure virtual functions from DRW_Interface
    void addHeader(const DRW_Header* data) override {
        if (data) {
            //header = *data;
        }
    }

    void addLType(const DRW_LType& data) override {}
    void addLayer(const DRW_Layer& data) override {}
    void addDimStyle(const DRW_Dimstyle& data) override {}
    void addVport(const DRW_Vport& data) override {}
    void addTextStyle(const DRW_Textstyle& data) override {}
    void addAppId(const DRW_AppId& data) override {}
    void addBlock(const DRW_Block& data) override {}
    void setBlock(const int handle) override {}
    void endBlock() override {}
    void addPoint(const DRW_Point& data) override {}
    void addLine(const DRW_Line& data) override {}
    void addRay(const DRW_Ray& data) override {}
    void addXline(const DRW_Xline& data) override {}
    void addArc(const DRW_Arc& data) override {}
    void addCircle(const DRW_Circle& data) override {}
    void addEllipse(const DRW_Ellipse& data) override {}
    void addLWPolyline(const DRW_LWPolyline& data) override {}
    void addPolyline(const DRW_Polyline& data) override {}
    void addSpline(const DRW_Spline* data) override {}
    void addKnot(const DRW_Entity& data) override {}
    void addInsert(const DRW_Insert& data) override {}
    void addTrace(const DRW_Trace& data) override {}
    void add3dFace(const DRW_3Dface& data) override {}
    void addSolid(const DRW_Solid& data) override {}
    void addMText(const DRW_MText& data) override {}
    void addText(const DRW_Text& data) override {}
    void addDimAlign(const DRW_DimAligned* data) override {}
    void addDimLinear(const DRW_DimLinear* data) override {}
    void addDimRadial(const DRW_DimRadial* data) override {}
    void addDimDiametric(const DRW_DimDiametric* data) override {}
    void addDimAngular(const DRW_DimAngular* data) override {}
    void addDimAngular3P(const DRW_DimAngular3p* data) override {}
    void addDimOrdinate(const DRW_DimOrdinate* data) override {}
    void addLeader(const DRW_Leader* data) override {}
    void addHatch(const DRW_Hatch* data) override {}
    void addViewport(const DRW_Viewport& data) override {}
    void addImage(const DRW_Image* data) override {}
    void linkImage(const DRW_ImageDef* data) override {}
    void addComment(const char* comment) override {}

    void writeHeader(DRW_Header& data) override {
       // data = header;
    }

    void writeBlocks() override {}
    void writeBlockRecords() override {}

    void writeEntities() override {

    }

    void writeLTypes() override {}
    void writeLayers() override {}
    void writeTextstyles() override {}
    void writeVports() override {}
    void writeDimstyles() override {}
    void writeAppId() override {}

    //void addPlotSettings(const DRW_PlotSettings* data) override {}

   // void writeObjects() override {}
};



int DxfWriter(int argc, char** argv)
{
    // Create DXF interface for writing
    SimpleWriter* writer = new SimpleWriter();

    // Add a circle
    DRW_Circle circle;
    circle.basePoint.x = 100.0;  // Center X
    circle.basePoint.y = 100.0;  // Center Y
    circle.basePoint.z = 0.0;    // Center Z
    circle.radious = 50.0;       // Radius
    circle.layer = "0";          // Layer name

    // Add circle to entities
    writer->addCircle(0, 0, 100);

    DRW_Header header;
    writer->writeHeader(header);

    DRW_Block block;
    writer->addBlock(block);

    //writer->writeEntities();

}