////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	earthModel = 0;
	sunModel = 0;
	moonModel = 0;
	mercuryModel = 0;
	venusModel = 0;
	marsModel = 0;
	jupiterModel = 0;
	saturnModel = 0;
	uranusModel = 0;
	neptuneModel = 0;
	rocketModel = 0;
	saturnRing = 0;
	
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 5.0f, -100.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 30.0f, -100.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.

	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 90.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(100.0f);

	// Create the earth object.

	earthModel = new ModelClass;
	if(!earthModel)
	{
		return false;
	}

	// Initialize the earth object.

	result = earthModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/earthtexture.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the earth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the sun model object.

	sunModel = new ModelClass;
	if(!sunModel)
	{
		return false;
	}

	// Initialize the sun model object.

	result = sunModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/suntexture.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sun model object.", L"Error", MB_OK);
		return false;
	}

	// Create the moon object

	moonModel = new BumpModelClass;
	if(!moonModel)
	{
		return false;
	}

	// Initialize the moon model object.

	result = moonModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/moontexture.dds",
								  L"../Engine/data/moontexture.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the moon model object.", L"Error", MB_OK);
		return false;
	}

	// Create the rocket model object.

	rocketModel = new ModelClass;
	if (!rocketModel)
	{
		return false;
	}

	// Initialize the rocket object.

	result = rocketModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Ship.txt", L"../Engine/data/ShipTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the rocket model object.", L"Error", MB_OK);
		return false;
	}

	// Create the mercury model object.

	mercuryModel = new ModelClass;
	if (!mercuryModel)
	{
		return false;
	}

	// Initialize the mercury object.


	result = mercuryModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/mercurytexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mercury model object.", L"Error", MB_OK);
		return false;
	}

	// Create the venus model object.

	venusModel = new ModelClass;
	if (!venusModel)
	{
		return false;
	}

	// Initialize the venus object.

	result = venusModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/venustexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the venus model object.", L"Error", MB_OK);
		return false;
	}
	// Create the mars model object.

	marsModel = new ModelClass;
	if (!marsModel)
	{
		return false;
	}

	// Initialize the mars object.

	result = marsModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/marstexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mars model object.", L"Error", MB_OK);
		return false;
	}

	// Create the jupiter model object.

	jupiterModel = new ModelClass;
	if (!jupiterModel)
	{
		return false;
	}

	// Initialize the jupiter object.

	result = jupiterModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/jupitertexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the jupiter model object.", L"Error", MB_OK);
		return false;
	}

	// Create the saturn model object.

	saturnModel = new ModelClass;
	if (!saturnModel)
	{
		return false;
	}

	// Initialize the saturn object.

	result = saturnModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/saturntexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the saturn model object.", L"Error", MB_OK);
		return false;
	}

	// Create the uranus model object.

	uranusModel = new ModelClass;
	if (!uranusModel)
	{
		return false;
	}

	// Initialize the uranus object.

	result = uranusModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/uranustexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the uranus model object.", L"Error", MB_OK);
		return false;
	}

	// Create the neptune model object.

	neptuneModel = new ModelClass;
	if (!neptuneModel)
	{
		return false;
	}

	// Initialize the neptune object.

	result = neptuneModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/neptunetexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the neptune model object.", L"Error", MB_OK);
		return false;
	}

	// Create the rocket model object.

	saturnRing = new ModelClass;
	if (!saturnRing)
	{
		return false;
	}

	// Initialize the rocket object.

	result = saturnRing->Initialize(m_D3D->GetDevice(), "../Engine/data/Ring.txt", L"../Engine/data/saturntexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the rocket model object.", L"Error", MB_OK);
		return false;
	}
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if(earthModel)
	{
		earthModel->Shutdown();
		delete earthModel;
		earthModel = 0;
	}

	if(sunModel)
	{
		sunModel->Shutdown();
		delete sunModel;
		sunModel = 0;
	}

	if(moonModel)
	{
		moonModel->Shutdown();
		delete moonModel;
		moonModel = 0;
	}

	if (rocketModel)
	{
		rocketModel->Shutdown();
		delete rocketModel;
		rocketModel = 0;
	}

	if (mercuryModel)
	{
		mercuryModel->Shutdown();
		delete mercuryModel;
		mercuryModel = 0;
	}

	if (marsModel)
	{
		marsModel->Shutdown();
		delete marsModel;
		marsModel = 0;
	}

	if (venusModel)
	{
		venusModel->Shutdown();
		delete venusModel;
		venusModel = 0;
	}

	if (jupiterModel)
	{
		jupiterModel->Shutdown();
		delete jupiterModel;
		jupiterModel = 0;
	}

	if (saturnModel)
	{
		saturnModel->Shutdown();
		delete saturnModel;
		saturnModel = 0;
	}

	if (uranusModel)
	{
		uranusModel->Shutdown();
		delete uranusModel;
		uranusModel = 0;
	}

	if (neptuneModel)
	{
		neptuneModel->Shutdown();
		delete neptuneModel;
		neptuneModel = 0;
	}

	if (saturnRing)
	{
		saturnRing->Shutdown();
		delete saturnRing;
		saturnRing = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	if (GetAsyncKeyState('2') & 0x8000) // Changing camera angle on keyboard input
	{
		m_Position->SetPosition(0.0f, 150.0f, 0.0f);
		m_Position->SetRotation(90.0f, 0.0f, 0.0f);
	}

	if (GetAsyncKeyState('1') & 0x8000) // Changing camera angle on keyboard input
	{
		m_Position->SetPosition(0.0f, 0.0f, -150.0f);
		m_Position->SetRotation(0.0f, 0.0f, 0.0f);
	}
	
	//Rotation and Translation for the earth model.\\\\\\\\\\\\\\\\\\\

	XMMATRIX scaleEarth;
	scaleEarth = XMMatrixScaling(0.03f, 0.03f, 0.03f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleEarth);


	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 10.0f));


	//set up positioning factors
	translateMatrix = XMMatrixTranslation(20.0f, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR MyAxis; MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, (rotation * 0.9))); //Set up speed of rotation on its axis

	

	// Render the first model using the texture shader.
	earthModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), earthModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		earthModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}


	//Rotation and Translation for the sun model. \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	XMMATRIX scaleSun;
	scaleSun = XMMatrixScaling(0.2f, 0.2f, 0.2f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleSun);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation)); 

	
	// Render the second model using the light shader.
	sunModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), sunModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		sunModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the moon model. \\\\\\\\\\\\\\\\\\\\\\\\\\\\\


	XMMATRIX scaleMoon;
	scaleMoon = XMMatrixScaling(0.02f, 0.02f, 0.02f);

	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMoon);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation));

	//set up positioning factors. Orbit from center of earth
	translateMatrix = XMMatrixTranslation(3.0f, 0.0f + sin(timeGetTime() / 500.0f), 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR MyAxis1;
	MyAxis1 = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis1, rotation));


	//set up positioning factors. Orbit from center of Sun
	translateMatrix = XMMatrixTranslation(20.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	//worldMatrix = XMMatrixRotationY(rotation);
	XMVECTOR MyAxis2;
	MyAxis2 = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis2, (rotation * 0.9))); //Set up speed of rotation on its axis


	// Render the third model using the bump map shader. 

	moonModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), moonModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		moonModel->GetColorTexture(), moonModel->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the rocket model. \\\\\\\\\\\\\\\\\\\\\\\\\\\\

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleRocket;
	scaleRocket = XMMatrixScaling(0.008f, 0.008f, 0.008f);

	worldMatrix = XMMatrixMultiply(worldMatrix, scaleRocket);

	//self-spinning
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 10.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(50, 20.0f + sin(timeGetTime() / 1000.0f), 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR rocketAxis;
	rocketAxis = XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(rocketAxis, (rotation * 0.2))); //Set up speed of rotation on its axis

	// Render the rocket model using the map shader.
	rocketModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), rocketModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		rocketModel->GetTexture());

	if(!result)
	{
		return false;
	}


	//Rotation and Translation for the mercury model.\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleMercury;
	scaleMercury = XMMatrixScaling(0.01f, 0.01f, 0.01f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleMercury);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 4.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(10.0f, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR mercuryAxis; mercuryAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(mercuryAxis, (rotation * 1.4))); //Set up speed of rotation on its axis

	// Render the mercury model using the texture shader.
	mercuryModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), mercuryModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		mercuryModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the venus model.\\\\\\\\\\\\\\\\\\\\\\\\
	

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleVenus;
	scaleVenus = XMMatrixScaling(0.01f, 0.01f, 0.01f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleVenus);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 5.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(15.0f, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR venusAxis; venusAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(venusAxis, rotation)); //Set up speed of rotation on its axis

	// Render the venus model using the bump shader.
	venusModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), venusModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		venusModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the Mars model.\\\\\\\\\\\\\\\\\\\\\\\\
	
	
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleMars;
	scaleMars = XMMatrixScaling(0.035f, 0.035f, 0.035f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleMars);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 5.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(25.0, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR marsAxis; marsAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(marsAxis, (rotation * 0.8))); //Set up speed of rotation on its axis

	// Render the Mars model using the texture shader.
	marsModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), marsModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		marsModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the Jupiter model.\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleJupiter;
	scaleJupiter = XMMatrixScaling(0.09f, 0.09f, 0.09f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleJupiter);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 10.0f));


	//set up positioning factors
	translateMatrix = XMMatrixTranslation(35.0, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR jupiterAxis; jupiterAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(jupiterAxis, (rotation * 0.6))); //Set up speed of rotation on its axis

	// Render the Jupiter model using the texture shader.
	jupiterModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), jupiterModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		jupiterModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());


	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the Saturn model.\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleSaturn;
	scaleSaturn = XMMatrixScaling(0.07f, 0.07f, 0.07f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleSaturn);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 3.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(45.0, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR saturnAxis; saturnAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(saturnAxis, (rotation * 0.5))); //Set up speed of rotation on its axis

	// Render the Saturn model using the texture shader.
	saturnModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), saturnModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		saturnModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}



	//Rotation and Translation for the Saturn ring model.\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX saturnRingScale;
	saturnRingScale = XMMatrixScaling(0.02f, 0.02f, 0.02f); worldMatrix = XMMatrixMultiply(worldMatrix, saturnRingScale);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 3.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(45.0, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR sRingAxis; sRingAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(sRingAxis, (rotation * 0.5))); //Set up speed of rotation on its axis

	// Render the mercury model using the texture shader.
	saturnRing->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), saturnRing->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		saturnRing->GetTexture());

	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the Uranus model.\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleUranus;
	scaleUranus = XMMatrixScaling(0.04, 0.04, 0.04); worldMatrix = XMMatrixMultiply(worldMatrix, scaleUranus);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 7.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(60.0, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR uranusAxis; uranusAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(uranusAxis, (rotation * 0.4))); //Set up speed of rotation on its axis

	// Render the uranus model using the texture shader.
	uranusModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), uranusModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		uranusModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	//Rotation and Translation for the neptune model.\\\\\\\\\\\\\\\\\\\\\\\\


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	XMMATRIX scaleNeptune;
	scaleNeptune = XMMatrixScaling(0.05f, 0.05f, 0.05f); worldMatrix = XMMatrixMultiply(worldMatrix, scaleNeptune);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 8.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(70.0f, 0.0f + sin(timeGetTime() / 1000.0f), 0.0f); worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR neptuneAxis; neptuneAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(neptuneAxis, (rotation * 0.2)));

	// Render the neptune model using the texture shader.
	neptuneModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), neptuneModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		neptuneModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}