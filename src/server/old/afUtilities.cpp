//------------------------------------------------------------------------------
// PEAR application facility Utility Classes								  --	
// (C) Sarah Zalusky 2010-2012, CERN											  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"pear_af_Utilities.cpp"
// [Author]			"Sarah Zalusky"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato, Sarah Zalusky"
// [Date]			"26 Jul 2012"
// [Language]		"C++"
//______________________________________________________________________________


// Application Components 
#include "pear_af_Utilities.h"
#include "pear_ac_Loop.h"

// The implemented GPs
#include "pear_gp_Scene.h"
#include "pear_gp_Virtual.h"
#include "pear_gp_Material.h"
#include "pear_gp_Frame.h"
#include "pear_gp_Point.h"
#include "pear_gp_Line.h"
#include "pear_gp_Polygon.h"
#include "pear_gp_Box.h"
#include "pear_gp_Sphere.h"
#include "pear_gp_Tube.h"
#include "pear_gp_Label.h"

// #############################################################################
namespace pear { namespace af {	namespace util {

//______________________________________________________________________________
void testSceneBoxes(unsigned int count)
{
	/*! Creates a scene filled with \c count arbitrary boxes. */	

	// Start a new scene.
	std::stringstream sName;
	sName << "Scene " << (time(NULL) % 3600);
	gp::Scene* scene = new gp::Scene;
	scene->Name(sName.str().c_str());
	
	// Test primitives.
	//scene->gp_Add(new gp::Point(), 0);
	//scene->gp_Add(new gp::Line(), 0);
	//scene->gp_Add(new gp::Polygon(), 0);
	//scene->gp_Add(new gp::Box(), 0);
	//scene->gp_Add(new gp::Sphere(1, 24, 24), 0);
	//scene->gp_Add(new gp::Tube(1,1.2,0.6,0.8,2,24,1), 0);
	//scene->gp_Add(new gp::Label("Pippo") , 0);

	// Dim ref boxes 
	scene->gp_Add(new gp::Sphere(1, 24, 24));
	scene->gp_Add(new gp::Box(5, 0, 0, 1, 1, 1));
	scene->gp_Add(new gp::Box(0, 5, 0, 1, 1, 1));
	scene->gp_Add(new gp::Box(5, 5, 0, 1, 1, 1));
	scene->gp_Add(new gp::Box(0, 0, 5, 1, 1, 1));
	scene->gp_Add(new gp::Box(5, 0, 5, 1, 1, 1));
	scene->gp_Add(new gp::Box(0, 5, 5, 1, 1, 1));
	scene->gp_Add(new gp::Box(5, 5, 5, 1, 1, 1));


	//scene->gp_Get(gp)->fill

	for (int i = 1; i <= scene->gp_Count(); i++) {
		GP* gp = scene->gp_Get(i);
		std::cout << "Stem: " << gp->Stem() 
				  << ", Size() =  " << gp->Size() 
				  << ", sizeof = " << sizeof(*gp) << "\n"; 

	}
	
	// Reference
	std::cout << "References:\n";
	std::cout << "GP:       " << sizeof (GP) << "\n";
	std::cout << "Stroked: " << sizeof (gp::Filled) << "\n";
	std::cout << "Filled:  " << sizeof (gp::Stroked) << "\n";
	std::cout << "Fonted:  " << sizeof (gp::Stroked) << "\n";
	std::cout << "Virtual: " << sizeof (gp::Virtual) << "\n";
	std::cout << "Frame:   " << sizeof (gp::Frame) << "\n";
	std::cout << "Point:   " << sizeof (gp::Point) << "\n";
	std::cout << "Line:    " << sizeof (gp::Line) << "\n";
	std::cout << "Polygon: " << sizeof (gp::Polygon) << "\n";	
	std::cout << "Box:     " << sizeof (gp::Box) << "\n";	
	std::cout << "Sphere:  " << sizeof (gp::Sphere) << "\n";
	std::cout << "Tube:    " << sizeof (gp::Tube) << "\n";
	std::cout << "Label:   " << sizeof (gp::Label) << "\n";
	
	/*
	gp::Point gp;
	std::cout << "sizeof GP size: " << sizeof(gp) << "\n";
	std::cout << "Default GP size: " << gp.Size() << "\n";
	std::cout << "My name is: " << gp.Name() << "\n";
	gp.Name("123");
	std::cout << "GP name = 123 size: " << gp.Size() << "\n";
	std::cout << "My name is: " << gp.Name() << "\n";
	gp.Name("1234567890123456789012345678901234567890");
	std::cout << "GP name = 1234 size: " << gp.Size() << "\n";
	std::cout << "My name is: " << gp.Name() << "\n";
	gp.Name("12");
	std::cout << "GP name = 12 size: " << gp.Size() << "\n";
	std::cout << "My name is: " << gp.Name() << "\n";
	gp.Info("Info!!!");
	std::cout << "My info is: [" << gp.Info() << "]\n";
	gp.Info("");
	std::cout << "My info is: [" << gp.Info() << "]\n";

	std::cout << "\nAllocates:\n";
	gp::Point gp2;
	std::cout << "gp1: " << &gp << "\n";
	std::cout << "gp2: " << &gp2 << "\n";
	*/
/*
	// Fills the scene
	int sideSize = 20;

	// Draws some boxes
	srand((unsigned int)clock());
	GPHnd parent, oldParent = 0;
	float pX, pY, pZ, sX, sY, sZ;
	float col[4];
	
	// Box generation loop.
	for (Uint32 i = 0; i < count; i++) {
		
		// Family building.
		if (rand() > 100)	{
		   	oldParent = parent;
			parent = (Uint32)floor(((double)rand() / 60000) * 1 * count);
			if (parent >= i) parent = oldParent;
		} else parent = 0;
		
		// Position, size and color.
		pX = (rand() % 20000 - 10000) / 500.0f;
		pY = (rand() % 20000 - 10000) / 500.0f;
		pZ = (rand() % 20000 - 10000) / 500.0f;
		sX = (rand() % 10000 - 5000) / 5000.0f;
		sY = (rand() % 10000 - 5000) / 5000.0f;
		sZ = (rand() % 10000 - 5000) / 5000.0f;
		col[0] = (rand() % 256) / 256.0f;
		col[1]  = (rand() % 256) / 256.0f;
		col[2]  = (rand() % 256) / 256.0f;
		col[3]  = (rand() % 201 + 55) / 256.0f;

		// Creates the GP.
		gp::Filled* gp = new gp::Box(pX, pY, pZ, sX, sY, sZ);
		//gp::Stroked* gp = new gp::Point(pX, pY, pZ, 3);
		//gp::Filled* gp = new gp::Box(pX, pY, pZ, sX, sY, sZ);
																
		// Sets GP specific properties.
		std::stringstream name;
		name << "Point # " << i;
		gp->Name(name.str().c_str());
		gp->Info("");

		// Appearance.
		gp->strkColor(col);
		//gp->strkWidth(2); 
		gp->strkEnable(true);
		gp->fillEnable(true);
		gp->fillColor(col);
		
		// Add the GP to the scene (this also build it).
		GPHnd gpHnd = scene->gp_Add(gp, parent);
	}
*/
	// Add the scene to the application main pad.
	pear::ac::_Loop->padGet()->scene_Add(scene);
}


// #############################################################################
}}} // Close namespaces