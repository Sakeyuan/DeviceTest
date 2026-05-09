#include "ScdParse/parse.h"

std::string Utf8ToGbk(const std::string& strUtf8) {
    // 1. 先将 UTF-8 转为宽字符 (Unicode)
    int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
    std::wstring wstr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, &wstr[0], len);

    // 2. 再将宽字符转为 GBK (ANSI)
    int gbkLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string strGbk(gbkLen, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &strGbk[0], gbkLen, NULL, NULL);

    // 去掉末尾可能存在的空字符
    if (!strGbk.empty() && strGbk.back() == '\0') strGbk.pop_back();

    return strGbk;
}

ScdParser::ScdParser() : m_pDoc(nullptr), m_dataTypeDone(false)
{
}

ScdParser::~ScdParser()
{
    if (m_pDoc)
        delete m_pDoc;
}

int ScdParser::parseSCD(char *iedName, char *scdFilePath)
{
    if (m_pDoc == nullptr || m_currentFile != scdFilePath)
    {
        if (m_pDoc)
            delete m_pDoc;
        m_pDoc = new pugi::xml_document();

        if (!m_pDoc->load_file(scdFilePath, pugi::parse_default, pugi::encoding_utf8))
        {
            delete m_pDoc;
            m_pDoc = nullptr;
            return -1;
        }
        m_currentFile = scdFilePath;
        m_currentIed = "";
        m_dataTypeDone = false;
    }

    pugi::xml_node pSCLNode = m_pDoc->child("SCL");
    if (iedName == nullptr)	// 直接解析IED部分和Communication部分
    {
        clearSCDList(0);
        if (!parseIED(pSCLNode, NULL))
            return -2;
        if (!parseCommunication(pSCLNode))
            return -5;
        return 0;
    }

    //解析DataTypeTemplates部分
    clearSCDList(1);
    if (!parseDataTypeTemplates(pSCLNode)) return -3;

    if (!parseIED(pSCLNode, iedName)) return -4;
    return 0;
}

void ScdParser::clearSCDList(int kind)
{
    if (kind == 0 || kind == 1)
    {
        CSCDLnTypeList.clear();
        CSCDLnMemberList.clear();
        CSCDDoTypeList.clear();
        CSCDDoMemberList.clear();
        CSCDDaTypeList.clear();
        CSCDDaMemberList.clear();
        CSCDEnumTypeList.clear();
        CSCDEnumMemberList.clear();
    }

    if (kind == 0 || kind == 2)
    {
        CSCDIEDList.clear();
        CSCDLDList.clear();
        CSCDLNinstList.clear();
        CSCDDOIList.clear();
        CSCDDAIList.clear();
        CSCDDataSetList.clear();
        CSCDDsMemberList.clear();
        CSCDRptCtrlList.clear();
        CSCDLLNOList.clear();
    }

    if (kind == 0 || kind == 3)
    {
        CSCDNetConfigList.clear();
        CSCDCommConfigList.clear();
        CSCDHeaderConfigList.clear();
        CSCDHistoryConfigList.clear();
    }
}

bool ScdParser::parseIED(pugi::xml_node &pSCLNode, char *iedName)
{
    bool parseOK = false;
    bool bAPName = true;

    for (pugi::xml_node iedNode = pSCLNode.child("IED"); iedNode; iedNode = iedNode.next_sibling("IED"))
    {
        CIED tIED;
        memset(&tIED, 0, sizeof(CIED));

        tIED.nId = (int)CSCDIEDList.size() + 1;
        tIED.nStart = (int)CSCDLDList.size() + 1;

        const char *currentIedName = iedNode.attribute("name").value();
        strncpy(tIED.strName, currentIedName, sizeof(tIED.strName) - 1);
        if (iedName == nullptr || strlen(iedName) == 0 || strcmp(tIED.strName, iedName) == 0)
        {
            snprintf(tIED.strDesc, sizeof(tIED.strDesc), "%s", iedNode.attribute("desc").value());
            snprintf(tIED.strCFGVersion, sizeof(tIED.strCFGVersion), "%s", iedNode.attribute("configVersion").value());
            snprintf(tIED.strType, sizeof(tIED.strType), "%s", iedNode.attribute("type").value());
            snprintf(tIED.strManufacture, sizeof(tIED.strManufacture), "%s", iedNode.attribute("manufacturer").value());
        }

        if (iedName != nullptr)
        {
            bAPName = false;
            parseOK = true;
        }

        int nAPNum = 0;
        char strAPNames[MAX_DESC_LEN] = {0};

        parseAccessPoint(iedNode, tIED.nId, nAPNum, strAPNames, bAPName);

        tIED.napNum = nAPNum;
        strncpy(tIED.strAPName, strAPNames, sizeof(tIED.strAPName) - 1);

        CSCDIEDList.push_back(tIED);
        if (parseOK)
            break;
    }

    return (!CSCDIEDList.empty());
}

bool ScdParser::parseAccessPoint(pugi::xml_node& iedNode, const int nIEDID, int &nAPNum, char *strAPNames, bool bAPName)
{
    // 遍历所有的 AccessPoint 节点
    for (pugi::xml_node apNode = iedNode.child("AccessPoint"); apNode; apNode = apNode.next_sibling("AccessPoint"))
    {
        // 1. 处理 AP 名称拼接 (例如: "MMS/GOOSE/")
        const char* currentAPName = apNode.attribute("name").value();
        if (currentAPName[0] != '\0')
        {
            strcat(strAPNames, currentAPName);
            strcat(strAPNames, "/");
        }

        // 2. 如果 bAPName 为 false，则深入解析 Server 及其内部的 LDevice
        if (!bAPName)
        {
            // 获取 Server 节点（SCD 规范中 AccessPoint 下通常只有一个 Server）
            pugi::xml_node serverNode = apNode.child("Server");
            if (serverNode)
            {
                // 遍历所有的 LDevice 节点
                for (pugi::xml_node ldNode = serverNode.child("LDevice"); ldNode; ldNode = ldNode.next_sibling("LDevice"))
                {
                    CLD tLD;
                    memset(&tLD, 0, sizeof(CLD));

                    tLD.nId = (int)CSCDLDList.size() + 1;
                    tLD.nStart = (int)CSCDLNinstList.size() + 1;
                    tLD.nIdIED = nIEDID;
                    std::string lnDesc = ldNode.attribute("desc").value();
                    // 拷贝 AccessPoint 名称和 LDevice 实例名(inst)及描述(desc)
                    strncpy(tLD.strAPName, currentAPName, sizeof(tLD.strAPName) - 1);
                    strncpy(tLD.strName, ldNode.attribute("inst").value(), sizeof(tLD.strName) - 1);
                    strncpy(tLD.strDesc, ldNode.attribute("desc").value(), sizeof(tLD.strDesc) - 1);

                    // 3. 解析 LN0 及其内部逻辑 (继续向下传递 xml_node)
                    // 注意：这里的 ParseLN0Part 需要你同步改为接收 pugi::xml_node&
                    parseLN0Part(ldNode, nIEDID, tLD.nId);

                    // 存入全局列表
                    CSCDLDList.push_back(tLD);
                }
            }
        }

        nAPNum++;
    }

    return true;

}

