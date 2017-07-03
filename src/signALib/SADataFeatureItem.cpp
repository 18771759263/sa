#include "SADataFeatureItem.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#define ROLE_ITEM_TYPE (Qt::UserRole + 1234)
#define XML_STR_ROOT__ "dfi"
#define XML_STR_ITEM__ "item"
#define XML_ATT_TYPE__ "type"
#define XML_ATT_NAME__ "name"
SADataFeatureItem::SADataFeatureItem():QStandardItem()
{

}

SADataFeatureItem::SADataFeatureItem(const QString &text):QStandardItem(text)
{
    setItemType(DescribeItem);
}

//SADataFeatureItem::SADataFeatureItem(const SADataFeatureItem::ItemType &type, const QString &text):QStandardItem(text)
//{
//    setItemType(type);
//}

SADataFeatureItem::SADataFeatureItem(double data):QStandardItem()
{
    setText(QString::number(data));
    setItemType(ValueItem);
}

SADataFeatureItem::SADataFeatureItem(int data):QStandardItem()
{
    setText(QString::number(data));
    setItemType(ValueItem);
}

SADataFeatureItem::SADataFeatureItem(const QPointF& data):QStandardItem()
{
    setText(QString("%1,%2").arg(data.x()).arg(data.y()));
    setItemType(PointItem);
}



SADataFeatureItem::~SADataFeatureItem()
{

}
///
/// \brief 子条目添加点序列条目
/// \param name
/// \param datas
///
void SADataFeatureItem::appendItem(const QString &name,const QVector<QPointF> &datas)
{
    SADataFeatureItem* item = new SADataFeatureItem(name);
    for(int i=0;i<datas.size();++i)
    {
        item->appendItem(QString::number(i+1),datas[i]);
    }
    appendRow(item);
}
///
/// \brief 子条目添加数组序列
/// \param datas
///
void SADataFeatureItem::appendItem(const QString &name,const QVector<double> &datas)
{
    SADataFeatureItem* item = new SADataFeatureItem(name);
    for(int i=0;i<datas.size();++i)
    {
        item->appendItem(QString::number(i+1),datas[i]);
    }
    appendRow(item);
}

void SADataFeatureItem::appendItem(const QString &name, int data)
{
    appendRow({new SADataFeatureItem(name),new SADataFeatureItem(data)});
}
///
/// \brief 插入一个double内容
/// \param data
/// \param name
///
void SADataFeatureItem::appendItem(const QString &name,double data)
{
    appendRow({new SADataFeatureItem(name),new SADataFeatureItem(data)});
}
///
/// \brief 插入一个QPointF内容
/// \param name
/// \param data
///
void SADataFeatureItem::appendItem(const QString &name, const QPointF &data)
{
    appendRow({new SADataFeatureItem(name),new SADataFeatureItem(data)});
}

QVariant SADataFeatureItem::displayRole() const
{
    return data(Qt::DisplayRole);
}

SADataFeatureItem::ItemType SADataFeatureItem::getItemType() const
{
    QVariant var = data(ROLE_ITEM_TYPE);
    if(!var.isValid())
    {
        return UnKnow;
    }
    bool isOK = false;
    int d = var.toInt(&isOK);
    if(!isOK)
    {
        return UnKnow;
    }
    return static_cast<SADataFeatureItem::ItemType>(d);
}

void SADataFeatureItem::setItemType(SADataFeatureItem::ItemType type)
{
    setData((int)type,ROLE_ITEM_TYPE);
}


///
/// \brief 获取最顶层条目
/// \return
/// \note 需要保证AbstractDataFeatureItem的子对象都是基于AbstractDataFeatureItem的子类
///
SADataFeatureItem *SADataFeatureItem::topParent() const
{
    SADataFeatureItem* cur = const_cast<SADataFeatureItem *>(this);
    SADataFeatureItem* par = static_cast<SADataFeatureItem *>(cur->parent());
    while(par != nullptr)
    {
        cur = par;
        par = static_cast<SADataFeatureItem *>(cur->parent());
    }
    return cur;
}
///
/// \brief 转换为xml
///
/// 此转换不是标准xml文件，而是以<fi>打头</fi>结尾的xml文件
/// \return
///
QString SADataFeatureItem::toXml() const
{
    return toXml(this);
}
///
/// \brief 从xml转换为item
/// \param xml
///
void SADataFeatureItem::fromXml(const QString &xml)
{
    fromXml(xml,this);
}
///
/// \brief 转换为xml
///
/// 此转换不是标准xml文件，而是以<fi>打头</fi>结尾的xml文件
/// \param item SADataFeatureItem指针
/// \return
///
QString SADataFeatureItem::toXml(const SADataFeatureItem *item)
{
    QString str;
    QXmlStreamWriter xml(&str);
    xml.setCodec("UTF-8");
    xml.writeStartElement(XML_STR_ROOT__);
    writeItem(&xml,static_cast<const QStandardItem*>(item));
    xml.writeEndElement();
    return str;
}
///
/// \brief 从xml转换为item
/// \param xml
/// \param item
///
void SADataFeatureItem::fromXml(const QString &xmlStr, SADataFeatureItem *item)
{
    QXmlStreamReader xml(xmlStr);
    while(!xml.atEnd())
    {
        if(xml.readNextStartElement())
        {
            if(xml.name()==XML_STR_ROOT__)
            {
                //读取到根目录
                readItem(&xml,item);
            }
        }

    }

}

int SADataFeatureItem::getTypeInt(const QStandardItem *item)
{
    QVariant var = item->data(ROLE_ITEM_TYPE);
    if(!var.isValid())
    {
        return 0;
    }
    bool isOK = false;
    return var.toInt(&isOK);
}

void SADataFeatureItem::writeItem(QXmlStreamWriter *xml, const QStandardItem *item)
{
    if(nullptr == item)
    {
        return;
    }
    xml->writeStartElement(XML_STR_ITEM__);
    QXmlStreamAttributes attrs;
    attrs.append(QXmlStreamAttribute(XML_ATT_TYPE__,QString::number(getTypeInt(item))));
    attrs.append(QXmlStreamAttribute(XML_ATT_NAME__,item->text()));
    xml->writeAttributes(attrs);
    //递归子节点
    const int subItemRow = item->rowCount();
    const int subItemColumn = item->columnCount();
    for(int i=0;i<subItemRow;++i)
    {
        for(int j=0;j<subItemColumn;++j)
        {
            writeItem(xml,item->child(i,j));
        }
    }
    xml->writeEndElement();
}

void SADataFeatureItem::readItem(QXmlStreamReader *xml, SADataFeatureItem *item)
{
    while(!xml->atEnd())
    {
        if(xml->readNextStartElement())
        {
            if(xml->name()==XML_STR_ITEM__)
            {
                //读取到条目
                QXmlStreamAttributes atts = xml->attributes();
                for(int i = 0;i < atts.size();++i)
                {
                    if(XML_ATT_TYPE__ == atts[i].name())
                    {
                        bool isOK = false;
                        int v = atts[i].value().toInt(&isOK);
                        if(!isOK)
                        {
                            continue;
                        }
                        item->setItemType(static_cast<SADataFeatureItem::ItemType>(v));
                    }
                    else if(XML_ATT_NAME__ == atts[i].name())
                    {
                        item->setText(atts[i].value().toString());
                    }
                }
            }
        }

    }
}