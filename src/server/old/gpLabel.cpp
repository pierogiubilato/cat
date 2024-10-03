//------------------------------------------------------------------------------
// CAT Label Graphic Primitive class										  --
// (C) Piero Giubilato, 2011-2024, Padova University						  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpLabel.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Components
#include "gpLabel.h"

// Include Main (to access the font facility).
#ifdef CAT_SERVER
	#include "acMain.h"
	#include "afFont.h"	
#endif


// #############################################################################
namespace cat { namespace gp {

// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
label::label()
{
	/*! Label ctor, automatic version. This is usually the one called by the
	 *	GP objects factory.
	 */
	
	// Reference position.
	_vtx[0].xyz(+0.0f, +0.0f, +0.0f);
	
	// (Eventual) containing quad.
	_vtx[1].xyz(-1.0f, -1.0f, +0.0f);
	_vtx[2].xyz(+1.0f, -1.0f, +0.0f);
	_vtx[3].xyz(+1.0f, +1.0f, +0.0f);
	_vtx[4].xyz(-1.0f, +1.0f, +0.0f);

	// The text.
	_text = "Empty";
	
	// Alignment and others.
	_alignment = GP::kAlign::null;
	_rotation = 0;
	_view2D = true;

	// The generated pixMap.
	#ifdef CAT_SERVER
		_pxmData = 0;
		_pxmWidth = 0;
		_pxmHeight = 0;
	#endif
}

//______________________________________________________________________________
label::label(const std::string& text, 
			 const double& x, const double& y, const double& z, 
			 const uint16_t& alignment, const double& rotation,
			 const bool& view2D)
{
	/*! Label constructor with text (\c text ), label position (\c x \c y ),
	 *	font name, size and face (\c fontName , \c fontSize , \c fontFace ). 
	 */
	
	// Reference position.
	_vtx[0].xyz(x, y, z);
	
	// (Eventual) containing quad.
	_vtx[1].xyz(x - 1.0f, y - 1.0f, z + 0.0f);
	_vtx[2].xyz(x + 1.0f, y - 1.0f, z + 0.0f);
	_vtx[3].xyz(x + 1.0f, y + 1.0f, z + 0.0f);
	_vtx[4].xyz(x - 1.0f, y + 1.0f, z + 0.0f);

	// The text.
	_text = text;
	
	// Alignment and others.
	_alignment = alignment;
	_rotation = static_cast<float>(rotation);
	_view2D = view2D;

	// The generated pixMap.
	#ifdef CAT_SERVER
		_pxmData = 0;
		_pxmWidth = 0;
		_pxmHeight = 0;
	#endif
}

//______________________________________________________________________________
label::~label()
{
	/*! Destructor	*/
	
	// The generated pixMap.
	#ifdef CAT_SERVER
		delete[] _pxmData;
	#endif	
} 
	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType label::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpLabel;
}

//______________________________________________________________________________
cat::coVer_t label::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string label::stem() const
{
	/*! Returns a string identification. */
	return "label";
}

//______________________________________________________________________________
size_t label::size(const bool& dynamic) const
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = stroked::size(true);
	#ifdef CAT_SERVER
		tSize += sizeof(*_pxmData)* _pxmWidth *_pxmHeight;	// Pixmap size.
	#endif
	
	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}
//______________________________________________________________________________
void label::dump(const int& ind) const
{
	/*! Send out all the GP data. */
	fonted::dump(ind);
	
	// Quick out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)

	// The label.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "Label ["
		<< "Text: " << CLW << _text << CD << ", "
		<< "Alignment: " << CLW << _alignment << CD << ", "
		<< "Rotation: " << CLW << _rotation << CD << ", "
		<< "View 2D: " << CLW << _view2D << CD << "]\n";

	// Display a map of the label if on SERVER side.
	#ifdef CAT_SERVER

		// Check if a map is available.
		if (!_pxmData) return;

		// Assign pivots.
		unsigned int max = 255;
		unsigned char symbol[7] = {250, 58, 176, 177, 178, 219, 232};	
		char brush = ' ';
		//std::cout << pad3 << "[" << COL(LWHITE) << "Map" << COL(DEFAULT) << "]\n";
		
		// Loop over all the data point of the pivot layer.
		for (auto r = 0; r < _pxmHeight; r++) {
			std::cout << pad3 << COL(BLACK + BG * WHITE);
			for (auto c = 0; c < _pxmWidth; c++) {
				auto p = _pxmData[((_pxmHeight - r - 1) * _pxmWidth + c) * 4 + 3];
				p ? brush = (symbol[(unsigned int)((float)p / max * 5)]) : brush = ' ';
				std::cout << brush;
			}
			std::cout << COL(DEFAULT + BG * BLACK) << "\n";
		}
				
	// Server side IF.
	#endif

	// Clear definitions.
	#undef CLW
	#undef CD
}