bool ScdParser::parseLN0Part(pugi::xml_node &pLDeviceNode, const int nIEDID, const int nLDID)
{
    pugi::xml_node ln0Node = pLDeviceNode.child("LN0");
    if(!ln0Node) return false;

    CLNinst tLNinst;
    memset(&tLNinst, 0, sizeof(CLNinst));
    tLNinst.nId = (int)CSCDLNinstList.size() + 1;
    tLNinst.nType = 0;
    tLNinst.nIdLD = nLDID;

    const char* lnTypeStr = ln0Node.attribute("lnType").value();
    strncpy(tLNinst.lnType, lnTypeStr, sizeof(tLNinst.lnType) - 1);
    strncpy(tLNinst.lnClass, ln0Node.attribute("lnClass").value(), sizeof(tLNinst.lnClass) - 1);
    strncpy(tLNinst.prefix, ln0Node.attribute("prefix").value(), sizeof(tLNinst.prefix) - 1);
    strncpy(tLNinst.strInst, ln0Node.attribute("inst").value(), sizeof(tLNinst.strInst) - 1);

    int nLNTypeID = -1;
    for (auto& lt : CSCDLnTypeList) {
        if (strcmp(lt.strType, lnTypeStr) == 0) {
            nLNTypeID = lt.nId;
            break;
        }
    }
    tLNinst.nLnType_id = nLNTypeID;

    CSCDLNinstList.push_back(tLNinst);
    int lnIndex = (int)CSCDLNinstList.size() - 1;

    parseLNPart(pLDeviceNode, nIEDID, nLDID);

    CLNinst& refLNinst = CSCDLNinstList.at(lnIndex);
    refLNinst.nStart = (int)CSCDDOIList.size() + 1;
    refLNinst.nStart_LN0[0] = (int)CSCDDataSetList.size() + 1;
    refLNinst.nStart_LN0[1] = (int)CSCDRptCtrlList.size() + 1;
    refLNinst.nStart_LN0[2] = (int)CSCDLLNOList.size() + 1;

    parseDOI(ln0Node, nIEDID, nLDID, refLNinst.nId, refLNinst.nLnType_id);
    parseDataSet(ln0Node, nIEDID, nLDID, refLNinst.nId);
    parseReportControl(ln0Node, nIEDID, nLDID, refLNinst.nId);

    // 4. 解析 SettingControl (定值组控制)
    int nNumofSGs = -1, nActSG = -1, nDsSetting_id = -1;
    pugi::xml_node setCtrlNode = ln0Node.child("SettingControl");
    if (setCtrlNode) {
        // 查找对应的 DataSet
        for (auto& ds : CSCDDataSetList) {
            if (ds.nIdIED == nIEDID && ds.nIdLD == nLDID && strcmp(ds.strName, "dsSetting") == 0) {
                nDsSetting_id = ds.nId;
                break;
            }
        }
        if (setCtrlNode.attribute("actSG")) nActSG = setCtrlNode.attribute("actSG").as_int();
        if (setCtrlNode.attribute("numOfSGs")) nNumofSGs = setCtrlNode.attribute("numOfSGs").as_int();
    }

    // 5. 解析 GSEControl (GOOSE) 和 SampledValueControl (SMV)
    pugi::xml_node gseNode = ln0Node.child("GSEControl");
    pugi::xml_node smvNode = ln0Node.child("SampledValueControl");

    // 逻辑：如果两者都没有，存一个空的控制块信息
    if (!gseNode && !smvNode) {
        CLLNO tLLN0;
        memset(&tLLN0, 0, sizeof(CLLNO));
        tLLN0.nId = (int)CSCDLLNOList.size() + 1;
        tLLN0.nIdIED = nIEDID; tLLN0.nIdLD = nLDID; tLLN0.nIdLNinst = refLNinst.nId;
        tLLN0.nLnType_id = nLNTypeID; tLLN0.nType = 0; tLLN0.nDsID = -1;
        tLLN0.nNumofSGs = nNumofSGs; tLLN0.nActSG = nActSG; tLLN0.nDsSetting_id = nDsSetting_id;
        CSCDLLNOList.push_back(tLLN0);
    }

    // 遍历 GSEControl
    for (; gseNode; gseNode = gseNode.next_sibling("GSEControl")) {
        CLLNO tLLN0;
        memset(&tLLN0, 0, sizeof(CLLNO));
        tLLN0.nId = (int)CSCDLLNOList.size() + 1;
        tLLN0.nIdIED = nIEDID; tLLN0.nIdLD = nLDID; tLLN0.nIdLNinst = refLNinst.nId;
        tLLN0.nLnType_id = nLNTypeID; tLLN0.nType = 1; tLLN0.isGoose = true;
        tLLN0.nNumofSGs = nNumofSGs; tLLN0.nActSG = nActSG; tLLN0.nDsSetting_id = nDsSetting_id;

        // 查找关联数据集
        const char* dsName = gseNode.attribute("datSet").value();
        for (auto& ds : CSCDDataSetList) {
            if (nIEDID == ds.nIdIED && nLDID == ds.nIdLD && strcmp(ds.strName, dsName) == 0) {
                tLLN0.nDsID = ds.nId; break;
            }
        }
        strncpy(tLLN0.strName, gseNode.attribute("name").value(), sizeof(tLLN0.strName) - 1);
        strncpy(tLLN0.strDesc, gseNode.attribute("desc").value(), sizeof(tLLN0.strDesc) - 1);
        strncpy(tLLN0.strAppID, gseNode.attribute("appID").value(), sizeof(tLLN0.strAppID) - 1);
        tLLN0.nConfRev = gseNode.attribute("confRev").as_int();
        if (strcmp(gseNode.attribute("type").value(), "GSSE") == 0) tLLN0.isGoose = false;

        CSCDLLNOList.push_back(tLLN0);
    }

    // 遍历 SampledValueControl
    for (; smvNode; smvNode = smvNode.next_sibling("SampledValueControl")) {
        CLLNO tLLN0;
        memset(&tLLN0, 0, sizeof(CLLNO));
        tLLN0.nId = (int)CSCDLLNOList.size() + 1;
        tLLN0.nIdIED = nIEDID; tLLN0.nIdLD = nLDID; tLLN0.nIdLNinst = refLNinst.nId;
        tLLN0.nLnType_id = nLNTypeID; tLLN0.nType = 2; tLLN0.isMulticast = true;
        tLLN0.nNumofSGs = nNumofSGs; tLLN0.nActSG = nActSG; tLLN0.nDsSetting_id = nDsSetting_id;

        const char* dsName = smvNode.attribute("datSet").value();
        for (auto& ds : CSCDDataSetList) {
            if (nIEDID == ds.nIdIED && nLDID == ds.nIdLD && strcmp(ds.strName, dsName) == 0) {
                tLLN0.nDsID = ds.nId; break;
            }
        }
        strncpy(tLLN0.strName, smvNode.attribute("name").value(), sizeof(tLLN0.strName) - 1);
        strncpy(tLLN0.strDesc, smvNode.attribute("desc").value(), sizeof(tLLN0.strDesc) - 1);
        strncpy(tLLN0.strAppID, smvNode.attribute("smvID").value(), sizeof(tLLN0.strAppID) - 1);
        tLLN0.nConfRev = smvNode.attribute("confRev").as_int();
        tLLN0.nSmpRate = smvNode.attribute("smpRate").as_int();
        tLLN0.nNofASDU = smvNode.attribute("nofASDU").as_int();
        if (strcmp(smvNode.attribute("multicast").value(), "false") == 0) tLLN0.isMulticast = false;

        // SmvOpts 子节点
        pugi::xml_node opts = smvNode.child("SmvOpts");
        if (opts) {
            if (opts.attribute("sampleRate").as_bool())      tLLN0.bSmvOpts |= 0x10;
            if (opts.attribute("refreshTime").as_bool())     tLLN0.bSmvOpts |= 0x08;
            if (opts.attribute("sampleSynchronized").as_bool()) tLLN0.bSmvOpts |= 0x04;
            if (opts.attribute("security").as_bool())        tLLN0.bSmvOpts |= 0x02;
            if (opts.attribute("dataRef").as_bool())         tLLN0.bSmvOpts |= 0x01;
        }

        CSCDLLNOList.push_back(tLLN0);
    }
    return true;
}

