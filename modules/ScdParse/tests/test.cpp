#include "ScdParse/parse.h"
#include "ScdParse/interface.h"
using namespace std;

int main() {
    ScdParser parser;
    string scdFilePath = "C:\\Users\\yuanjiafei\\Desktop\\scd\\PRS-713NA-DA-GCN-C.scd";
    IED_LIST iedList[10]; 
    int iedCount = getScdIedList(iedList, const_cast<char*>(scdFilePath.c_str()));
    return 0;
}