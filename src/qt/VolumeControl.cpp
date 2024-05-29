/*******************************************************************************
  OmicronTK_qt

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: MIT License

  Copyright 2018-2019, Fábio Pichler

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "OmicronTK/qt/VolumeControl.hpp"
#include "OmicronTK/qt/Widget.hpp"
#include "OmicronTK/qt/Slider.hpp"

#include <QMenu>
#include <QLabel>
#include <QWidgetAction>
#include <QBoxLayout>
#include <QEvent>

namespace OmicronTK {
namespace qt {

VolumeControl::VolumeControl(QWidget *parent)
    : QPushButton(parent)
{
    m_mute = false;
    setToolTip("Ajustar o Volume");

    QWidget *popup = new QWidget(this);
    popup->setMinimumWidth(240);

    m_muteButton = new QPushButton(popup);
    m_muteButton->setProperty("class", "muteButton iconButton smallIconButton");
    m_muteButton->setToolTip("Desativar som");

    m_volumeSlider = new Slider(popup);
    m_volumeSlider->setOrientation(Qt::Horizontal);
    m_volumeSlider->setRange(0, 100);

    m_volumeLabel = new QLabel(popup);
    m_volumeLabel->setAlignment(Qt::AlignCenter);
    m_volumeLabel->setText("0%");
    m_volumeLabel->setMinimumWidth(45);

    connect(m_muteButton, &QPushButton::clicked, this, &VolumeControl::changeMute);
    connect(m_volumeSlider, &QAbstractSlider::valueChanged, this, &VolumeControl::volumeChanged);
    connect(m_volumeSlider, &QAbstractSlider::valueChanged, this, &VolumeControl::updateVolume);

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setContentsMargins(2, 2, 2, 2);
    popupLayout->addWidget(m_volumeLabel);
    popupLayout->addWidget(m_volumeSlider);
    popupLayout->addSpacing(4);
    popupLayout->addWidget(m_muteButton);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    QMenu *menu = new QMenu(this);
    menu->addAction(action);
    menu->installEventFilter(this);

    setMenu(menu);
}

int VolumeControl::volume() const
{
    return m_volumeSlider->value();
}

//================================================================================================================
// public slots
//================================================================================================================

void VolumeControl::setVolume(int volume)
{
    m_volumeSlider->setValue(volume);
}

//================================================================================================================
// private slots
//================================================================================================================

void VolumeControl::updateVolume(int volume)
{
    m_volumeLabel->setText(QString(QString::number(volume)).append("%"));
    mute(false, false);
}

void VolumeControl::changeMute()
{
    if (m_mute)
        mute(false);
    else
        mute(true);
}

//================================================================================================================
// private
//================================================================================================================

void VolumeControl::mute(bool act, bool event)
{
    if (act == m_mute)
        return;

    if (act)
    {
        m_mute = true;

        setProperty("mute", true);
        m_muteButton->setProperty("mute", true);
        m_muteButton->setToolTip("Ativar som");

        if (event)
            emit volumeChanged(0);
    }
    else
    {
        m_mute = false;

        setProperty("mute", false);
        m_muteButton->setProperty("mute", false);
        m_muteButton->setToolTip("Desativar som");

        if (event)
            emit volumeChanged(m_volumeSlider->value());
    }

    Widget::updateStyle(m_muteButton);
    Widget::updateStyle(this);
}

bool VolumeControl::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Show && obj == menu())
    {
        menu()->move(mapToGlobal(QPoint(width() - menu()->width(), (height() - menu()->height()) / 2)));
        return true;
    }

    return false;
}

}
}