bool ScdParser::parseLNPart(pugi::xml_node &pLDeviceNode, const int nIEDID, const int nLDID)
{
    for (pugi::xml_node lnNode = pLDeviceNode.child("LN"); lnNode; lnNode = lnNode.next_sibling("LN"))
    {
        CLNinst tLNinst;
        memset(&tLNinst, 0, sizeof(CLNinst));
        tLNinst.nId = (int)CSCDLNinstList.size() + 1;
        tLNinst.nStart = (int)CSCDDOIList.size() + 1;
        tLNinst.nType = 1; // 1 代表普通 LN
        tLNinst.nIdLD = nLDID;
        tLNinst.nLnType_id = -1;

        // 获取 lnType 属性并查找对应的 ID
        const char* lnTypeAttr = lnNode.attribute("lnType").value();
        if (lnTypeAttr[0] != '\0')
        {
            strncpy(tLNinst.lnType, lnTypeAttr, sizeof(tLNinst.lnType) - 1);

            // 在 LnTypeList 容器中匹配对应的类型 ID
            for (const auto& lt : CSCDLnTypeList)
            {
                if (strcmp(lt.strType, lnTypeAttr) == 0)
                {
                    tLNinst.nLnType_id = lt.nId;
                    break;
                }
            }
        }

        // 拷贝其它属性 (PugiXML 的 value() 保证了即使属性缺失也返回 "" 而非 NULL)
        strncpy(tLNinst.lnClass, lnNode.attribute("lnClass").value(), sizeof(tLNinst.lnClass) - 1);
        strncpy(tLNinst.prefix, lnNode.attribute("prefix").value(), sizeof(tLNinst.prefix) - 1);
        strncpy(tLNinst.strInst, lnNode.attribute("inst").value(), sizeof(tLNinst.strInst) - 1);
        strncpy(tLNinst.strDesc, lnNode.attribute("desc").value(), sizeof(tLNinst.strDesc) - 1);

        // 存入全局列表
        CSCDLNinstList.push_back(tLNinst);

        // 解析 DOI 部分 (数据对象实例)
        // 传入当前生成的 tLNinst.nId 作为关联外键
        parseDOI(lnNode, nIEDID, nLDID, tLNinst.nId, tLNinst.nLnType_id);
    }
    return true;
}

bool ScdParser::parseDOI(pugi::xml_node &lnNode, const int nIEDID, const int nLDID, const int nLNinstID, const int nLnTypeID)
{
    for (pugi::xml_node doiNode = lnNode.child("DOI"); doiNode; doiNode = doiNode.next_sibling("DOI"))
    {
        const char* doiName = doiNode.attribute("name").value();
        // 1. 获取 nDoTypeID
        int nDoTypeID = -1;
        for (const auto& lm : CSCDLnMemberList) {
            if (nLnTypeID == lm.nLnType_id && strcmp(lm.strDoName, doiName) == 0) {
                nDoTypeID = lm.nDoType_id;
                break;
            }
        }

        CDOI tDOI;
        memset(&tDOI, 0, sizeof(CDOI));
        tDOI.nId = (int)CSCDDOIList.size() + 1;
        tDOI.nStart = (int)CSCDDAIList.size() + 1;
        tDOI.nIdIED = nIEDID;
        tDOI.nIdLD = nLDID;
        tDOI.nIdLNinst = nLNinstID;
        tDOI.nIdDotype = nDoTypeID;
        tDOI.nDsMember = -1;
        tDOI.nDataType = -1;

        strncpy(tDOI.strName, doiName, sizeof(tDOI.strName) - 1);
        strncpy(tDOI.strDesc, doiNode.attribute("desc").value(), sizeof(tDOI.strDesc) - 1);

        // 2. 处理 DAI / SDI
        // 第一层 DAI
        for (pugi::xml_node daiNode = doiNode.child("DAI"); daiNode; daiNode = daiNode.next_sibling("DAI")) {
            processDAI(daiNode, tDOI, "");
        }
        // 处理 SDI 嵌套
        for (pugi::xml_node sdiNode = doiNode.child("SDI"); sdiNode; sdiNode = sdiNode.next_sibling("SDI")) {
            const char* s1 = sdiNode.attribute("name").value();
            // SDI -> DAI
            for (pugi::xml_node d2 = sdiNode.child("DAI"); d2; d2 = d2.next_sibling("DAI")) {
                processDAI(d2, tDOI, s1);
            }
            // SDI -> SDI -> DAI
            for (pugi::xml_node s2node = sdiNode.child("SDI"); s2node; s2node = s2node.next_sibling("SDI")) {
                const char* s2 = s2node.attribute("name").value();
                for (pugi::xml_node d3 = s2node.child("DAI"); d3; d3 = d3.next_sibling("DAI")) {
                    char path[128];
                    snprintf(path, sizeof(path), "%s$%s", s1, s2);
                    processDAI(d3, tDOI, path);
                }
                // SDI -> SDI -> SDI -> DAI
                for (pugi::xml_node s3node = s2node.child("SDI"); s3node; s3node = s3node.next_sibling("SDI")) {
                    const char* s3 = s3node.attribute("name").value();
                    for (pugi::xml_node d4 = s3node.child("DAI"); d4; d4 = d4.next_sibling("DAI")) {
                        char path[128];
                        snprintf(path, sizeof(path), "%s$%s$%s", s1, s2, s3);
                        processDAI(d4, tDOI, path);
                    }
                }
            }
        }

        // 3. 补充逻辑
        supplementDAIByDoType(nIEDID, nLDID, nLNinstID, &tDOI);

        if (tDOI.str_dU[0] == '\0' && tDOI.strDesc[0] != '\0') {
            strncpy(tDOI.str_dU, tDOI.strDesc, sizeof(tDOI.str_dU) - 1);
        }

        CSCDDOIList.push_back(tDOI);
    }
    return true;
}
void ScdParser::supplementDAIByDoType(const int nIEDID, const int nLDID, const int nLNinstID, CDOI *pDOI)
{
    if (!pDOI || pDOI->nIdDotype <= 0) return;

    // 1. 获取当前 DOI 所属的 DOType 模板
    CDoType* pDoType = nullptr;
    // 假设 CSCDDoTypeList 已经按 ID 排序或可以直接查找
    for (auto &dt : CSCDDoTypeList) {
        if (dt.nId == pDOI->nIdDotype) {
            pDoType = &dt;
            break;
        }
    }
    if (!pDoType) return;

    // 2. 遍历该 DOType 下的所有成员
    for (auto &member : CSCDDoMemberList) {
        if (member.nDotype_id != pDoType->nId) continue;

        // --- 情况 A: 成员是 DA (属性) ---
        if (member.nKind == 0)
        {
            // 匹配 stVal
            if (strcmp(member.strDaName, "stVal") == 0) {
                pDOI->nDataType = (strcmp(member.strBType, "Dbpos") == 0) ? ENUM_TYPE_CODEENUM : ENUM_TYPE_BOOLEAN;
                if ((pDOI->doiType & 1) == 0) {
                    addMissingDAI(pDOI->nId, "stVal");
                    pDOI->doiType |= 1;
                }
            }
            else if (strcmp(member.strDaName,"general") == 0)
            {
                pDOI->nDataType = ENUM_TYPE_BOOLEAN;
                if ((pDOI->doiType & (1 << 1)) == 0) {
                    addMissingDAI(pDOI->nId, "general");
                    pDOI->doiType |= 2;
                }
            }

            // 匹配 mag
            else if (strcmp(member.strDaName, "mag") == 0) {
                pDOI->nDataType = ENUM_TYPE_FLOAT;
                if ((pDOI->doiType & (1 << 4)) == 0) {
                    addMissingDAI(pDOI->nId, "mag$f");
                    pDOI->doiType |= (1 << 4);
                }
            }
            else if(strcmp(member.strDaName, "instMag") == 0 ) {
                pDOI->nDataType = ENUM_TYPE_INT;
                if((pDOI->doiType & (1 << 6)) == 0) {
                    addMissingDAI(pDOI->nId, "instMag$i");
                    pDOI->doiType |= (1 << 6);
                }
            }
            // 匹配 cVal
            else if (strcmp(member.strDaName, "cVal") == 0) {
                pDOI->nDataType = ENUM_TYPE_FLOAT;
                if ((pDOI->doiType & (1 << 5)) == 0) {
                    addMissingDAI(pDOI->nId, "cVal$mag$f");
                    pDOI->doiType |= (1 << 5);
                }
            }
            // 匹配 setVal (定值)
            else if (strcmp(member.strDaName, "setVal") == 0) {
                if (strcmp(member.strBType, "Unicode255") == 0) pDOI->nDataType = ENUM_TYPE_VISIBLESTRING;
                else if (strcmp(member.strBType, "BOOLEAN") == 0) pDOI->nDataType = ENUM_TYPE_BOOLEAN;
                else if (strcmp(member.strBType, "INT32") == 0) pDOI->nDataType = ENUM_TYPE_INT;
                else if (strcmp(member.strBType, "FLOAT32") == 0) pDOI->nDataType = ENUM_TYPE_FLOAT;

                if ((pDOI->doiType & (1 << 12)) == 0) {
                    addMissingDAI(pDOI->nId, "setVal");
                    pDOI->doiType |= (1 << 12);
                }
            }
            // 匹配控制点
            else if (strcmp(member.strDaName, "SBOw") == 0 && (pDOI->doiType & (1 << 8)) == 0) {
                addMissingDAI(pDOI->nId, "SBOw$ctlVal");
                pDOI->doiType |= (1 << 8);
            }
            else if (strcmp(member.strDaName, "Oper") == 0 && (pDOI->doiType & (1 << 9)) == 0) {
                addMissingDAI(pDOI->nId, "Oper$ctlVal");
                pDOI->doiType |= (1 << 9);
            }

        }
        // --- 情况 B: 成员是 SDO
        else if (member.nKind == 1)
        {
            // 如果还没标记过 Bit 7 (复合值标记)，则检查 SDO 的类型
            if ((pDOI->doiType & (1 << 7)) == 0 && member.nType_id > 0)
            {
                // 遍历 CSCDDoMemberList 寻找该 SDO 类型下的成员
                for (auto &subMember : CSCDDoMemberList) {
                    if (subMember.nDotype_id != member.nType_id) continue;

                    // 如果子成员里有 cVal (通常用于复合测量值如 WYE 结构)
                    if (strcmp(subMember.strDaName, "cVal") == 0) {
                        char compositeName[128];
                        // 拼接名称，如 "phsA" + "$cVal$mag$f"
                        snprintf(compositeName, sizeof(compositeName), "%s$cVal$mag$f", member.strDaName);

                        addMissingDAI(pDOI->nId, compositeName);
                        pDOI->doiType |= (1 << 7); // 标记 Bit 7
                        break; // 找到一个复合标志即可，跳出当前 SDO 的子遍历
                    }
                }
            }
        }
    }
}
void ScdParser::addMissingDAI(int nDoiId, const char* name)
{
    CDAI tDAI;
    memset(&tDAI, 0, sizeof(CDAI));
    tDAI.nId = (int)CSCDDAIList.size() + 1;
    tDAI.nIdDOI = nDoiId;
    strncpy(tDAI.daiName, name, sizeof(tDAI.daiName) - 1);
    CSCDDAIList.push_back(tDAI);
}

void ScdParser::processDAI(pugi::xml_node &daiNode, CDOI &doi, std::string prefix)
{
    CDAI tDAI;
    memset(&tDAI, 0, sizeof(CDAI));
    tDAI.nId = (int)CSCDDAIList.size() + 1;
    tDAI.nIdDOI = doi.nId;

    const char* name = daiNode.attribute("name").value();
    if (prefix.empty())
        strncpy(tDAI.daiName, name, sizeof(tDAI.daiName) - 1);
    else
        snprintf(tDAI.daiName, sizeof(tDAI.daiName), "%s$%s", prefix.c_str(), name);

    strncpy(tDAI.strSaddr, daiNode.attribute("sAddr").value(), sizeof(tDAI.strSaddr) - 1);
    strncpy(tDAI.valKind, daiNode.attribute("valKind").value(), sizeof(tDAI.valKind) - 1);
    strncpy(tDAI.val, daiNode.child_value("Val"), sizeof(tDAI.val) - 1);

    // 更新 DOI 的特征位

    if (strcmp(tDAI.daiName, "dU") == 0) strncpy(doi.str_dU, tDAI.val, sizeof(doi.str_dU) - 1);
    else if (strcmp(tDAI.daiName, "ctlModel") == 0) strncpy(doi.str_ctlModel, tDAI.val, sizeof(doi.str_ctlModel) - 1);
    else if (strcmp(tDAI.daiName, "stVal") == 0) doi.doiType |= 1;
    else if (strcmp(tDAI.daiName, "general") == 0) doi.doiType |= 2;
    else if (strcmp(tDAI.daiName, "mag$f") == 0) doi.doiType |= (1 << 4);
    else if (strcmp(tDAI.daiName, "cVal$mag$f") == 0) doi.doiType |= (1 << 5);
    else if (strcmp(tDAI.daiName, "instMag$i") == 0) doi.doiType |= (1 << 6);
    else if (strstr(tDAI.daiName, "$cVal$mag$f")) doi.doiType |= (1 << 7);
    else if (strcmp(tDAI.daiName, "SBOw$ctlVal") == 0) doi.doiType |= (1 << 8);
    else if (strcmp(tDAI.daiName, "Oper$ctlVal") == 0) doi.doiType |= (1 << 9);
    else if (strcmp(tDAI.daiName, "Cancel$ctlVal") == 0) doi.doiType |= (1 << 10);
    else if (strcmp(tDAI.daiName, "setVal") == 0) doi.doiType |= (1 << 12);
    else if (strcmp(tDAI.daiName, "setMag$f") == 0) doi.doiType |= (1 << 13);

    CSCDDAIList.push_back(tDAI);
}

