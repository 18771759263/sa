#ifndef SARIBBONPANNEL_H
#define SARIBBONPANNEL_H
#include "SARibbonGlobal.h"
#include <QWidget>
#include "SARibbonToolButton.h"
class SARibbonGallery;
class QGridLayout;
class SARibbonPannelOptionButton;
///
/// \brief The SARibbonPannel class
///
class SA_RIBBON_EXPORT SARibbonPannel : public QWidget
{
    Q_OBJECT
public:
    SARibbonPannel(QWidget* parent = 0);
    using QWidget::addAction;
    SARibbonToolButton* addLargeToolButton(const QString& text,const QIcon& icon,QToolButton::ToolButtonPopupMode popMode);
    SARibbonToolButton* addLargeAction(QAction *action);
    SARibbonToolButton* addSmallToolButton(const QString& text,const QIcon& icon,QToolButton::ToolButtonPopupMode popMode);
    SARibbonToolButton *addSmallAction(QAction *action);
    SARibbonGallery* addGallery();
    void addSeparator();
    void addWidget(QWidget* w, int row=0);
    void addWidget(QWidget* w, int row,int rowSpan);
    void addOptionAction(QAction* action);
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;
    void setReduce(bool isReduce);
    void setExpanding(bool isExpanding = true);
    bool isExpanding() const;
    bool event(QEvent *event);
protected:
    static QSize maxHightIconSize(const QSize& size,int height);
    void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
private:
    QGridLayout* m_gridLayout;
    QPoint m_nextElementPosition;
    int m_row;
    SARibbonPannelOptionButton* m_optionActionButton;
    int m_titleOptionButtonSpace;///< 标题和项目按钮的间隔
    int m_titleHeight;///< 标题的高度
    int m_titleY;///< 标题栏的y距离
    SARibbonToolButton* m_defaultReduceButton;///<在pannel无法显示全的时候，显示一个toolbutton用来弹出pannel
};

#endif // SARIBBONPANNEL_H
