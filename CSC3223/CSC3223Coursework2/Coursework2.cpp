#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;

RenderObject* shrink(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1) };

	for (int i = 0; i < 154; i++) {
		colours.push_back(Vector4(1, 1, 1, 1));
	}
	
	OGLShader* scale = new OGLShader("scaleShader.glsl","");

	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	m->SetVertexColours(colours);
	m->UploadToGPU();
	
	RenderObject* object = new RenderObject(m);

	object->SetShader(scale);

	TextureBase* tex = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->AddRenderObject(object);

	return object;
}

RenderObject* mixTexture(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1) };

	for (int i = 0; i < 154; i++) {
		colours.push_back(Vector4(1, 1, 1, 1));
	}
	OGLShader* mix = new OGLShader("coursework2VertexFocus.glsl", "mixTextures.glsl");

	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	m->SetVertexColours(colours);
	m->UploadToGPU();

	RenderObject* object = new RenderObject(m);

	object->SetShader(mix);
	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("brick.png"));
	object->SetSecondTexture(OGLTexture::RGBATextureFromFilename("perlin_noise.png"));

	renderer->AddRenderObject(object);

	return object;

}
RenderObject* transparency(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1) };

	for (int i = 0; i < 154; i++) {
		colours.push_back(Vector4(1, 1, 1, 1));
	}
	OGLShader* transparent = new OGLShader("coursework2VertexFocus.glsl", "transparencyFrag.glsl");

	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	m->SetVertexColours(colours);
	m->UploadToGPU();

	RenderObject* object = new RenderObject(m);

	object->SetShader(transparent);
	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("brick.png"));

	renderer->AddRenderObject(object);

	return object;
}
RenderObject* geometry(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1) };

	for (int i = 0; i < 154; i++) {
		colours.push_back(Vector4(1, 1, 1, 1));
	}

	OGLShader* geometry = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "GeomShader.glsl");

	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	m->SetVertexColours(colours);
	m->UploadToGPU();

	RenderObject* object = new RenderObject(m);

	object->SetShader(geometry);
	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("brick.png"));

	renderer->AddRenderObject(object);



	return object;

}

RenderObject* tessilation(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1) };

	for (int i = 0; i < 154; i++) {
		colours.push_back(Vector4(1, 1, 1, 1));
	}

	OGLShader* tess = new OGLShader("tessVert.glsl", "displaceFrag.glsl", "", "displaceTCS.glsl", "displaceTES.glsl");

	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Patches);
	m->SetVertexColours(colours);
	m->UploadToGPU();


	RenderObject* object = new RenderObject(m);

	object->SetShader(tess);
	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("brick.png"));

	renderer->AddRenderObject(object);



	return object;
}
RenderObject* test(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1) };

	for (int i = 0; i < 154; i++) {
		colours.push_back(Vector4(1, 1, 1, 1));
	}
	OGLShader* testing = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "normGeomShader.glsl");
	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	m->SetVertexColours(colours);
	m->UploadToGPU();


	RenderObject* object = new RenderObject(m);
	object->SetShader(testing);
	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("brick.png"));

	renderer->AddRenderObject(object);



	return object;
}
RenderObject* Coursework2(Renderer* renderer) {
	std::vector <Vector4> colours = {
	Vector4(1,1 ,1 ,1)};

	for (int i = 0; i < 154; i++) {
		 colours.push_back(Vector4(1, 1,1, 1));
	}
	
	OGLMesh* m = new OGLMesh("cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	m->SetVertexColours(colours);
	m->UploadToGPU();
	

	RenderObject* object = new RenderObject(m);

	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("brick.png"));
	
	renderer->AddRenderObject(object);



	return object;
}

int main() {
	Window* w = Window::CreateGameWindow("CSC3223 Coursework 2!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

	RenderObject* cube = Coursework2(renderer);

	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

	Vector3 viewPosition(0, 0, 0);
	float rotation = 0.0f;


	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();
		rotation += time * 30;
		renderer->Update(time);

		renderer->EnableDepthBuffer(true);		renderer->EnableBlending(true);
		renderer->SetBlendToLinear();
		

		Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -4));

		modelMat = modelMat * Matrix4::Rotation(rotation, Vector3(1, 1, 1));

		cube->SetTransform(modelMat);

		renderer->DrawString("Bradley Ford's Coursework 2!", Vector2(10, 10));
		renderer->DrawString("Press keys F1-F7 to see shaders", Vector2(10, 30));

		renderer->Render();

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewPosition.x += 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition.x -= 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
			viewPosition.y -= 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			viewPosition.y += 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.z += 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.z -= 1.0f;

		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime(); //resets time to apply new shader
			cube = Coursework2(renderer);
			
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F2)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime();
			cube = shrink(renderer);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F3)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime();
			cube = mixTexture(renderer);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F4)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime();
			cube = transparency(renderer);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime();
			cube = geometry(renderer);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime();
			cube = tessilation(renderer);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) {
			renderer->DeleteAllRenderObjects();
			renderer->resetTime();
			cube = test(renderer);
		}
		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}