bool ScdParser::parseDataSet(pugi::xml_node &ln0Node, const int nIEDID, const int nLDID, const int nLNinstID)
{
    for (pugi::xml_node dsNode = ln0Node.child("DataSet"); dsNode; dsNode = dsNode.next_sibling("DataSet"))
    {
        CDataSet tDataSet;
        memset(&tDataSet, 0, sizeof(CDataSet));

        tDataSet.nId = (int)CSCDDataSetList.size() + 1;
        tDataSet.nStart = (int)CSCDDsMemberList.size() + 1;
        tDataSet.nIdIED = nIEDID;
        tDataSet.nIdLD = nLDID;
        tDataSet.nIdLNinst = nLNinstID;

        const char* dsNameAttr = dsNode.attribute("name").value();
        strncpy(tDataSet.strName, dsNameAttr, sizeof(tDataSet.strName) - 1);
        strncpy(tDataSet.strDesc, dsNode.attribute("desc").value(), sizeof(tDataSet.strDesc) - 1);

        // 判断是否为 GOOSE 数据集
        std::string upperName = dsNameAttr;
        for (auto &c : upperName) c = (char)toupper(c);
        int nIsGoose = (upperName.find("GOOSE") != std::string::npos) ? 1 : 0;

        int nSeqMember = 0;
        for (pugi::xml_node fcdaNode = dsNode.child("FCDA"); fcdaNode; fcdaNode = fcdaNode.next_sibling("FCDA"))
        {
            CDsMember tDsMember;
            memset(&tDsMember, 0, sizeof(CDsMember));

            tDsMember.nId = (int)CSCDDsMemberList.size() + 1;
            tDsMember.nIdIED = nIEDID;
            tDsMember.nDOI = -1;
            tDsMember.nDAI = -1;
            tDsMember.nDsId = tDataSet.nId;
            tDsMember.nSeqMember = nSeqMember;
            tDsMember.nIsGoose = nIsGoose;
            tDsMember.nAppType = -1;
            tDsMember.nBTypeValue = -1;

            // 属性拷贝
            strncpy(tDsMember.strDaName, fcdaNode.attribute("daName").value(), sizeof(tDsMember.strDaName) - 1);
            strncpy(tDsMember.strDoName, fcdaNode.attribute("doName").value(), sizeof(tDsMember.strDoName) - 1);
            strncpy(tDsMember.strFC, fcdaNode.attribute("fc").value(), sizeof(tDsMember.strFC) - 1);
            strncpy(tDsMember.strPrefix, fcdaNode.attribute("prefix").value(), sizeof(tDsMember.strPrefix) - 1);
            strncpy(tDsMember.strLnClass, fcdaNode.attribute("lnClass").value(), sizeof(tDsMember.strLnClass) - 1);
            strncpy(tDsMember.strLnInst, fcdaNode.attribute("lnInst").value(), sizeof(tDsMember.strLnInst) - 1);
            strncpy(tDsMember.strLdInst, fcdaNode.attribute("ldInst").value(), sizeof(tDsMember.strLdInst) - 1);

            // 1. 匹配 DOI (关联 FCDA 到具体的 DOI 实例)
            for (auto& doi : CSCDDOIList)
            {
                if (doi.nIdLD == nLDID &&
                    strcmp(tDsMember.strDoName, doi.strName) == 0 &&
                    strcmp(tDsMember.strPrefix, CSCDLNinstList.at(doi.nIdLNinst - 1).prefix) == 0 &&
                    strcmp(tDsMember.strLnClass, CSCDLNinstList.at(doi.nIdLNinst - 1).lnClass) == 0 &&
                    strcmp(tDsMember.strLnInst, CSCDLNinstList.at(doi.nIdLNinst - 1).strInst) == 0)
                {
                    doi.nDsMember = tDsMember.nId;
                    tDsMember.nDOI = doi.nId;
                    break;
                }
            }

            // 2. 匹配 DAI (关联 FCDA 到具体的 DAI 实例)
            // 注意：只有当 FCDA 指定了 daName 时才需要匹配到 DAI 级别
            if (tDsMember.strDaName[0] != '\0')
            {
                std::string targetPattern = std::string(tDsMember.strDoName) + "$" + tDsMember.strDaName;
                for (auto &c : targetPattern) if (c == '.') c = '$'; // 规范化 . 为 $

                for (auto& dai : CSCDDAIList)
                {
                    CDOI& parentDOI = CSCDDOIList.at(dai.nIdDOI - 1);
                    if (parentDOI.nIdLD == nLDID &&
                        strcmp(tDsMember.strPrefix, CSCDLNinstList.at(parentDOI.nIdLNinst - 1).prefix) == 0 &&
                        strcmp(tDsMember.strLnClass, CSCDLNinstList.at(parentDOI.nIdLNinst - 1).lnClass) == 0 &&
                        strcmp(tDsMember.strLnInst, CSCDLNinstList.at(parentDOI.nIdLNinst - 1).strInst) == 0)
                    {
                        std::string currentFullPath = std::string(parentDOI.strName) + "$" + dai.daiName;
                        if (currentFullPath.find(targetPattern) != std::string::npos)
                        {
                            dai.nDsMember = tDsMember.nId;
                            tDsMember.nDAI = dai.nId;
                            // 这里不 break，因为某些复杂路径可能匹配多项，或者保留原有逻辑的遍历行为
                        }
                    }
                }
            }

            CSCDDsMemberList.push_back(tDsMember);
            nSeqMember++;
        }

        CSCDDataSetList.push_back(tDataSet);
    }
    return true;
}

