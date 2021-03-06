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
// \file	qglSGLineAAMaterial.cpp
// \author	benoit@destrat.io
// \date	2016 10 01
//-----------------------------------------------------------------------------

// Qt headers
#include <QtGlobal>
#include <QOpenGLFunctions>
#include <QSGEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

// QuickGeoGL headers
#include "./qglSGLineAAMaterial.h"

namespace qgl { // ::qgl

QSGMaterialType SGLineAAMaterial::_type;

SGLineAAShader::SGLineAAShader( ) :
    QSGMaterialShader{}
{
    setShaderSourceFile( QOpenGLShader::Vertex, ":/QuickGeoGL/qglLineAAVsh.glsl" );
#if (QT_VERSION >= QT_VERSION_CHECK(5, 9, 0))
    program()->addCacheableShaderFromSourceFile(QOpenGLShader::Geometry, ":/QuickGeoGL/qglLineAAGsh.glsl");
#else
    program()->addShaderFromSourceFile(QOpenGLShader::Geometry, ":/QuickGeoGL/qglLineAAGsh.glsl");
#endif
    setShaderSourceFile( QOpenGLShader::Fragment, ":/QuickGeoGL/qglLineAAFsh.glsl");
}

void	SGLineAAShader::updateState(const RenderState & state, QSGMaterial* newMaterial, QSGMaterial* oldMaterial )
{
    QSGMaterialShader::updateState( state, newMaterial, oldMaterial );
    if ( program() == nullptr ||
         !program()->isLinked( ) ) {
        qWarning() << "qgl::SGLineAAShader::updateState(): Error: Material shader is not linked.";
        return;
    }
    if ( state.isMatrixDirty( ) ) {
        program()->setUniformValue( _combMatrixId, state.combinedMatrix( ) );
        program()->setUniformValue( _mvMatrixId, state.modelViewMatrix( ) );
    }
    if ( state.isOpacityDirty( ) )
        program()->setUniformValue( _opacityId, state.opacity( ) );

    auto m = static_cast< SGLineAAMaterial* >( newMaterial );
    if ( m != nullptr ) {
        program()->setUniformValue( _colorId, m->getColor( ) );
        program()->setUniformValue( _widthId, ( GLfloat )m->getWidth( ) );
    }
}

void SGLineAAShader::initialize( )
{
    if ( program() == nullptr ||
         !program()->isLinked( ) ) {
        qWarning() << "qgl::SGLineAAShader::initialize(): Error: Material shader is not linked.";
        return;
    }
    _combMatrixId = program()->uniformLocation( "combmatrix" );
    _mvMatrixId = program()->uniformLocation( "mvmatrix" );
    _opacityId = program()->uniformLocation( "opacity" );
    _colorId = program()->uniformLocation( "color" );
    _widthId = program()->uniformLocation( "width" );
}
//-----------------------------------------------------------------------------

} // ::qgl
