#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <iostream>


using namespace std;
int main(int argc, char *argv[])
{

    
    PNMreader reader(argv[1]);

    Crop c;
    c.SetInput(reader.GetOutput());
    c.SetRegion(500, 1190, 0, 885);

    PNMreader reader1(argv[2]);

    Shrinker s;
    s.SetInput(reader1.GetOutput());

    TBConcat tb;
    tb.SetInput(reader1.GetOutput());
    tb.SetInput2(reader1.GetOutput());


    LRConcat lr;
    lr.SetInput(tb.GetOutput());
    lr.SetInput2(tb.GetOutput());

    Blender b;
    b.SetInput(c.GetOutput());
    b.SetInput2(tb.GetOutput());
    b.SetFactor(.4);

    b.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(b.GetOutput());
    writer.Write(argv[3]);

    //CheckSum cs;
    //cs.SetInput(b.GetOutput());
    //cs.OutputCheckSum("proj3G_checksum");
}
