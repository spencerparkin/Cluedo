#include "Canvas.h"
#include "Application.h"
#include <gl/GLU.h>

static int attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };

Canvas::Canvas(wxWindow* parent) : wxGLCanvas(parent, wxID_ANY, attributeList, wxDefaultPosition, wxDefaultSize)
{
	this->renderContext = new wxGLContext(this);

	this->Bind(wxEVT_PAINT, &Canvas::OnPaint, this);
	this->Bind(wxEVT_SIZE, &Canvas::OnSize, this);
}

/*virtual*/ Canvas::~Canvas()
{
	delete this->renderContext;
}

void Canvas::OnPaint(wxPaintEvent& event)
{
	this->SetCurrent(*this->renderContext);

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	double aspectRatio = float(viewport[2]) / float(viewport[3]);

	Cluedo::BoardGraph* boardGraph = wxGetApp().GetBoardGraph();
	Cluedo::Box2D worldBox = boardGraph->GetBoundingBox();
	worldBox.AddMargin(1.0);
	worldBox.MinimallyExpandToMatchAspectRatio(aspectRatio);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(worldBox.minCorner.x, worldBox.maxCorner.x, worldBox.minCorner.y, worldBox.maxCorner.y);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);

	boardGraph->ForAllNodes([this](const Cluedo::BoardGraph::Node* node) -> bool
		{
			this->RenderBoardNodeQuad(node);
			return true;
		});

	glColor3f(0.0f, 0.0f, 0.0f);

	boardGraph->ForAllNodes([this](const Cluedo::BoardGraph::Node* node) -> bool
		{
			this->RenderBoardNodeBorder(node);
			return true;
		});

	glEnd();

	boardGraph->ForAllNodes([this](const Cluedo::BoardGraph::Node* node) -> bool
		{
			this->RenderOccupantIfAny(node);
			return true;
		});

	glFlush();

	this->SwapBuffers();
}

void Canvas::RenderBoardNodeQuad(const Cluedo::BoardGraph::Node* node)
{
	const Cluedo::Vector2D& location = node->GetLocation();

	if (node->GetZone() == Cluedo::Zone::Unused)
		return;
	else if(node->GetZone() == Cluedo::Zone::Hallway)
	{
		if (int(location.x + location.y) % 2 == 0)
			glColor3f(1.0f, 1.0f, 1.0f);
		else
			glColor3f(0.5f, 0.5f, 0.5f);
	}
	else if (node->IsRoom())
	{
		glColor3f(0.4f, 0.6f, 0.8f);
	}

	glVertex2d(location.x - 0.5, location.y - 0.5);
	glVertex2d(location.x + 0.5, location.y - 0.5);
	glVertex2d(location.x + 0.5, location.y + 0.5);
	glVertex2d(location.x - 0.5, location.y + 0.5);
}

void Canvas::RenderBoardNodeBorder(const Cluedo::BoardGraph::Node* node)
{
	std::vector<const Cluedo::BoardGraph::Node*> adjacentNodeArray;
	node->GetAdjacencies(adjacentNodeArray);

	for (auto* adjacentNode : adjacentNodeArray)
	{
		if (node->IsPathway(adjacentNode))
			continue;
		
		Cluedo::Vector2D point = (node->GetLocation() + adjacentNode->GetLocation()) / 2.0;
		Cluedo::Vector2D minorAxis = point - node->GetLocation();
		Cluedo::Vector2D majorAxis = minorAxis.RotatedCCW90();
		Cluedo::Vector2D endPointA = point + majorAxis;
		Cluedo::Vector2D endPointB = point - majorAxis;
		Cluedo::Vector2D thicknessVector = minorAxis.Normalized() * 0.05;
		Cluedo::Vector2D vertexA = endPointA - thicknessVector;
		Cluedo::Vector2D vertexB = endPointB - thicknessVector;
		Cluedo::Vector2D vertexC = endPointB + thicknessVector;
		Cluedo::Vector2D vertexD = endPointA + thicknessVector;

		glVertex2d(vertexA.x, vertexA.y);
		glVertex2d(vertexB.x, vertexB.y);
		glVertex2d(vertexC.x, vertexC.y);
		glVertex2d(vertexD.x, vertexD.y);
	}
}

void Canvas::RenderOccupantIfAny(const Cluedo::BoardGraph::Node* node)
{
	const Cluedo::BoardGraph::Token* token = node->GetOccupant();
	if (!token)
		return;

	// Calculate vertices.
	const Cluedo::Vector2D& location = token->GetLocation();
	double radius = 0.45;
	const int numSegments = 32;
	std::vector<Cluedo::Vector2D> vertexArray;
	for (int i = 0; i < numSegments; i++)
	{
		Cluedo::Vector2D delta;
		delta.Compose(radius, (2.0 * M_PI) * double(i) / double(numSegments));
		Cluedo::Vector2D vertex = location + delta;
		vertexArray.push_back(vertex);
	}

	// Draw the circle.
	glBegin(GL_TRIANGLE_FAN);
	double r = 0.0, g = 0.0, b = 0.0;
	token->GetColor(r, g, b);
	glColor3d(r, g, b);
	glVertex2d(location.x, location.y);
	for (int i = 0; i <= numSegments; i++)
	{
		const Cluedo::Vector2D& vertex = vertexArray[i % numSegments];
		glVertex2d(vertex.x, vertex.y);
	}
	glEnd();

	// Draw the border.
	glBegin(GL_LINE_LOOP);
	glColor3d(0.0, 0.0, 0.0);
	for (int i = 0; i < numSegments; i++)
	{
		const Cluedo::Vector2D& vertex = vertexArray[i];
		glVertex2d(vertex.x, vertex.y);
	}
	glEnd();
}

void Canvas::OnSize(wxSizeEvent& event)
{
	this->SetCurrent(*this->renderContext);

	wxSize size = event.GetSize();
	glViewport(0, 0, size.GetWidth(), size.GetHeight());

	this->Refresh();
}