//______________________________________________________________________________
bool label::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	GP::stream(o, read);
		
	// Streams the vertexes
	for (auto i = 0; i < 5; i++) _vtx[i].stream(o, read);
	
	// Read/Write from/to stream.
	af::stream::rw(o, _text, read);
	af::stream::rw(o, _alignment, read);
	af::stream::rw(o, _rotation, read);   
	af::stream::rw(o, _view2D, read);

	// Everything fine.
	return false;
}

//______________________________________________________________________________
label& label::trsf(const ge::ref& rf, const bool& inv)
{
	/*! Transforms the box coordinates applying the rf transformation directly
	 *	if inv = false, and by applying the inverse transformation if inv = true. 
	 */
	for (auto i = 0; i < 5; i++) rf.trsf(_vtx[i], inv);
	return *this;
}	

// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
ge::point label::vtx(const int& idx) const
{
	/*! Returns the Idx th vertex of the box. Returns a (0,0,0) vertex in case
	 *	of OOB call. 
	 */
	if (idx < 5) return _vtx[idx];
	else return ge::point(0, 0, 0);
}


// *****************************************************************************
// **							     SERVER SIDE							  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER


// *****************************************************************************
// **							     gl Functions							  **
// *****************************************************************************

//______________________________________________________________________________
double label::glAlpha()
{
	/*! Overloaded from GP. As a label is actually a pixmap, it is always a 
	 *	item, so fix this output to true.
	 */
	return 0;
}

//______________________________________________________________________________
void label::glDrawSel()
{
	/*!	Draws a label selection skeleton. */
		
	// Common drawing properties are handled by the parent.
	stroked::glDrawSel(); 

	// Need to think a bit about this... probably a 2D square around 
	// the label should work.
}

//______________________________________________________________________________
void label::glDraw()
{
	/*!	Draws a label object. */
		
	// Common drawing properties are handled by the parent.
	stroked::glDraw(); 

	// If not visible, bye bye.
	if (!modeVisible()) return;
		
	// Get a string for the text, and a pointer to an array of color.
	std::string text = _text;	// The string with all control sequences.
	std::vector<uint32_t> color;	// The array containing the char color.
	
	// Get the starting color for the text.
	uint32_t defaultCol = 0;
	defaultCol = ((uint32_t)(_strkColor[0] * 255)) << 24;		// Red.
	defaultCol += ((uint32_t)(_strkColor[1] * 255)) << 16;	// Green.
	defaultCol += ((uint32_t)(_strkColor[2] * 255)) << 8;		// Blue.
	defaultCol += ((uint32_t)(_strkColor[3] * 255)) << 0;		// Alpha.

	// Analyze label text to search for special control sequences ('//' style),
	// Assigning the per-character color array.	
	cat::af::_font->textParse(text, color, defaultCol);

	// Prepares the text pixmap. The text routines sets the size for the map.
	cat::af::_font->textFont(_fontFamily, _fontStyle, _fontSize, _rotation);  
	cat::af::_font->textDraw(text, color, _pxmWidth, _pxmHeight, _pxmData);  

	// Stroke outline.
	if (_strkEnable) {
			
		// Set data alignment at 64 bit.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
		
		// Set label position, 2D style respect the center.
		if (_view2D) {
//			glRasterPos3f(0, 0, 0);
//			glBitmap(0, 0, 0, 0, _vtx[0].X(), _vtx[0].Y(), NULL); 
			
		// Set label position, 3D derived from the anchor point.
		} else {
//			glRasterPos3f(_vtx[0].X(), _vtx[0].Y(), _vtx[0].Z());
		}

		// Adds the offset to correctly align the label to the anchor point.
		cat::gp::GPDim dim;
		dim.x = (float)_pxmWidth;
		dim.y = (float)_pxmHeight;
		GPPos off = offset(dim, _alignment);
//		glBitmap(0, 0, 0, 0, off.x, -off.y, NULL); 

		// Actually draw the label pixmap.
//		glDrawPixels(_pxmWidth, _pxmHeight, GL_RGBA, GL_UNSIGNED_BYTE, _pxmData);
	}
}

