#include "Renderer.h"
#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3223;

Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader = new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

Renderer::~Renderer()
{
	delete defaultShader;
}

void Renderer::RenderFrame() {
	OGLShader* activeShader = nullptr;

	int modelLocation = 0;

	for (const RenderObject* object : renderObjects) {
		OGLShader* objectShader = (OGLShader*)object->GetShader();
		if (!object->GetMesh()) {
			continue;
		}
		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}
		if (objectShader != activeShader) {
			activeShader = objectShader;
			BindShader(activeShader);
			int projLocation = glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
			int viewLocation = glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
			modelLocation = glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");

			glUniformMatrix4fv(projLocation, 1, false, (float*)& projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)& viewMatrix);
			ApplyLightToShader(activeLight, activeShader);

			Matrix3 rotation = Matrix3(viewMatrix);
			Vector3 invCamPos = viewMatrix.GetPositionVector();

			Vector3 camPos = rotation * -invCamPos; // invert the
			glUniform3fv(glGetUniformLocation(activeShader->GetProgramID(), "cameraPos"), 1, (float*)& camPos);
		}

		Matrix4 mat = object->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)& mat);

		BindTextureToShader(object->GetBaseTexture(), "mainTex", 0);
		BindTextureToShader(object->GetSecondTexture(), "secondTex", 1);
		BindMesh(object->GetMesh());
		DrawBoundMesh();

		int timeLocation =
			glGetUniformLocation(activeShader->GetProgramID(), "time");

		if (timeLocation >= 0) {

			float totalTime = frameTimer.GetTotalTime() - timeReset; // added -timeReset to reset time every time I want to apply a new shader to the cube
			glUniform1f(timeLocation, totalTime);
		}
	}
}

void Renderer::OnWindowResize(int w, int h) {
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}
void Renderer::EnableBilinearFiltering(OGLTexture& t) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}void Renderer::EnableMipMapFiltering(OGLTexture& t) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}
void Renderer::EnableTextureRepeating(
	OGLTexture& t, bool uRepeat, bool vRepeat) {
	GLuint id = t.GetObjectID();

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uRepeat ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vRepeat ? GL_REPEAT : GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);}void Renderer::SetBlendToLinear() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}void Renderer::SetBlendToAdditive() {
	glBlendFunc(GL_ONE, GL_ONE);

}
void Renderer::SetBlendToInvert() {
	glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);}void Renderer::SetLightProperties(Vector3 position, Vector3 colour, float radius) {
	activeLight.position = position;
	activeLight.colour = colour;
	activeLight.radius = radius;}void Renderer::ApplyLightToShader(const Light& l, const OGLShader* s) {
	glUniform3fv(glGetUniformLocation(
		s->GetProgramID(), "lightColour"), 1, (float*)& l.colour);
	glUniform3fv(glGetUniformLocation(
		s->GetProgramID(), "lightPos"), 1, (float*)& l.position);
	glUniform1f(glGetUniformLocation(
		s->GetProgramID(), "lightRadius"), l.radius);}