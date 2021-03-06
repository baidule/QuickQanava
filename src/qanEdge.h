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
// This file is a part of the QuickQanava software library.
//
// \file	hedges.h
// \author	benoit@destrat.io
// \date	2004 February 15
//-----------------------------------------------------------------------------

#ifndef qanEdge_h
#define qanEdge_h

// Qt headers

// QuickQanava headers
#include "./qanGraphConfig.h"
#include "./qanStyle.h"
#include "./qanNode.h"

namespace qan { // ::qan

class Graph;
class EdgeItem;

//! Weighted directed edge linking two nodes in a graph.
/*!
    \nosubgrouping
 */
class Edge : public gtpo::GenEdge< qan::GraphConfig >
{
    /*! \name Edge Object Management *///--------------------------------------
    //@{
    Q_OBJECT
public:
    //! Edge constructor with source, destination and weight initialization.
    explicit Edge();
    Edge( const Edge& ) = delete;
    virtual ~Edge();

public:
    Q_PROPERTY( qan::Graph* graph READ getGraph CONSTANT FINAL )
    //! Shortcut to gtpo::GenEdge<>::getGraph().
    qan::Graph*         getGraph() noexcept;
    //! \copydoc getGraph()
    const qan::Graph*   getGraph() const noexcept;

public:
    friend class qan::EdgeItem;

    Q_PROPERTY( qan::EdgeItem* item READ getItem CONSTANT )
    qan::EdgeItem*   getItem() noexcept;
    void             setItem(qan::EdgeItem* edgeItem) noexcept;
private:
    QPointer<qan::EdgeItem> _item;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Edge Static Factories *///---------------------------------------
    //@{
public:
    /*! \brief Return the default delegate QML component that should be used to generate edge \c item.
     *
     *  \arg caller Use this for \c caller argument, since at component creation a valid QML engine is necessary.
     *  \return Default delegate component or nullptr (when nullptr is returned, QuickQanava default to Qan.Edge component).
     */
    static  QQmlComponent*      delegate(QObject* caller) noexcept;

    /*! \brief Return the default style that should be used with qan::Edge.
     *
     *  \return Default style or nullptr (when nullptr is returned, qan::StyleManager default edge style will be used).
     */
    static  qan::EdgeStyle*     style() noexcept;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Edge Topology Management *///------------------------------------
    //@{
public:
    Q_INVOKABLE qan::Node* getSource() noexcept;
    Q_INVOKABLE qan::Node* getDestination() noexcept;
    Q_INVOKABLE qan::Edge* getHDestination() noexcept;

    //! Read-only abstract item model of this edge in hyper nodes.
    Q_PROPERTY( QAbstractItemModel* inHNodes READ getInHNodesModel CONSTANT FINAL )
    QAbstractItemModel* getInHNodesModel() const;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Edge Properties Management *///----------------------------------
    //@{
public:
    Q_PROPERTY( QString label READ getLabel WRITE setLabel NOTIFY labelChanged FINAL )
    //! Set this edge label.
    void            setLabel( const QString& label );
    //! Get this edge label.
    const QString&  getLabel( ) const { return _label; }
protected:
    QString         _label{""};
signals:
    void            labelChanged( );

public:
    Q_PROPERTY( qreal weight READ getWeight WRITE setWeight NOTIFY weightChanged FINAL )
    //! Get edge's weight.
    inline qreal    getWeight( ) const { return _weight; }
    //! Set edge's weight.
    void            setWeight( qreal weight );
protected:
    qreal           _weight{1.0};
signals:
    void            weightChanged( );
    //@}
    //-------------------------------------------------------------------------
};

} // ::qan

QML_DECLARE_TYPE( qan::Edge )

#endif // qanEdge_h