//______________________________________________________________________________
void label::glDrawEnd()
{
	// Complete drawing operations.
	stroked::glDrawEnd(); 
}


// *****************************************************************************
// **							   ui Functions								  **
// *****************************************************************************

////______________________________________________________________________________
//void TW_CALL label::uiTextSet(const void *value, void *clientData)
//{ 
//    /*! Set the _text value in a TWBar compatible way. It uses the Dynamic string
//	 *	AntTweakBar call as at the moment it seems that the stl::string one
//	 *	implementation does not works properly.
//	 */
//	//static_cast<Label*>(clientData)->Text() = std::string(*(const char**)value);	
//}
//			
////______________________________________________________________________________
//void TW_CALL Label::uiTextGet(void *value, void *clientData)
//{ 
//    /*! Put the _Text value in a TWBar compaible way. It uses the Dynamic string
//	 *	AntTweakBar call as at the moment it seems that the stl::string one
//	 *	implementation does not works properly.
//	 */
//	//TwCopyCDStringToLibrary(static_cast<char**>(value), static_cast<Label*>(clientData)->Text().c_str());
//}
//
////______________________________________________________________________________
//TwType Label::uiTwEnumTxAlign() const
//{ 
//    /*! Creates a TwType containing the available text alignments. */
///*
//	const TwEnumVal twEnum[] = {
//		{kal_Default, "Default"}, 
//		{kal_Hor_Left + kal_Ver_Top, "Left, Top"},			// Left, Top. 
//		{kal_Hor_Mid + kal_Ver_Top, "Center, Top"},			// Mid, Top.
//		{kal_Hor_Right + kal_Ver_Top, "Right, Top"},		// Right, Top.
//		{kal_Hor_Left + kal_Ver_Mid, "Left, Center"},		// Left, Mid. 
//		{kal_Hor_Mid + kal_Ver_Mid, "Center, Center"},		// Mid, Mid.
//		{kal_Hor_Right + kal_Ver_Mid, "Right, Center"},		// Right, Mid.
//		{kal_Hor_Left + kal_Ver_Bottom, "Left, Bottom"},	// Left, Bottom. 
//		{kal_Hor_Mid + kal_Ver_Bottom, "Center, Bottom"},	// Mid, Bottom.
//		{kal_Hor_Right + kal_Ver_Bottom, "Right, Bottom"}	// Right, Bottom.
//    };
//	return TwDefineEnum("ViewMode", twEnum, SDL_arraysize(twEnum));
//*/
//}
//
////______________________________________________________________________________
//void Label::uiBarLoad(ui::Bar& bar)
//{
//	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
//	 *	the GP. This member should be overloaded to change/add the properties
//	 *	shown on the properties bar by every GP.
//	 */
///*
//	// The parent first!
//	Fonted::uiBarLoad(bar); 
//
//	// Add the specific properties 
//	TwBar* twBar = bar._TwBar; 
//
//	// Label text.
//	bar.GroupAdd("Text");
//	TwAddVarCB(twBar, "txText", TW_TYPE_CDSTRING, Label::uiTextSet, Label::uiTextGet, this, "label='Text' group='Text'");
//	
//	// Alignment.
//	bar.GroupAdd("Alignment");
//	TwAddVarRW(twBar, "alRotation", TW_TYPE_FLOAT, &_Rotation, "label='Rotation' group='Alignment' min=0.00 max=6.28 step=0.01");	
//	TwAddVarRW(twBar, "alAlignment", uiTwEnumTxAlign(), &_Alignment, "label='Alignment' group='Alignment'");
//	TwAddVarRW(twBar, "al2DView", TW_TYPE_BOOLCPP, &_View2D, "label='Force 2D' group='Alignment'");	
// */
// }

// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace