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

	void RenderBoardNodeQuad(const BoardGraph::Node* node);
	void RenderBoardNodeBorder(const BoardGraph::Node* node);
	void RenderToken(const BoardGraph::Token* token);

	wxGLContext* renderContext;
};