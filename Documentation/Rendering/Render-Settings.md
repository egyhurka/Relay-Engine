# Render Settings

Class `Renderer`

`Renderer::vSync(interval)`
- `true`: Locks the frame rate to 60 FPS
- `false`: No frame rate limit, rendering at maximum speed

`Renderer::setBackgroundColor(ColorRGB color)`
- Sets the background color of the rendering window.

`Renderer::polygonMode(GLenum mode)`
- `GL_FILL`: default, filled polygon rendering
- `GL_LINE`: wireframe rendering
- **Bound to F1 for easy toggling**