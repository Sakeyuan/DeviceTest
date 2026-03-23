#ifndef UTILS_H
#define UTILS_H
#include <QObject>

namespace DeviceTest { 
    Q_NAMESPACE       

    enum class NodeType {
        TestCategory = 0,    // 0 测例类别
        VendorDevice = 1,    // 1 厂家设备分类
        TestSet  = 2,        // 2 终端测试集
        TestProject  = 3,    // 3 测试项目
        TestGroup    = 4,    // 4 测试组
        TestItem     = 5     // 5 测试项
    };
    Q_ENUM_NS(NodeType)
    
    enum class TreeAction {
        ImportScd,
        AddChild,
        EditName,
        Delete,
        RunTest,
        ViewReport
    };
    Q_ENUM_NS(TreeAction)
}

#endif
