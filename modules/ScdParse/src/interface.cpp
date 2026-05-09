#include "ScdParse/interface.h"
#include "ScdParse/parse.h"

#include <vector>
#include <string>

std::string UTF_8Decode(std::string str)
{


    return str;
}



static std::string BuildMmsPath(int nIdIED, int nIdLD, int nIdLNinst, const char *fc, const char *doiName, ScdParser &parser, const char *suffix = "")
{
    if (nIdIED <= 0 || nIdLD <= 0 || nIdLNinst <= 0)
        return "";

    std::string path = parser.CSCDIEDList.at(nIdIED - 1).strName;
    path += parser.CSCDLDList.at(nIdLD - 1).strName;
    path += "/";
    path += parser.CSCDLNinstList.at(nIdLNinst - 1).prefix;
    path += parser.CSCDLNinstList.at(nIdLNinst - 1).lnClass;
    path += parser.CSCDLNinstList.at(nIdLNinst - 1).strInst;
    path += "$";
    path += fc;
    path += "$";
    path += doiName;
    path += suffix;
    return path;
}

static bool IsIgnoredDoi(const char *name)
{
    if (!name)
        return true;
    static const char *ignored[] = {"Beh", "Health", "PhyHealth", "Mod", "NamPlt", "PhyName", "PhyNam", "Proxy"};
    for (const char *s : ignored)
    {
        if (strcmp(name, s) == 0)
            return true;
    }
    return false;
}

template <typename T>
void UpdateChannelInfo(T *infoArray, int count)
{
    if (!infoArray || count <= 0)
        return;
    int lastIed = -1;
    int currentChannel = 0;
    for (int i = 0; i < count; i++)
    {
        if (infoArray[i].nIED != lastIed)
        {
            lastIed = infoArray[i].nIED;
            currentChannel = 1;
        }
        else
        {
            currentChannel++;
        }
        if constexpr (std::is_same_v<T, DZ_INFO>)
            infoArray[i].nID = currentChannel;
        else
            infoArray[i].nChannel = currentChannel;
    }
}

