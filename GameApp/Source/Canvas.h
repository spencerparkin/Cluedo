#pragma once

#include "BoardGraph.h"
#include <wx/glcanvas.h>

class Canvas : public wxGLCanvas
{
public:
	Canvas(wxWindow* parent);
	virtual ~Canvas();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

private:

	void RenderBoardNodeQuad(const Cluedo::BoardGraph::Node* node);
	void RenderBoardNodeBorder(const Cluedo::BoardGraph::Node* node);
	void RenderOccupantIfAny(const Cluedo::BoardGraph::Node* node);

	wxGLContext* renderContext;
};