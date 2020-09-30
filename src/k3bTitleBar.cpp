/*
 * Copyright (C) 2020  KylinSoft Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>

#include <QDebug>

#include "k3bTitleBar.h"
#include "k3bappdevicemanager.h"
#include "k3bdevice.h"
#include "k3bapplication.h"
#include <KMountPoint>
#include "k3bMd5Dialog.h"
#include <klocalizedstring.h>

K3b::TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{

    setFixedHeight(50);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMenubutton = new QToolButton(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(30,30);
    m_pIconLabel->setStyleSheet("QLabel{background-image: url(:/new/prefix1/pic/logo.png);"
                                "background-color:rgb(255,255,255);"
                                "background-repeat: no-repeat;}");

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMenubutton->setFixedSize(30, 30);
    m_pMinimizeButton->setFixedSize(30, 30);
    m_pMaximizeButton->setFixedSize(30, 30);
    m_pCloseButton->setFixedSize(30, 30);

    m_pMenubutton->setObjectName("menuButton");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMenubutton->setToolTip(i18n("Menu__"));
    m_pMinimizeButton->setToolTip(i18n("Minimize__"));
    m_pMaximizeButton->setToolTip(i18n("Maximize__"));
    m_pCloseButton->setToolTip(i18n("Close__"));

    m_pTitleLabel->setContentsMargins(8,0,0,0);
    m_pTitleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    //m_pMenubutton->setIcon( QIcon::fromTheme( "setting-default" ) );
    m_pMenubutton->setStyleSheet("QToolButton{border-image: url(:/icon/icon/icon-设置-默认.png);"
                                 "border:none;background-color:rgb(255, 255, 255);"
                                 "border-radius: 4px;}"
                                "QToolButton:hover{border-image: url(:/icon/icon/icon-设置-悬停点击.png);"
                                 "border:none;background-color:rgb(61, 107, 229);"
                                 "border-radius: 4px;}"
                                "QToolButton:checked{border-image: url(:/icon/icon/icon-设置-悬停点击.png);"
                                 "border:none;background-color:rgb(50, 87, 202);"
                                 "border-radius: 4px;}"
                                 "QToolButton::menu-indicator{image:none;}");

    m_pMinimizeButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/icon-最小化-默认.png);"
                                     "border:none;background-color:rgb(255, 255, 255);"
                                     "border-radius: 4px;}"
                                "QPushButton:hover{border-image: url(:/icon/icon/icon-最小化-悬停点击.png);"
                                     "border:none;background-color:rgb(61, 107, 229);"
                                     "border-radius: 4px;}"
                                "QPushButton:pressed{border-image: url(:/icon/icon/icon-最小化-悬停点击.png);"
                                     "border:none;background-color:rgb(50, 87, 202);"
                                     "border-radius: 4px;}");

    m_pMaximizeButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/icon-最大化-默认.png);"
                                     "border:none;background-color:rgb(255, 255, 255);"
                                     "border-radius: 4px;}"
                                "QPushButton:hover{border-image: url(:/icon/icon/icon-最大化-悬停点击.png);"
                                     "border:none;background-color:rgb(61, 107, 229);"
                                     "border-radius: 4px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/icon-最大化-悬停点击.png);"
                                     "border:none;background-color:rgb(50, 87, 202);"
                                     "border-radius: 4px;}");

    m_pCloseButton->setStyleSheet("QPushButton{border-image: url(:/icon/icon/icon-关闭-默认.png);"
                                  "border:none;background-color:rgb(255, 255, 255);"
                                  "border-radius: 4px;}"
                                "QPushButton:hover{border-image: url(:/icon/icon/icon-关闭-悬停点击.png);"
                                  "border:none;background-color:rgb(248, 100, 87);"
                                  "border-radius: 4px;}"
                                 "QPushButton:pressed{border-image: url(:/icon/icon/icon-关闭-悬停点击.png);"
                                    "border:none;background-color:rgba(228, 76, 80, 1);"
                                    "border-radius: 4px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/icon-关闭-悬停点击.png);"
                                  "border:none;background-color:rgb(228, 236, 80);"
                                  "border-radius: 4px;}");

    QMenu *menu = new QMenu(this);  //新建菜单

    menu->addAction(QIcon(""), i18n("popup"), this,&TitleBar::popup);
    menu->addAction(QIcon(""), i18n("Clean"), this,&TitleBar::clean);
    menu->addSeparator();
    menu->addAction(QIcon(""), i18n("MD5"), this,&TitleBar::md5);
    menu->addAction(QIcon(""), i18n("filter"), this, &TitleBar::filter);
    menu->addSeparator();
    //menu->addAction(QIcon(""), i18n("help"), this,&TitleBar::help);
    //menu->addAction(QIcon(""), i18n("about"), this,&TitleBar::about);

    //menu->setStyleSheet("QMenu::item:hover{background-color:#6b8eeb;}");
    //menu->setStyleSheet("QMenu:hover{background-color:#ffffff;}");

    m_pMenubutton->setPopupMode(QToolButton::InstantPopup); //点击模式
    m_pMenubutton->setMenu(menu);  //下拉菜单


    //QHBoxLayout *mainWidgetLayout = new QHBoxLayout(this);
    //QWidget *mainWidget = new QWidget;
    QLabel* label_top = new QLabel( this );
    label_top->setFixedHeight( 50 );
    QHBoxLayout *pLayout = new QHBoxLayout( label_top );

    //mainWidgetLayout->addWidget(mainWidget);
    //mainWidget->setLayout(pLayout);
    //mainWidgetLayout->setMargin(0);
    pLayout->setContentsMargins( 0, 4, 4, 16);
    pLayout->setSpacing(0);
    pLayout->addStretch(0);
    label_top->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
    pLayout->addWidget(m_pMenubutton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pMinimizeButton);
    //pLayout->addWidget(m_pMaximizeButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pCloseButton);
    //pLayout->addSpacing(3);

    QVBoxLayout* mainLayout = new QVBoxLayout( this );
    mainLayout->setContentsMargins( 0, 4, 4, 0);
    mainLayout->addWidget( label_top );
    mainLayout->addStretch( 0 );

    dlg = new FileFilter( this );


    connect(dlg, SIGNAL(setHidden(bool)), this, SLOT(callHidden(bool)));
    connect(dlg, SIGNAL(setBroken(bool)), this, SLOT(callBroken(bool)));
    connect(dlg, SIGNAL(setReplace(bool)), this, SLOT(callReplace(bool)));


    connect(m_pMenubutton, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pMinimizeButton, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pMaximizeButton, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pCloseButton, &QPushButton::clicked, this, &TitleBar::onClicked);
}

K3b::TitleBar::~TitleBar()
{
   delete m_pIconLabel;
   delete m_pTitleLabel;
   delete m_pMenubutton;
   delete m_pMinimizeButton;
   delete m_pMaximizeButton;
   delete m_pCloseButton;
   if (dlg) delete dlg;
}

void K3b::TitleBar::callHidden(bool flag)
{
    qDebug() << "call hidden" << flag;
    emit setIsHidden(flag);
}

void K3b::TitleBar::callBroken(bool flag)
{
    emit setIsBroken(flag);
}

void K3b::TitleBar::callReplace(bool flag)
{
    emit setIsReplace(flag);
}
void K3b::TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    //Q_EMIT m_pMaximizeButton->clicked();
}

void K3b::TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        QWidget *pWindow = this->window();
        pWindow->move(pWindow->pos() + (event->globalPos() - mLastMousePosition));
        mLastMousePosition = event->globalPos();
    }
}

void K3b::TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}

void K3b::TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void K3b::TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
            updateMaximize();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
            updateMaximize();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
            exit(0);
        }
    }
}

void K3b::TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            m_pMaximizeButton->setToolTip(tr("Maximize"));
        }

        m_pMaximizeButton->setStyle(QApplication::style());
    }
}

void K3b::TitleBar::clean()
{
    formatMedium( testDev );
}

void K3b::TitleBar::formatMedium( K3b::Device::Device* dev )
{
    K3b::MediaFormattingDialog dlg( this );
    dlg.setDevice( dev );
    dlg.exec();
}

void K3b::TitleBar::popup()
{
    QList<K3b::Device::Device*> device_list = k3bappcore->appDeviceManager()->allDevices();
    foreach(K3b::Device::Device* dev, device_list){
        if ( dev ){
            KMountPoint::Ptr mountPoint = KMountPoint::currentMountPoints().findByDevice( dev->blockDeviceName() );
            if ( dev->diskInfo().diskState() == K3b::Device::STATE_EMPTY ){
                dev->eject();
                break;
            }
            if( mountPoint ){
                dev->eject();
                break;
            }
        }
    }
}

void K3b::TitleBar::md5()
{
    K3b::Md5Check* dialog = new K3b::Md5Check( this );
    dialog->show();
}

void K3b::TitleBar::filter()
{
    dlg->show();
}
void K3b::TitleBar::help()
{

}
void K3b::TitleBar::about()
{

}

void K3b::TitleBar::isHidden(bool flag)
{
    qDebug() << "Set title bar dialog hidden to " << flag;
    dlg->setIsHidden(flag);
}

void K3b::TitleBar::isBroken(bool flag)
{
    dlg->setIsBroken(flag);
}

void K3b::TitleBar::isReplace(bool flag)
{
    dlg->setIsReplace(flag);
}
