/*
 * @file Xml.cpp
 * @brief
 *
 * @version 1.0
 * @date Sat Sep 22 14:47:49 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "xml/Xml.h"

#include <stdio.h>

#include <string>
#include <list>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#define XML_VERSION             "1.0"
#define XML_ENCODING            "UTF-8"
#define XML_INDENT_LEVEL        0
#define XML_FORMAT_ALLOWED      1

namespace ossfs
{


Xml::Xml()
{
    _doc = NULL;
}

Xml::~Xml()
{
    xmlFreeDoc(_doc);
    _doc = NULL;
}

XmlNode *
Xml::loadFile(const std::string &file)
{
    if (NULL != _doc) {
        fprintf(stderr, "[WARNING] In Xml::loadFile, _doc != NULL\n");
        xmlFreeDoc(_doc);
        _doc = NULL;
    }

    _doc = xmlReadFile(file.c_str(), XML_ENCODING,
                       int(XML_PARSE_RECOVER));

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::loadFile, xmlReadFile() error\n");
        return NULL;
    }

    xmlNode *rootNode = xmlDocGetRootElement(_doc);

    if (NULL == rootNode) {
        fprintf(stderr, "[ERROR] In Xml::loadFile, "
                "xmlDocGetRootElement() error\n");
        return NULL;
    }

    return rootNode;
}


XmlNode *
Xml::loadMemory(const char *buf, int size)
{
    if (NULL == buf) {
        fprintf(stderr, "[ERROR] In Xml::loadMemory, buf == NULL\n");
        return NULL;
    }

    if (NULL != _doc) {
        fprintf(stderr, "[ERROR] In Xml::loadMemory, _doc != NULL\n");
        xmlFreeDoc(_doc);
        _doc = NULL;
    }

    _doc = xmlReadMemory(
               buf,
               size,
               NULL,
               XML_ENCODING,
               int(XML_PARSE_RECOVER)
           );

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::loadMemory, xmlReadMemory() error\n");
        return NULL;
    }

    xmlNode *rootNode = xmlDocGetRootElement(_doc);

    if (NULL == rootNode) {
        fprintf(stderr, "[ERROR] In Xml::loadMemory, "
                "xmlDocGetRootElement() error\n");
        return NULL;
    }

    return rootNode;
}

bool
Xml::saveToBuffer(XmlNode *curNode, std::string *buf) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::saveToBuffer, curNode == NULL\n");
        return false;
    }

    if (NULL == buf) {
        fprintf(stderr, "[ERROR] In Xml::saveToBuffer, buf == NULL\n");
        return false;
    }

    xmlBuffer *xmlBuf = xmlBufferCreate();

    if (NULL == xmlBuf) {
        fprintf(stderr, "[ERROR] In Xml::saveToBuffer, "
                "xmlBufferCreate() error\n");
        return false;
    }

    int bytes = xmlNodeDump(xmlBuf, _doc, curNode,
                            XML_INDENT_LEVEL, XML_FORMAT_ALLOWED);

    if (bytes < 0) {
        fprintf(stderr, "[ERROR] In Xml::saveToBuffer, xmlNodeDump() error\n");
        return false;
    }

    *buf = (const char *)(xmlBuf->content);
    xmlBufferFree(xmlBuf);
    xmlBuf = NULL;

    return true;
}

bool
Xml::saveToBuffer(std::string *buf) const
{
    if (NULL == buf) {
        fprintf(stderr, "[ERROR] In Xml::saveToBuffer, buf == NULL\n");
        return false;
    }

    xmlNode *rootNode = xmlDocGetRootElement(_doc);

    if (NULL == rootNode) {
        fprintf(stderr, "[ERROR] In Xml::saveToBuffer, "
                "xmlDocGetRootElement() error\n");
        return false;
    }

    return saveToBuffer(rootNode, buf);
}

bool
Xml::saveToFile(const std::string &file) const
{
    int nwrite = xmlSaveFormatFileEnc(file.c_str(), _doc,
                                      XML_ENCODING, XML_FORMAT_ALLOWED);

    if (-1 == nwrite) {
        fprintf(stderr, "[ERROR] In Xml::saveToFile, "
                "xmlSaveFormatFileEnc() error\n");
        return false;
    }

    return true;
}

XmlNode *
Xml::createDocument(const std::string &rootName)
{
    if (NULL != _doc) {
        fprintf(stderr, "[WARNING] In Xml::createDocument, _doc != NULL\n");
        xmlFreeDoc(_doc);
        _doc = NULL;
    }

    _doc = xmlNewDoc(BAD_CAST XML_VERSION);

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::createDocument, xmlNewDoc() error\n");
        return NULL;
    }

    xmlNode *rootNode = xmlNewNode(NULL, BAD_CAST rootName.c_str());
    xmlDocSetRootElement(_doc, rootNode);

    return rootNode;
}

XmlNode *
Xml::getRootNode() const
{
    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getRootNode, _doc == NULL\n");
        return NULL;
    }

    return xmlDocGetRootElement(_doc);
}


XmlNode *
Xml::getParentNode(XmlNode *curNode) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getParentNode, curNode == NULL\n");
        return NULL;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getParentNode, _doc == NULL\n");
        return NULL;
    }

    return curNode->parent;
}

XmlNode *
Xml::getChildNode(XmlNode *curNode) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getFirstChildNode, "
                "curNode == NULL\n");
        return NULL;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getFirstChildNode, _doc == NULL\n");
        return NULL;
    }

    return curNode->children;
}

bool
Xml::getChildNodes(XmlNode *curNode, std::list<XmlNode *> *nodeList) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodes, curNode == NULL\n");
        return false;
    }

    if (NULL == nodeList) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodes, nodeList == NULL\n");
        return false;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodes, _doc == NULL\n");
        return false;
    }

    xmlNode *childNode = curNode->children;

    while (NULL != childNode) {
        nodeList->push_back(childNode);
        childNode = childNode->next;
    }

    return true;
}

XmlNode *
Xml::getChildNodeByNodeName(
    XmlNode *curNode,
    const std::string &nodeName
) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodeByNodeName, "
                "curNode == NULL\n");
        return NULL;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodeByNodeName, "
                "_doc == NULL\n");
        return NULL;
    }

    xmlNode *childNode = curNode->children;

    while (NULL != childNode) {
        if (1 == xmlStrEqual(childNode->name,
                             BAD_CAST nodeName.c_str())) {
            return childNode;
        }

        childNode = childNode->next;
    }

    return NULL;
}


bool
Xml::getChildNodesByNodeName(
    XmlNode *curNode,
    const std::string &nodeName,
    std::list<XmlNode *> *nodeList
) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodesByNodeName, "
                "curNode == NULL\n");
        return false;
    }

    if (NULL == nodeList) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodesByNodeName, "
                "nodeList == NULL\n");
        return false;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodesByNodeName, "
                "_doc == NULL\n");
        return false;
    }

    xmlNode *childNode = curNode->children;

    while (NULL != childNode) {
        if (1 == xmlStrEqual(childNode->name,
                             BAD_CAST nodeName.c_str())) {
            nodeList->push_back(childNode);
        }

        childNode = childNode->next;
    }

    return true;
}


std::string
Xml::getChildNodeValueByNodeName(
    XmlNode *curNode,
    const std::string &childNodeName
) const
{
    std::string value;

    if (getChildNodeValueByNodeName(curNode, childNodeName, &value)) {
        return value;
    }

    return "";
}

bool
Xml::getChildNodeValueByNodeName(
    XmlNode *curNode,
    const std::string &childNodeName,
    std::string *value
) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodeValueByNodeName, "
                "curNode == NULL\n");
        return false;
    }

    if (NULL == value) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodeValueByNodeName, "
                "value == NULL\n");
        return false;
    }

    xmlNode *childNode = getChildNodeByNodeName(curNode, childNodeName);

    if (NULL == childNode) {
        fprintf(stderr, "[ERROR] In Xml::getChildNodeValueByNodeName, "
                "getChildNodeByNodeName() error\n");
        return false;
    }

    return getNodeValue(childNode, value);
}

std::string
Xml::getNodeValue(XmlNode *curNode) const
{
    std::string value;

    if (getNodeValue(curNode, &value)) {
        return value;
    }

    return "";
}

bool
Xml::getNodeValue(XmlNode *curNode, std::string *value) const
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValue, curNode == NULL\n");
        return false;
    }

    if (NULL == value) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValue, value == NULL\n");
        return false;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValue, _doc == NULL\n");
        return false;
    }

    xmlChar *pXmlValue = xmlNodeGetContent(curNode);

    if (NULL == pXmlValue) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValue, "
                "xmlNodeGetContent() error\n");
        return false;
    }

    *value = (const char *) pXmlValue;
    xmlFree(pXmlValue);

    return 0;
}

bool
Xml::setNodeValue(XmlNode *curNode, const std::string &value)
{
    if (NULL == curNode) {
        fprintf(stderr, "[ERROR] In Xml::setNodeValue, curNode == NULL\n");
        return false;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::setNodeValue, _doc == NULL\n");
        return false;
    }

    xmlNodeSetContent(curNode, BAD_CAST value.c_str());

    return true;
}

XmlNode *
Xml::addChildNode(
    XmlNode *parentNode,
    const std::string &nodeName,
    const std::string &nodeValue
)
{
    if (NULL == parentNode) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, parentNode = NULL\n");
        return NULL;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, _doc == NULL\n");
        return NULL;
    }

    return xmlNewTextChild(
               parentNode, NULL,
               BAD_CAST nodeName.c_str(),
               BAD_CAST nodeValue.c_str()
           );
}

XmlNode *
Xml::addChildNode(XmlNode *parentNode, const std::string &nodeName)
{
    if (NULL == parentNode) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, parentNode == NULL\n");
        return NULL;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, _doc = NULL\n");
        return NULL;
    }

    xmlNode *childNode = xmlNewNode(NULL, BAD_CAST nodeName.c_str());

    if (NULL == childNode) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, xmlNewNode() error\n");
        return NULL;
    }

    return xmlAddChild(parentNode, childNode);
}

XmlNode *
Xml::addChildNode(XmlNode *parentNode, XmlNode *childNode)
{
    if (NULL == parentNode) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, "
                "parentNode == NULL\n");
        return NULL;
    }

    if (NULL == childNode) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, childNode == NULL\n");
        return NULL;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::addChildNode, _doc == NULL\n");
        return NULL;
    }

    return xmlAddChild(parentNode, childNode);
}


XmlNode *
Xml::getNodeByXPath(XmlNode *curNode, const std::string &xpath) const
{
    // curNode can be NULL, that means xpath is relative to root node

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, _doc == NULL\n");
        return NULL;
    }

    // init XPath context
    xmlXPathContext *context = xmlXPathNewContext(_doc);

    if (NULL == context) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, "
                "xmlXPathNewContext() error\n");
        return NULL;
    }

    // set current node
    if (NULL != curNode) {
        context->node = curNode;
    }

    // parse XPath expression
    xmlXPathObject *pResult = xmlXPathEvalExpression(
                                  BAD_CAST xpath.c_str(),
                                  context
                              );
    // release XPath context object
    xmlXPathFreeContext(context);
    context = NULL;

    if (NULL == pResult) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, "
                "xmlXPathEvalExpression() error\n");
        return NULL;
    }

    // parse result set of XPath
    xmlNode *node = NULL;
    xmlNodeSet *nodeSet = pResult->nodesetval;

    if (NULL == nodeSet) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, nodeSet == NULL\n");
        xmlXPathFreeObject(pResult);

        return NULL;
    }

    if (nodeSet->nodeNr >= 1) {
        node = nodeSet->nodeTab[0];

    } else {
        fprintf(stderr,
                "[ERROR] In Xml::getNodeByXPath, no path '%s' found\n",
                xpath.c_str());
    }

    // release result set object of xpath
    xmlXPathFreeObject(pResult);
    pResult = NULL;

    return node;
}

XmlNode *
Xml::getNodeByXPath(const std::string &xpath) const
{
    return getNodeByXPath(NULL, xpath);
}

bool
Xml::getNodesByXPath(
    XmlNode *curNode,
    const std::string &xpath,
    std::list<XmlNode *> *nodeList
) const
{
    // curNode can be NULL

    if (NULL == nodeList) {
        fprintf(stderr, "[ERROR] In Xml::getNodesByXPath, "
                "nodeList == NULL\n");
        return false;
    }

    if (NULL == _doc) {
        fprintf(stderr, "[ERROR] In Xml::getNodesByXPath, _doc == NULL\n");
        return false;
    }

    // init xpath context
    xmlXPathContext *context = xmlXPathNewContext(_doc);

    if (NULL == context) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, "
                "xmlXPathNewContext() error\n");
        return false;
    }

    // set current node
    if (NULL != curNode) {
        context->node = curNode;
    }

    // parse xpath expression
    xmlXPathObject *pResult = xmlXPathEvalExpression(
                                  BAD_CAST xpath.c_str(),
                                  context);
    // release context
    xmlXPathFreeContext(context);
    context = NULL;

    if (NULL == pResult) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, "
                "xmlXPathEvalExpression() error\n");
        return false;
    }

    // parse result set
    xmlNode *node = NULL;
    xmlNodeSet *nodeSet = pResult->nodesetval;

    if (NULL == nodeSet) {
        fprintf(stderr, "[ERROR] In Xml::getNodeByXPath, nodeSet == NULL\n");
        xmlXPathFreeObject(pResult);

        return false;
    }

    for (int i = 0; i < nodeSet->nodeNr; ++i) {
        nodeList->push_back(nodeSet->nodeTab[i]);
    }

    // release result set
    xmlXPathFreeObject(pResult);

    return true;
}

bool
Xml::getNodesByXPath(
    const std::string &xpath,
    std::list<XmlNode *> *nodeList
) const
{
    return getNodesByXPath(NULL, xpath, nodeList);
}

std::string
Xml::getNodeValueByXPath(const std::string &xpath) const
{
    std::string value;

    if (getNodeValueByXPath(xpath, &value)) {
        return value;
    }

    return "";
}

bool
Xml::getNodeValueByXPath(const std::string &xpath, std::string *value) const
{
    if (NULL == value) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValueByXPath, "
                "value == NULL\n");
        return false;
    }

    xmlNode *node = getNodeByXPath(xpath);

    if (NULL == node) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValueByXPath, "
                "getNodeByXPath() error\n");
        return false;
    }

    return getNodeValue(node, value);
}

std::string
Xml::getNodeValueByXPath(XmlNode *curNode, const std::string &xpath) const
{
    std::string value;

    if (getNodeValueByXPath(curNode, xpath, &value)) {
        return value;
    }

    return "";
}

bool
Xml::getNodeValueByXPath(
    XmlNode *curNode,
    const std::string &xpath,
    std::string *value
) const
{
    // curNode can be NULL

    if (NULL == value) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValueByXPath,"
                " value == NULL\n");
        return false;
    }

    xmlNode *node = getNodeByXPath(curNode, xpath);

    if (NULL == node) {
        fprintf(stderr, "[ERROR] In Xml::getNodeValueByXPath, "
                "getNodeByXPath() error\n");
        return false;
    }

    return getNodeValue(node, value);
}

}


