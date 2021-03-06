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
// This file is a part of the QuickGeoGL software. Copyright (C) 2016 Benoit Autheman.
//
// \file	qglSGConvexPolygonNode.h
// \author	benoit@destrat.io
// \date	2016 09 24
//-----------------------------------------------------------------------------

#ifndef qglSGConvexPolygonNode_h
#define qglSGConvexPolygonNode_h

// Std headers
#include <memory>

// Qt headers
#include <QSGGeometryNode>
#include <QSGMaterialShader>

// QuickGeoGL headers
// Nil

namespace qgl { // ::qgl

struct PolygonPoint {
    float x, y;
};

struct PolygonGadget {
    int                     pointCount = 0;
    QSGGeometry::Point2D*   points{nullptr};
};

class SGConvexPolygonNode : public QSGGeometryNode
{
    /*! \name SGConvexPolygonNode Scene Graph Interface *///-------------------
    //@{
public:
    /*! \brief Construct a SGConvexPolygonNode polyline with \c pointCount points an a given \c strokeMaterial material.
     *
     *  \note The internal PolLineGadget gadget points are left uninitialized.
     *  \param strokeMaterial material used to "stroke" the line, polyline node does not get the material ownership.
     */
    SGConvexPolygonNode() noexcept;
    virtual     ~SGConvexPolygonNode( ) { }
    SGConvexPolygonNode( const SGConvexPolygonNode& ) = delete;
    SGConvexPolygonNode& operator=(const SGConvexPolygonNode& ) = delete;

    auto        createGeometry( const QPolygonF& polygon ) noexcept -> void;
    auto        updateGeometry( const QPolygonF& polygon ) noexcept -> void;

    /*! \brief Every time you access the underlining polyline gadget, this node consider that you have modified it, internal geometry may be updated.
     *
     * \note Automatically call setDirty().
     */
    inline  auto    getGadget( ) noexcept -> PolygonGadget& { return _gadget; }
    inline  auto    getGadget( ) const noexcept -> const PolygonGadget& { return _gadget; }
protected:
    QSGGeometry*    _geometry{nullptr};
    QSGMaterial*    _material{nullptr};
    PolygonGadget   _gadget;
    //@}
    //-------------------------------------------------------------------------
};

} // ::qgl

#endif  // qglSGConvexPolygonNode.h

