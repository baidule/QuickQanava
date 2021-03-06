/*
 Copyright (c) 2008-2017, Benoit AUTHEMAN All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author or Destrat.io nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL AUTHOR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library. Copyright 2014 Benoit AUTHEMAN.
//
// \file	Edge.qml
// \author	benoit@destrat.io
// \date	2015 06 20
//-----------------------------------------------------------------------------

import QtQuick          2.7
import QtQuick.Layouts  1.3

import QuickQanava          2.0 as Qan
import QuickGeoGL           1.0 as Qgl
import "qrc:/QuickGeoGL"    1.0 as Qgl

Qan.EdgeItem {
    id: edgeItem
    property color  color: style ? style.lineColor : Qt.black
    Qgl.Arrow {
        anchors.fill: parent
        id: arrow
        visible: edgeItem.visible && !edgeItem.hidden
        p1: edgeItem.p1
        p2: edgeItem.p2
        p2CapSize: edgeItem.style ? edgeItem.style.arrowSize : 4
        lineWidth: edgeItem.style ? edgeItem.style.lineWidth : 2
        color: edgeItem.color
    }
}

