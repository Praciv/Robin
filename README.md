# Robin

This is a custom 3D game engine that I'm developing, roughly following [TheCherno's game engine series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) as a guide. The aim is to learn how a game engine works under the hood and to create a flexible lightweight, and powerful base for games and interactive applications. The engine is built as a static library and is currently linked to to projects, the runtime app sandbox which is being used to test features, and the editor to be used to create games with. 

## Implemented features 

### Rendering 
- Custom shader support
- Texture loading and rendering 
- Vertex buffer and index buffer management

### Maths and Graphics
- Currently supporting OpenGL through GLAD
- Orthogonal & perspective cameras with camera controllers
- Math primitves for transformations through GLM

### UI
- Editor using Dear ImGui
- UI Docking and a viewport for the game  

### Platform 
- Currently only supporting Windows 
- Window and context management through GLFW
- Event handling 
- Custom key and Mouse codes

### Core
- Timestep management and delta time calculation
- Basic Logging with different severity levels 
- Layer system for organized update/render orde
- event dispatcher and observer pattern 

## Current Next steps 

- **Runtime app and editor integration**: fully link the sandbox app and the editor such that changes made on the editor affect the runtime application 

- **Entity Component System:** Implement a ECS architecture with core components (Transform, MeshRenderer, Camera, Lights) 
- **Scene Management System:** Implement scene graph with hierarchical transforms, scene serialization, and scene switching capabilities
- **Primitives and model loading:** Add support for basic 3D primitives (cube, sphere, plane) and 3D model loading
- **Material System:** Create material definitions with shader bindings, material properties, and PBR support

## Future Goals 

### Short-term

- **Gizmos and Editor Tools:** Translation, rotation, scale gizmos with object manipulation
- **Asset Browser:** File system browser with drag-and-drop functionality
- **Batch Rendering:** Optimize draw calls with sprite batching and mesh instancing
- **Lighting System:** Point, directional, and spot lights with basic shadow mapping

### Medium-term

- **Post-Processing Pipeline:** Framebuffer management with bloom, SSAO, and tone mapping
- **Audio System:** 3D positional audio with FMOD or OpenAL integration
- **Scripting Support:** C# scripting integration with hot-reloading
- **Cross-platform File System:** Abstract file operations for asset packaging
- **Physics Engine:** Integration with Bullet Physics or custom physics implementation

### Long-term

- **Vulkan Support:** Modern graphics API support alongside OpenGL
- **Fully Fledged Editor:** Complete game development environment with visual editors
- **Linux and macOS Support:** Multi-platform deployment capabilities
- **Advanced Rendering:** Deferred rendering, PBR materials, and modern lighting techniques

## Architecture Overview
The engine follows a modular architecture with clear separation of concerns:

- **Core:** Application framework, logging, events, and platform abstraction
- **Renderer:** Graphics API abstraction, cameras, shaders, and rendering commands
- **Platform:** Window management, input handling, and OS-specific implementations
- **Editor:** ImGui-based tools and game development interface
- **Sandbox:** Test application for feature validation and development

## Dependencies

- **GLFW:** Window and input management
- **GLAD:** OpenGL function loading
- **GLM:** Mathematics library for graphics
- **Dear ImGui:** Immediate mode GUI
- **stb_image:** Image loading library
- **spdlog:** Fast C++ logging library

## Getting Started
Visual Studio 2022 is recommended for Windows development.

### Prerequisites

- Windows 10/11
- Visual Studio 2022 with C++ development tools
- Git with submodule support

### Setup Instructions


1. Clone the repository with submodules:
 
>git clone --recursive https://github.com/Praciv/Robin
2. Navigate to the project directory:
> cd Robin    
3. Run the project generation script:
> GenerateProject.bat
4. Open Robin.sln in Visual Studio 2022
5. Set the startup project to either Sandbox (for testing) or Editor (for development)
6. Build and run with F5 or Ctrl+F5

## Project Structure


```
Robin/
├── Robin/                 # Core engine library
│   ├── src/
│   │   ├── Robin/         # Public engine headers
│   │   └── Platform/      # Platform-specific implementations
│   └── vendor/            # Third-party dependencies
├── Sandbox/               # Test application
├── Editor/                # Game editor application
├── scripts/               # Build and utility scripts
└── premake5.lua          # Build configuration
```
## Contributing

This is primarily a learning project, but contributions and suggestions are welcome! Please feel free to:

- Report bugs and issues
- Suggest new features or improvements
- Submit pull requests for bug fixes
- Share feedback on architecture decisions

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

This project was strongly influenced by:

- [TheCherno's Game Engine series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) - Primary architectural guidance
- [Learn OpenGL](https://learnopengl.com/) - Graphics programming tutorials
- [Game Engine Architecture](https://www.gameenginebook.com/) by Jason Gregory
- The broader game development and graphics programming community

## Status

🚧 This engine is currently in active development and not yet suitable for production use.
Current focus is on implementing core systems and editor functionality. The API may change significantly as development progresses.