bool ScdParser::parseReportControl(pugi::xml_node &ln0Node, const int nIEDID, const int nLDID, const int nLNinstID)
{
    // 辅助函数：将 XML 属性的 "true"/"false" 转为 bool
    auto getBoolAttr = [](pugi::xml_node& node, const char* attrName) -> bool {
        return strcmp(node.attribute(attrName).value(), "true") == 0;
    };

    for (pugi::xml_node rptNode = ln0Node.child("ReportControl"); rptNode; rptNode = rptNode.next_sibling("ReportControl"))
    {
        CRptCtrl tRptCtrl;
        memset(&tRptCtrl, 0, sizeof(CRptCtrl));

        tRptCtrl.nId = (int)CSCDRptCtrlList.size() + 1;
        tRptCtrl.nIdIED = nIEDID;
        tRptCtrl.nIdLD = nLDID;
        tRptCtrl.nIdLNinst = nLNinstID;
        tRptCtrl.nIdDS = -1;

        // 基础属性解析
        strncpy(tRptCtrl.strName, rptNode.attribute("name").value(), sizeof(tRptCtrl.strName) - 1);
        strncpy(tRptCtrl.strRptID, rptNode.attribute("rptID").value(), sizeof(tRptCtrl.strRptID) - 1);
        strncpy(tRptCtrl.strDesc, rptNode.attribute("desc").value(), sizeof(tRptCtrl.strDesc) - 1);

        tRptCtrl.nConfRev = rptNode.attribute("confRev").as_int();
        tRptCtrl.nBufTime = rptNode.attribute("bufTime").as_int();
        tRptCtrl.nIntgPd  = rptNode.attribute("intgPd").as_int();
        tRptCtrl.isBuffered = getBoolAttr(rptNode, "buffered");

        // 关联数据集 (DataSet)
        const char* dsName = rptNode.attribute("datSet").value();
        if (dsName[0] != '\0')
        {
            for (const auto& ds : CSCDDataSetList)
            {
                if (ds.nIdIED == nIEDID && ds.nIdLD == nLDID && strcmp(ds.strName, dsName) == 0)
                {
                    tRptCtrl.nIdDS = ds.nId;
                    break;
                }
            }
        }

        // 解析触发选项 TrgOps (位掩码处理)
        pugi::xml_node trgNode = rptNode.child("TrgOps");
        if (trgNode)
        {
            if (getBoolAttr(trgNode, "dchg"))   tRptCtrl.bTrgOps |= 0x08;
            if (getBoolAttr(trgNode, "qchg"))   tRptCtrl.bTrgOps |= 0x04;
            if (getBoolAttr(trgNode, "dupd"))   tRptCtrl.bTrgOps |= 0x02;
            if (getBoolAttr(trgNode, "period")) tRptCtrl.bTrgOps |= 0x01;
        }

        // 解析可选字段 OptFields (位掩码处理)
        pugi::xml_node optNode = rptNode.child("OptFields");
        if (optNode)
        {
            if (getBoolAttr(optNode, "seqNum"))     tRptCtrl.bOptFields |= 0x80;
            if (getBoolAttr(optNode, "timeStamp"))  tRptCtrl.bOptFields |= 0x40;
            if (getBoolAttr(optNode, "reasonCode")) tRptCtrl.bOptFields |= 0x20;
            if (getBoolAttr(optNode, "dataSet"))    tRptCtrl.bOptFields |= 0x10;
            if (getBoolAttr(optNode, "dataRef"))    tRptCtrl.bOptFields |= 0x08;
            if (getBoolAttr(optNode, "bufOvfl"))    tRptCtrl.bOptFields |= 0x04;
            if (getBoolAttr(optNode, "entryID"))    tRptCtrl.bOptFields |= 0x02;
            if (getBoolAttr(optNode, "configRef"))  tRptCtrl.bOptFields |= 0x01;
        }

        // 解析报告使能 RptEnabled
        pugi::xml_node enNode = rptNode.child("RptEnabled");
        if (enNode)
        {
            tRptCtrl.nMax = enNode.attribute("max").as_int();
        }

        CSCDRptCtrlList.push_back(tRptCtrl);
    }
    return true;
}

bool ScdParser::parseCommunication(pugi::xml_node &pSCLNode)
{
    pugi::xml_node communicationNode = pSCLNode.child("Communication");
    if (!communicationNode) return false;

    // 遍历 SubNetwork
    for (pugi::xml_node subNetworkNode : communicationNode.children("SubNetwork"))
    {
        CNetConfig *pNetConfig = (CNetConfig *)calloc(1, sizeof(CNetConfig));
        pNetConfig->nId = CSCDNetConfigList.size() + 1;
        pNetConfig->nStart = CSCDCommConfigList.size() + 1;

        // 获取属性
        strncpy(pNetConfig->chNetName, subNetworkNode.attribute("name").value(), MAX_NAME_LEN);
        strncpy(pNetConfig->chNetProtocol, subNetworkNode.attribute("type").value(), MAX_NAME_LEN);

        // 获取 BitRate
        pugi::xml_node bitRateNode = subNetworkNode.child("BitRate");
        if (bitRateNode) {
            pNetConfig->nBitRate = bitRateNode.text().as_int();
        }

        // 协议逻辑处理
        if (pNetConfig->chNetProtocol[0] == '\0') {
            strcpy(pNetConfig->chNetProtocol, pNetConfig->chNetName);
        }

        if (strstr(pNetConfig->chNetProtocol, "MMS")) strcpy(pNetConfig->chNetType, "MMS");
        else if (strstr(pNetConfig->chNetProtocol, "GOOSE")) strcpy(pNetConfig->chNetType, "GOOSE");
        else if (strstr(pNetConfig->chNetProtocol, "SMV")) strcpy(pNetConfig->chNetType, "SMV");

        // 遍历 ConnectedAP
        for (pugi::xml_node connectedAPNode : subNetworkNode.children("ConnectedAP"))
        {
            const char* apName = connectedAPNode.attribute("apName").value();
            const char* iedName = connectedAPNode.attribute("iedName").value();

            // 如果没识别出类型，根据 apName 首字母猜测 (S=MMS, G=GOOSE, M=SMV)
            if (pNetConfig->chNetType[0] == '\0' && apName[0] != '\0') {
                if (apName[0] == 'S') strcpy(pNetConfig->chNetType, "MMS");
                else if (apName[0] == 'G') strcpy(pNetConfig->chNetType, "GOOSE");
                else if (apName[0] == 'M') strcpy(pNetConfig->chNetType, "SMV");
            }

            // 处理不同类型的配置 (MMS, GOOSE, SMV)
            // 注意：这里逻辑上 MMS 走 Address，GOOSE/SMV 走 GSE/SMV 节点
            if (strcmp(pNetConfig->chNetType, "MMS") == 0)
            {
                parseMmsAddress(connectedAPNode, pNetConfig->nId, iedName, apName);
            }
            else if (strcmp(pNetConfig->chNetType, "GOOSE") == 0)
            {
                for (pugi::xml_node gseNode : connectedAPNode.children("GSE")) {
                    parseGseOrSmvConfig(gseNode, connectedAPNode, pNetConfig->nId, "GOOSE");
                }
            }
            else if (strcmp(pNetConfig->chNetType, "SMV") == 0)
            {
                for (pugi::xml_node smvNode : connectedAPNode.children("SMV")) {
                    parseGseOrSmvConfig(smvNode, connectedAPNode, pNetConfig->nId, "SMV");
                }
            }
        }

        CSCDNetConfigList.push_back(*pNetConfig);
        free(pNetConfig);
    }

    return true;
}

void ScdParser::parseMmsAddress(pugi::xml_node apNode, int subNetId, const char* iedName, const char* apName)
{
    CCommConfig config;
    memset(&config, 0, sizeof(CCommConfig));
    config.nId = CSCDCommConfigList.size() + 1;
    config.nIdSubNet = subNetId;
    strcpy(config.strIEDName, iedName);
    strcpy(config.strApName, apName);
    strcpy(config.strConnectedAP, apNode.attribute("desc").value());

    for (pugi::xml_node pNode : apNode.child("Address").children("P")) {
        const char* type = pNode.attribute("type").value();
        const char* val = pNode.text().get();
        if (!val) continue;

        if (strcmp(type, "IP") == 0) strcpy(config.strIPAdder, val);
        else if (strcmp(type, "IP-SUBNET") == 0) strcpy(config.strIP_Subnet, val);
        else if (strcmp(type, "OSI-AP-Title") == 0) strcpy(config.strOSI_AP_Title, val);
        else if (strcmp(type, "OSI-AE-Qualifier") == 0) strcpy(config.strOSI_AE_Qualifier, val);
        else if (strcmp(type, "OSI-PSEL") == 0) strcpy(config.strOSI_PSEL, val);
        else if (strcmp(type, "OSI-SSEL") == 0) strcpy(config.strOSI_SSEL, val);
        else if (strcmp(type, "OSI-TSEL") == 0) strcpy(config.strOSI_TSEL, val);
    }
    CSCDCommConfigList.push_back(config);
}