int getScd61850Info(ALL_61850_INFO *all61850Info, char *scdFilePath)
{
    ScdParser parser;
    int ret = parser.parseSCD("", scdFilePath);
    if (ret < 0)
        return ret;
    all61850Info->ied_num = parser.CSCDIEDList.size();
    all61850Info->ied_list = (IED_LIST *)calloc(all61850Info->ied_num, sizeof(IED_LIST));
    for (int i = 0; i < all61850Info->ied_num; i++)
    {
        CIED &pIED = parser.CSCDIEDList[i];
        all61850Info->ied_list[i].id = pIED.nId;
        strncpy(all61850Info->ied_list[i].name, pIED.strName, MAX_NAME_LEN);
        strncpy(all61850Info->ied_list[i].desc, pIED.strDesc, MAX_DESC_LEN);
        strncpy(all61850Info->ied_list[i].type, pIED.strType, MAX_NAME_LEN);
        strncpy(all61850Info->ied_list[i].configVersion, pIED.strCFGVersion, MAX_NAME_LEN);
        strncpy(all61850Info->ied_list[i].manufacturer, pIED.strManufacture, MAX_NAME_LEN);
    }
    std::vector<YX_INFO> vYX;
    std::vector<YC_INFO> vYC;
    std::vector<YK_INFO> vYK;
    std::vector<DZ_INFO> vDZ;
    std::vector<SJ_INFO> vSJ;
    for (auto &doi : parser.CSCDDOIList)
    {
        if (strcmp(parser.CSCDLDList.at(doi.nIdLD - 1).strAPName, "S1") != 0)
            continue;
        if (strlen(doi.str_dU) == 0 || IsIgnoredDoi(doi.strName) || doi.doiType == 0)
            continue;
        std::string decodedDesc = UTF_8Decode(doi.str_dU);

        // --- 遥信 (YX) & 事件 (SJ) ---
        if (doi.doiType & 1)
        { // 遥信
            YX_INFO info = {0};
            info.nIED = doi.nIdIED;
            info.nDataType = doi.nDataType;
            strncpy(info.strName, decodedDesc.c_str(), MAX_NAME_LEN);
            strncpy(info.strMmsVarName, BuildMmsPath(doi.nIdIED, doi.nIdLD, doi.nIdLNinst, "ST", doi.strName, parser, "$stVal").c_str(), MAX_DESC_LEN);
            if (doi.nDsMember > 0)
                strncpy(info.strDataSetName, parser.CSCDDataSetList.at(parser.CSCDDsMemberList.at(doi.nDsMember - 1).nDsId - 1).strName, MAX_DESC_LEN);
            vYX.push_back(info);
        }
        if (doi.doiType & 2)
        { // 事件
            SJ_INFO info = {0};
            info.nIED = doi.nIdIED;
            info.nDataType = doi.nDataType;
            strncpy(info.strName, decodedDesc.c_str(), MAX_NAME_LEN);
            strncpy(info.strMmsVarName, BuildMmsPath(doi.nIdIED, doi.nIdLD, doi.nIdLNinst, "ST", doi.strName, parser, "$general").c_str(), MAX_DESC_LEN);
            if (doi.nDsMember > 0)
                strncpy(info.strDataSetName, parser.CSCDDataSetList.at(parser.CSCDDsMemberList.at(doi.nDsMember - 1).nDsId - 1).strName, MAX_DESC_LEN);
            vSJ.push_back(info);
        }

        // --- 遥测 (YC) ---
        if (doi.doiType & (1 << 4 | 1 << 5 | 1 << 6))
        {
            YC_INFO info = {0};
            info.nIED = doi.nIdIED;
            info.nDataType = doi.nDataType;
            info.nType = 0;
            strncpy(info.strName, decodedDesc.c_str(), MAX_NAME_LEN);
            const char *suffix = (doi.doiType & (1 << 4)) ? "$mag$f" : (doi.doiType & (1 << 5)) ? "$cVal$mag$f"
                                                                                                : "$instMag$i";
            if(doi.doiType & (1 << 5)){
                info.nType = 1;
            }
            strncpy(info.strMmsVarName, BuildMmsPath(doi.nIdIED, doi.nIdLD, doi.nIdLNinst, "MX", doi.strName, parser, suffix).c_str(), MAX_DESC_LEN);
            if (doi.nDsMember > 0)
                strncpy(info.strDataSetName, parser.CSCDDataSetList.at(parser.CSCDDsMemberList.at(doi.nDsMember - 1).nDsId - 1).strName, MAX_DESC_LEN);
            vYC.push_back(info);
        }

        if (doi.doiType & (1 << 7))
        {
            for (auto dai = parser.CSCDDAIList.begin() + doi.nStart - 1; dai != parser.CSCDDAIList.end(); ++dai)
            {
                if (dai->nIdDOI != doi.nId)
                    break;

                // --- 修改点1：同时支持浮点($mag$f)和整型($instMag$i) ---
                bool isFloat = strstr(dai->daiName, "$cVal$mag$f") != nullptr;
                bool isInt = strstr(dai->daiName, "$instMag$i") != nullptr;

                if (isFloat || isInt)
                {
                    YC_INFO info = {0};
                    info.nIED = doi.nIdIED;
                    info.nType = 1;

                    // --- 修改点2：根据后缀自动识别数据类型 ---
                    if (isFloat)
                        info.nDataType = 3; // Float
                    else if (isInt)
                        info.nDataType = 1; // Int32

                    // --- 修改点3：构建 MMS 路径 ---
                    std::string basePath = BuildMmsPath(doi.nIdIED, doi.nIdLD, doi.nIdLNinst, "MX", doi.strName, parser);

                    // 如果 daiName 已经包含了 $ 符号（比如 phsA$cVal...），
                    // 我们需要检查 basePath 末尾是否有 $，避免出现 double $$
                    if (!basePath.empty() && basePath.back() != '$')
                    {
                        snprintf(info.strMmsVarName, sizeof(info.strMmsVarName), "%s$%s", basePath.c_str(), dai->daiName);
                    }
                    else
                    {
                        snprintf(info.strMmsVarName, sizeof(info.strMmsVarName), "%s%s", basePath.c_str(), dai->daiName);
                    }

                    // --- 修改点4：查找中文描述 ---
                    char descLookup[MAX_DESC_LEN] = {0};
                    strncpy(descLookup, dai->daiName, MAX_DESC_LEN - 1);

                    char *pSuffix = nullptr;
                    if (isFloat)
                        pSuffix = strstr(descLookup, "$cVal$mag$f");
                    else if (isInt)
                        pSuffix = strstr(descLookup, "$instMag$i");

                    if (pSuffix)
                    {
                        strcpy(pSuffix, "$dU");
                        for (auto it_n = parser.CSCDDAIList.begin() + doi.nStart - 1; it_n != parser.CSCDDAIList.end(); ++it_n)
                        {
                            if (it_n->nIdDOI != doi.nId)
                                break;
                            if (strcmp(it_n->daiName, descLookup) == 0)
                            {
                                // 转换并存入名称
                                std::string decodedName = UTF_8Decode(it_n->val);
                                strncpy(info.strName, decodedName.c_str(), sizeof(info.strName) - 1);
                                break;
                            }
                        }
                    }

                    // 数据集处理
                    if (dai->nDsMember > 0)
                    {
                        int dsIdx = parser.CSCDDsMemberList.at(dai->nDsMember - 1).nDsId - 1;
                        if (dsIdx >= 0 && dsIdx < parser.CSCDDataSetList.size())
                            strncpy(info.strDataSetName, parser.CSCDDataSetList.at(dsIdx).strName, sizeof(info.strDataSetName) - 1);
                    }

                    // 只有名字有效才加入结果集
                    if (info.strName[0] != '\0')
                    {
                        vYC.push_back(info);
                    }
                }
            }
        }

        // --- 遥控 (YK) ---
        if (doi.doiType & (1 << 8 | 1 << 9))
        {
            YK_INFO info = {0};
            info.nIED = doi.nIdIED;
            strncpy(info.strName, decodedDesc.c_str(), MAX_NAME_LEN);
            const char *suffix = (doi.doiType & (1 << 8)) ? "$SBOw$ctlVal" : "$Oper$ctlVal";
            strncpy(info.strMmsVarName, BuildMmsPath(doi.nIdIED, doi.nIdLD, doi.nIdLNinst, "CO", doi.strName, parser, suffix).c_str(), MAX_DESC_LEN);
            // 遥控模型转换略... (按原逻辑保留)
            vYK.push_back(info);
        }

        // --- 定值 (DZ) ---
        if ((doi.doiType & (1 << 12 | 1 << 13)) && doi.nDsMember > 0)
        {
            DZ_INFO info = {0};
            info.nIED = doi.nIdIED;
            info.nDataType = doi.nDataType;
            strncpy(info.strName, decodedDesc.c_str(), MAX_NAME_LEN);
            const char *fc = (doi.nDsMember > 0 && !strcmp(parser.CSCDDsMemberList.at(doi.nDsMember - 1).strFC, "SP")) ? "SP" : "SG";
            const char *suffix = (doi.doiType & (1 << 12)) ? "$setVal" : "$setMag$f";
            strncpy(info.strMmsVarName, BuildMmsPath(doi.nIdIED, doi.nIdLD, doi.nIdLNinst, fc, doi.strName, parser, suffix).c_str(), MAX_DESC_LEN);
            vDZ.push_back(info);
        }
    }

    auto CopyToTarget = [](auto &sourceVec, void **targetPtr, int &targetCount)
    {
        targetCount = (int)sourceVec.size();
        if (targetCount > 0)
        {
            // 获取 vector 存储的元素类型的大小
            size_t elementSize = sizeof(typename std::decay_t<decltype(sourceVec)>::value_type);
            size_t totalSize = targetCount * elementSize;

            // 分配内存
            *targetPtr = calloc(1, totalSize);
            if (*targetPtr != nullptr)
            {
                memcpy(*targetPtr, sourceVec.data(), totalSize);
            }
        }
        else
        {
            *targetPtr = nullptr;
        }
    };

    // 调用时需要将二级指针强制转换为 void**，或者在 Lambda 里处理转换
    CopyToTarget(vYX, (void **)&all61850Info->yx_info, all61850Info->yx_num);
    CopyToTarget(vYC, (void **)&all61850Info->yc_info, all61850Info->yc_num);
    CopyToTarget(vYK, (void **)&all61850Info->yk_info, all61850Info->yk_num);
    CopyToTarget(vDZ, (void **)&all61850Info->dz_info, all61850Info->dz_num);
    CopyToTarget(vSJ, (void **)&all61850Info->sj_info, all61850Info->sj_num);

    // 4. 更新通道号/ID
    UpdateChannelInfo(all61850Info->yx_info, all61850Info->yx_num);
    UpdateChannelInfo(all61850Info->yc_info, all61850Info->yc_num);
    UpdateChannelInfo(all61850Info->yk_info, all61850Info->yk_num);
    UpdateChannelInfo(all61850Info->dz_info, all61850Info->dz_num);
    UpdateChannelInfo(all61850Info->sj_info, all61850Info->sj_num);

    return 0;
}

