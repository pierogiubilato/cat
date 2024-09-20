//------------------------------------------------------------------------------
// CAT User Interface Pad OpenGL support class								  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiPadGL.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Application components
#include "uiPadGL.h"


// #############################################################################
namespace cat { namespace ui {



// *****************************************************************************
// **							  Static Members							  **
// *****************************************************************************

pad* padGL::_owner = 0;	    // The static reference to the Pad owning the GL.



// *****************************************************************************
// **							  Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
padGL::padGL(pad* owner)
{
	/*! Creates a pad GL, a minimal library to use the current OpenGL context
	 *	as a traditional raster viewport.	
	 */
		
	// Set up the parent
	oOwner = owner;

}

//______________________________________________________________________________
padGL::~padGL() 
{
	/*! Releases all allocated resources. */

}


// *****************************************************************************
// **								Public Members							  **
// *****************************************************************************

//______________________________________________________________________________
void padGL::glSet()
{
	/*! Sets the OpenGL context to simulate a drawing viewport.	
	 */
		
    // Store bit-planes attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

	// Stores the matrixes.
	glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    

	GLint Vp[4];
    glGetIntegerv(GL_VIEWPORT, Vp);
    //if(Width > 0 && Height > 0 )
    //{
    //    Vp[0] = 0;
    //    Vp[1] = 0;
    //    Vp[2] = Width - 1;
    //    Vp[3] = Height - 1;
    //    glViewport(Vp[0], Vp[1], Vp[2], Vp[3]);
    //}
    glLoadIdentity();
    glOrtho(Vp[0], Vp[0] + Vp[2], Vp[1]+Vp[3], Vp[1], -1, 1);
    //glGetIntegerv(GL_VIEWPORT, m_ViewportInit);
    //glGetFloatv(GL_PROJECTION_MATRIX, m_ProjMatrixInit);

    //glGetFloatv(GL_LINE_WIDTH, &m_PrevLineWidth);
    glDisable(GL_POLYGON_STIPPLE);
    glLineWidth(1);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	//glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &m_PrevTexEnv);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glGetIntegerv(GL_POLYGON_MODE, m_PrevPolygonMode);
    
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_FOG);
    glDisable(GL_LOGIC_OP);
    glDisable(GL_SCISSOR_TEST);
    
}

//______________________________________________________________________________
void padGL::glReset()
{
	/*! Resets the OpenGL context to simulate a drawing viewport.	
	 */
	
	// Retrieves the matrixes.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	
	// Retrieve bit-planes attributes.
	glPopClientAttrib();
	glPopAttrib();

	/*
	glBindTexture(GL_TEXTURE_2D, m_PrevTexture);
    if( glBindBufferARB!=NULL )
    {
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_PrevArrayBufferARB);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_PrevElementArrayBufferARB);
    }
    if( _glBindProgramARB!=NULL )
    {
        if( m_PrevVertexProgramARB )
            _glEnable(GL_VERTEX_PROGRAM_ARB);
        if( m_PrevFragmentProgramARB )
            _glEnable(GL_FRAGMENT_PROGRAM_ARB);
    }
    if( _glGetHandleARB!=NULL && _glUseProgramObjectARB!=NULL )
        _glUseProgramObjectARB(m_PrevProgramObjectARB);
    if( _glTexImage3D!=NULL && m_PrevTexture3D )
        _glEnable(GL_TEXTURE_3D);
    if( m_SupportTexRect && m_PrevTexRectARB )
        _glEnable(GL_TEXTURE_RECTANGLE_ARB);
    if( _glBlendEquation!=NULL )
        _glBlendEquation(m_PrevBlendEquation);
    if( _glBlendEquationSeparate!=NULL )
        _glBlendEquationSeparate(m_PrevBlendEquationRGB, m_PrevBlendEquationAlpha);
    if( _glBlendFuncSeparate!=NULL )
        _glBlendFuncSeparate(m_PrevBlendSrcRGB, m_PrevBlendDstRGB, m_PrevBlendSrcAlpha, m_PrevBlendDstAlpha);
    
    _glPolygonMode(GL_FRONT, m_PrevPolygonMode[0]);
    _glPolygonMode(GL_BACK, m_PrevPolygonMode[1]);
    _glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, m_PrevTexEnv);
    _glLineWidth(m_PrevLineWidth);
    _glMatrixMode(GL_PROJECTION);
    _glPopMatrix();
    _glMatrixMode(GL_MODELVIEW);
    _glPopMatrix();
    _glMatrixMode(GL_TEXTURE);
    _glPopMatrix();
    _glPopClientAttrib();
    _glPopAttrib();

    if( _glActiveTextureARB )
    {
        int maxTexUnits = 1;
        _glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTexUnits);
        maxTexUnits = max(1, min(32, maxTexUnits));
        for( int i=0; i<maxTexUnits; ++i )
        {
            _glActiveTextureARB(GL_TEXTURE0_ARB+i);
            if( m_PrevActiveTexture1D[i] )
                _glEnable(GL_TEXTURE_1D);
            if( m_PrevActiveTexture2D[i] )
                _glEnable(GL_TEXTURE_2D);
            if( m_PrevActiveTexture3D[i] )
                _glEnable(GL_TEXTURE_3D);
        }
        _glActiveTextureARB(m_PrevActiveTextureARB);
    }
	*/
}

//______________________________________________________________________________
void padGL::glLine(const int& x1, const int& y1, const int& x2, const int& y2,
					const Uint32& col1, const Uint32& col2, const bool& alias)
{
	/*! Draws a line. */
	const GLfloat dx = +0.5f;
    const GLfloat dy = -0.5f;
    
	// Anti aliasing On/Off
	(alias) ? glEnable(GL_LINE_SMOOTH): glDisable(GL_LINE_SMOOTH);
    
	// set the gl.
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Line appearance.
	glDisable(GL_POLYGON_STIPPLE);
    glLineWidth(1);
    
	// Draw the line.
	glBegin(GL_LINES);
		glColor4ub(GLubyte(col1 >> 16), GLubyte(col1 >> 8), GLubyte(col1), GLubyte(col1 >> 24));
		glVertex2f((GLfloat)x1 + dx, (GLfloat)y1 + dy);
		glColor4ub(GLubyte(col2 >> 16), GLubyte(col2 >> 8), GLubyte(col2), GLubyte(col2 >> 24));
		glVertex2f((GLfloat)x2 + dx, (GLfloat)y2 + dy);
	glEnd();
	
	// Reset smoothing.
	glDisable(GL_LINE_SMOOTH);
}


// *****************************************************************************
// **							User interface update						  **
// *****************************************************************************

// *****************************************************************************
// **							User interface events						  **
// *****************************************************************************

// *****************************************************************************
// **							 Static Callbacks							  **
// *****************************************************************************


// *****************************************************************************
// **						  Private drawing members						  **
// *****************************************************************************


// #############################################################################
}} // Close namespaces