void ScdParser::parseGseOrSmvConfig(pugi::xml_node commNode, pugi::xml_node apNode, int subNetId, const char* type)
{
    CCommConfig config;
    memset(&config, 0, sizeof(CCommConfig));
    config.nId = CSCDCommConfigList.size() + 1;
    config.nIdSubNet = subNetId;

    strcpy(config.strIEDName, apNode.attribute("iedName").value());
    strcpy(config.strApName, apNode.attribute("apName").value());
    strcpy(config.strConnectedAP, apNode.attribute("desc").value());

    strcpy(config.strGseOrSmvCbName, commNode.attribute("cbName").value());
    strcpy(config.strGseOrSmvDesc, commNode.attribute("desc").value());
    strcpy(config.strLdInst, commNode.attribute("ldInst").value());

    for (pugi::xml_node pNode : commNode.child("Address").children("P")) {
        const char* pType = pNode.attribute("type").value();
        const char* pVal = pNode.text().get();
        if (!pVal) continue;

        if (strcmp(pType, "MAC-Address") == 0) strcpy(config.strMACAddr, pVal);
        else if (strcmp(pType, "APPID") == 0) strcpy(config.strAppID, pVal);
        else if (strcmp(pType, "VLAN-ID") == 0) config.nVlan_ID = atoi(pVal);
        else if (strcmp(pType, "VLAN-PRIORITY") == 0) config.nVLAN_PRIORITY = atoi(pVal);
    }

    config.nMinTime = commNode.child("MinTime").text().as_int();
    config.nMaxTime = commNode.child("MaxTime").text().as_int();

    CSCDCommConfigList.push_back(config);
}

bool ScdParser::parseDataTypeTemplates(pugi::xml_node &pSCLNode)
{
    pugi::xml_node pDataTypeTemplatesElement = pSCLNode.child("DataTypeTemplates");

    if (!pDataTypeTemplatesElement) return false;

    //解析EnumType部分
    parseEnumType(pDataTypeTemplatesElement);

    //解析DAType部分
    parseDAType(pDataTypeTemplatesElement);

    //解析DOType部分
    parseDOType(pDataTypeTemplatesElement);

    //解析LNodeType部分
    parseLNodeType(pDataTypeTemplatesElement);

    return true;
}

bool ScdParser::parseEnumType(pugi::xml_node &pDataTypeTemplatesElement)
{
    pugi::xml_node pEnumTypeElement = pDataTypeTemplatesElement.child("EnumType");
    if (!pEnumTypeElement) return true;
    for (; pEnumTypeElement; pEnumTypeElement = pEnumTypeElement.next_sibling("EnumType"))
    {
        CEnumType *pEnumType = (CEnumType *)calloc(1, sizeof(CEnumType));
        if (!pEnumType) return false;

        pEnumType->nId = (int)CSCDEnumTypeList.size() + 1;
        pEnumType->nStart = (int)CSCDEnumMemberList.size() + 1;

        // 获取 id 属性
        pugi::xml_attribute idAttr = pEnumTypeElement.attribute("id");
        if (idAttr)
        {
            strncpy(pEnumType->strName, idAttr.value(), MAX_NAME_LEN - 1);
        }

        // 遍历当前 EnumType 下的所有 EnumVal 子节点
        for (pugi::xml_node pEnumValElement = pEnumTypeElement.child("EnumVal");
             pEnumValElement;
             pEnumValElement = pEnumValElement.next_sibling("EnumVal"))
        {
            CEnumMember *pEnumMember = (CEnumMember *)calloc(1, sizeof(CEnumMember));
            if (!pEnumMember) continue;

            pEnumMember->nId = (int)CSCDEnumMemberList.size() + 1;
            pEnumMember->nEnumType_id = pEnumType->nId;

            // 获取 EnumVal 的文本内容
            const char* valText = pEnumValElement.text().get();
            if (valText && strlen(valText) > 0)
            {
                strncpy(pEnumMember->strName, valText, MAX_NAME_LEN - 1);
            }

            pEnumMember->nValue = -1;
            pugi::xml_attribute ordAttr = pEnumValElement.attribute("ord");
            if (ordAttr)
            {
                pEnumMember->nValue = ordAttr.as_int();
            }

            CSCDEnumMemberList.push_back(*pEnumMember);
            free(pEnumMember);
        }

        CSCDEnumTypeList.push_back(*pEnumType);
        free(pEnumType);
    }

    return true;
}

bool ScdParser::parseDAType(pugi::xml_node &pDataTypeTemplatesElement)
{
    for (pugi::xml_node pDATypeElement = pDataTypeTemplatesElement.child("DAType");
         pDATypeElement;
         pDATypeElement = pDATypeElement.next_sibling("DAType"))
    {
        CDaType *pDaType = (CDaType *)calloc(1, sizeof(CDaType));
        if (!pDaType) return false;

        pDaType->nId = (int)CSCDDaTypeList.size() + 1;
        pDaType->nStart = (int)CSCDDaMemberList.size() + 1;

        // 获取 id 属性
        strncpy(pDaType->strName, pDATypeElement.attribute("id").value(), MAX_NAME_LEN - 1);

        // 遍历当前 DAType 下的所有 BDA 子节点
        for (pugi::xml_node pBDAElement = pDATypeElement.child("BDA");
             pBDAElement;
             pBDAElement = pBDAElement.next_sibling("BDA"))
        {
            CDaMember *pDaMember = (CDaMember *)calloc(1, sizeof(CDaMember));
            if (!pDaMember) continue;

            pDaMember->nId = (int)CSCDDaMemberList.size() + 1;
            pDaMember->nDaType_id = pDaType->nId;
            pDaMember->nType_id = -1;

            // 获取 BDA 的 name, bType, type 属性
            strncpy(pDaMember->strName, pBDAElement.attribute("name").value(), MAX_NAME_LEN - 1);
            strncpy(pDaMember->strBType, pBDAElement.attribute("bType").value(), MAX_NAME_LEN - 1);
            strncpy(pDaMember->strType, pBDAElement.attribute("type").value(), MAX_NAME_LEN - 1);

            // 类型关联逻辑
            if (strcmp(pDaMember->strBType, "Struct") == 0)
            {
                // bType为Struct，标记为 -2，等所有 DAType 解析完后再统一查找
                pDaMember->nType_id = -2;
            }
            else if (strcmp(pDaMember->strBType, "Enum") == 0)
            {
                // bType为Enum，从已解析的 Enum 列表中查找 ID
                for (auto& enType : CSCDEnumTypeList)
                {
                    if (strcmp(enType.strName, pDaMember->strType) == 0)
                    {
                        pDaMember->nType_id = enType.nId;
                        break;
                    }
                }
            }

            CSCDDaMemberList.push_back(*pDaMember);
            free(pDaMember);
        }

        CSCDDaTypeList.push_back(*pDaType);
        free(pDaType);
    }

    // --- 二次遍历：BDA 查找引用的 DAType，更新 nType_id ---
    // 解决“先引用后定义”的问题
    for (auto& mda : CSCDDaMemberList)
    {
        if (mda.nType_id == -2)
        {
            for (auto& daType : CSCDDaTypeList)
            {
                if (strcmp(daType.strName, mda.strType) == 0)
                {
                    mda.nType_id = daType.nId;
                    break;
                }
            }
        }
    }

    return true;
}