int getScdIedList(IED_LIST *iedList, char *scdFilePath)
{
    if (iedList == nullptr || scdFilePath == nullptr)
        return -1;
    IED_LIST *ied = iedList;
    int iedCount = 0;
    ScdParser parser;
    if (parser.parseSCD(nullptr, scdFilePath) != 0)
    {
        return -1;
    }

    for (std::vector<CIED>::iterator it = parser.CSCDIEDList.begin(); it < parser.CSCDIEDList.end(); it++)
    {
        CIED *pied = &(*it);

        if (strstr(pied->strAPName, "S1") == nullptr)
        {
            continue; // 只处理包含 S1 的 AccessPoint
        }

        memset(ied, 0, sizeof(IED_LIST));

        ied->id = pied->nId;
        snprintf(ied->name, sizeof(ied->name), "%s", pied->strName);
        snprintf(ied->desc, sizeof(ied->desc), "%s", pied->strDesc);
        snprintf(ied->type, sizeof(ied->type), "%s", pied->strType);
        snprintf(ied->configVersion, sizeof(ied->configVersion), "%s", pied->strCFGVersion);
        snprintf(ied->manufacturer, sizeof(ied->manufacturer), "%s", pied->strManufacture);

        int k = 0;
        for (size_t i = 0; i < parser.CSCDNetConfigList.size(); i++)
        {
            CNetConfig &netConfig = parser.CSCDNetConfigList[i];
            if (strcmp(netConfig.chNetType, "MMS") != 0)
                continue;

            k++;
            if (netConfig.nStart <= 0 || netConfig.nStart > parser.CSCDCommConfigList.size())
                continue;

            auto it_comm = parser.CSCDCommConfigList.begin() + (netConfig.nStart - 1);
            while (it_comm != parser.CSCDCommConfigList.end())
            {
                CCommConfig &commConfig = *it_comm;
                if (commConfig.nIdSubNet != netConfig.nId)
                    break;

                if (strcmp(commConfig.strIEDName, ied->name) == 0)
                {
                    if (k == 1)
                    {
                        snprintf(ied->strIPAddr1, sizeof(ied->strIPAddr1), "%s", commConfig.strIPAdder);
                        snprintf(ied->strIPSubnet1, sizeof(ied->strIPSubnet1), "%s", commConfig.strIP_Subnet);
                    }
                    else if (k == 2)
                    {
                        snprintf(ied->strIPAddr2, sizeof(ied->strIPAddr2), "%s", commConfig.strIPAdder);
                        snprintf(ied->strIPSubnet2, sizeof(ied->strIPSubnet2), "%s", commConfig.strIP_Subnet);
                    }
                    break;
                }
                it_comm++;
            }
        }
        ied++;
        iedCount++;
    }
    return iedCount;
}