bool ScdParser::parseDOType(pugi::xml_node &pDataTypeTemplatesElement)
{
    // 遍历所有 DOType 节点
    for (pugi::xml_node pDOTypeElement = pDataTypeTemplatesElement.child("DOType");
         pDOTypeElement;
         pDOTypeElement = pDOTypeElement.next_sibling("DOType"))
    {
        CDoType *pDoType = (CDoType *)calloc(1, sizeof(CDoType));
        if (!pDoType) return false;

        pDoType->nId = (int)CSCDDoTypeList.size() + 1;
        pDoType->nStart = (int)CSCDDoMemberList.size() + 1;

        // 获取属性 id, cdc, desc
        strncpy(pDoType->strType, pDOTypeElement.attribute("id").value(), MAX_NAME_LEN - 1);
        strncpy(pDoType->strCDCName, pDOTypeElement.attribute("cdc").value(), MAX_NAME_LEN - 1);
        strncpy(pDoType->strDesc, pDOTypeElement.attribute("desc").value(), MAX_DESC_LEN - 1);

        // --- 1. 解析 DA 子节点 ---
        for (pugi::xml_node pDAElement = pDOTypeElement.child("DA");
             pDAElement;
             pDAElement = pDAElement.next_sibling("DA"))
        {
            CDoMember *pDoMember = (CDoMember *)calloc(1, sizeof(CDoMember));
            if (!pDoMember) continue;

            pDoMember->nId = (int)CSCDDoMemberList.size() + 1;
            pDoMember->nDotype_id = pDoType->nId;
            pDoMember->nKind = 0;   // DA 标记为 0
            pDoMember->nType_id = -1;

            // 获取基础属性
            strncpy(pDoMember->strDaName, pDAElement.attribute("name").value(), MAX_NAME_LEN - 1);
            strncpy(pDoMember->strBType, pDAElement.attribute("bType").value(), MAX_NAME_LEN - 1);
            strncpy(pDoMember->strType, pDAElement.attribute("type").value(), MAX_NAME_LEN - 1);
            strncpy(pDoMember->strFC, pDAElement.attribute("fc").value(), MAX_FC_LEN + 1);

            // 使用 as_bool() 自动处理 "true"/"false" 字符串转换
            pDoMember->bDchg = pDAElement.attribute("dchg").as_bool();
            pDoMember->bQchg = pDAElement.attribute("qchg").as_bool();
            pDoMember->bDupd = pDAElement.attribute("dupd").as_bool();

            // 查找引用类型
            if (strcmp(pDoMember->strBType, "Struct") == 0)
            {
                // 查找 DaType
                const char* typeRef = pDAElement.attribute("type").value();
                for (auto& daType : CSCDDaTypeList) {
                    if (strcmp(daType.strName, typeRef) == 0) {
                        pDoMember->nType_id = daType.nId;
                        break;
                    }
                }
            }
            else if (strcmp(pDoMember->strBType, "Enum") == 0)
            {
                // 查找 EnumType
                for (auto& enType : CSCDEnumTypeList) {
                    if (strcmp(enType.strName, pDoMember->strType) == 0) {
                        pDoMember->nType_id = enType.nId;
                        break;
                    }
                }
            }

            CSCDDoMemberList.push_back(*pDoMember);
            free(pDoMember);
        }

        // --- 2. 解析 SDO 子节点 ---
        for (pugi::xml_node pSDOElement = pDOTypeElement.child("SDO");
             pSDOElement;
             pSDOElement = pSDOElement.next_sibling("SDO"))
        {
            CDoMember *pDoMember = (CDoMember *)calloc(1, sizeof(CDoMember));
            if (!pDoMember) continue;

            pDoMember->nId = (int)CSCDDoMemberList.size() + 1;
            pDoMember->nDotype_id = pDoType->nId;
            pDoMember->nKind = 1;      // SDO 标记为 1
            pDoMember->nType_id = -2;  // 标记为 -2，待后续二次遍历查找

            strncpy(pDoMember->strDaName, pSDOElement.attribute("name").value(), MAX_NAME_LEN - 1);
            strncpy(pDoMember->strType, pSDOElement.attribute("type").value(), MAX_NAME_LEN - 1);

            CSCDDoMemberList.push_back(*pDoMember);
            free(pDoMember);
        }

        CSCDDoTypeList.push_back(*pDoType);
        free(pDoType);
    }

    // --- 3. SDO 查找引用的 DOType，更新 nType_id ---
    // 这一步必须在所有 DOType 解析完成后进行，因为 SDO 可能引用后面定义的 DOType
    for (auto& mdo : CSCDDoMemberList)
    {
        if (mdo.nType_id == -2)
        {
            for (auto& doType : CSCDDoTypeList)
            {
                if (strcmp(doType.strType, mdo.strType) == 0)
                {
                    mdo.nType_id = doType.nId;
                    break;
                }
            }
        }
    }

    return true;
}

bool ScdParser::parseLNodeType(pugi::xml_node &pDataTypeTemplatesElement)
{
    // 遍历所有 LNodeType 节点
    for (pugi::xml_node pLNodeTypeElement = pDataTypeTemplatesElement.child("LNodeType");
         pLNodeTypeElement;
         pLNodeTypeElement = pLNodeTypeElement.next_sibling("LNodeType"))
    {
        CLnType *pLnType = (CLnType *)calloc(1, sizeof(CLnType));
        if (!pLnType) return false;

        pLnType->nId = (int)CSCDLnTypeList.size() + 1;
        pLnType->nStart = (int)CSCDLnMemberList.size() + 1;

        // 获取 desc, lnClass, id 属性
        // 建议：如果 desc 包含中文且 SCD 是 UTF-8 编码，可使用 UTF_8Decode
        strncpy(pLnType->strDesc, pLNodeTypeElement.attribute("desc").value(), MAX_DESC_LEN - 1);
        strncpy(pLnType->strLnclass, pLNodeTypeElement.attribute("lnClass").value(), MAX_CLASS_LEN - 1);
        strncpy(pLnType->strType, pLNodeTypeElement.attribute("id").value(), MAX_NAME_LEN - 1);

        // --- 解析 DO 子节点 ---
        for (pugi::xml_node pDOElement = pLNodeTypeElement.child("DO");
             pDOElement;
             pDOElement = pDOElement.next_sibling("DO"))
        {
            CLnMember *pLnMember = (CLnMember *)calloc(1, sizeof(CLnMember));
            if (!pLnMember) continue;

            pLnMember->nId = (int)CSCDLnMemberList.size() + 1;
            pLnMember->nLnType_id = pLnType->nId;
            pLnMember->nDoType_id = -1;

            const char* doTypeRef = pDOElement.attribute("type").value();

            // 在已解析的 CSCDDoTypeList 中查找匹配的 DOType ID
            for (auto& doType : CSCDDoTypeList)
            {
                if (strcmp(doType.strType, doTypeRef) == 0)
                {
                    pLnMember->nDoType_id = doType.nId;
                    break;
                }
            }

            // 获取 DO 的 name, type, desc 属性
            strncpy(pLnMember->strDoName, pDOElement.attribute("name").value(), MAX_NAME_LEN - 1);
            strncpy(pLnMember->strType, doTypeRef, MAX_NAME_LEN - 1);
            strncpy(pLnMember->strDoDesc, pDOElement.attribute("desc").value(), MAX_DESC_LEN - 1);

            CSCDLnMemberList.push_back(*pLnMember);
            free(pLnMember);
        }

        CSCDLnTypeList.push_back(*pLnType);
        free(pLnType);
    }

    return true;
}
