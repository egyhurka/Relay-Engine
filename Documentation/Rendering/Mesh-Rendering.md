# Simple Rendering
To begin with, we define a cube mesh using the `Mesh` class

```
Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, ColorRGB color, std::optional<Texture> texture);
```

Utilizing the built-in methods `Mesh::CreateCubeVertices()` and `Mesh::CreateCubeIndices()` greatly simplifies this process

For specifying the color, we have both  `ColorRGB` and `ColorRGBA` structures at our disposal. For instance, we can define a white color as follows
```
ColorRGB color = {1.0f, 1.0f, 1.0f}; // WHITE
```
Alternatively, we can instantiate it using
```
ColorRGB(1.0f, 1.0f, 1.0f);
```

Since textures are not yet functional, we can use `std::nullopt` as the last parameter. The complete definition for creating the cube mesh looks like this

```
Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
```

Having successfully created the cube mesh, we need to add it to the render queue. There are two methods available for queue addition `addMeshToRenderQueue(Mesh* mesh)` for single mesh rendering and `addInstancedObjectToRenderQueue(InstancedObject* object)` for instanced objects. For rendering the single cube, we will use the simple mesh render queue by adding the following line
```
renderer.addMeshToRenderQueue(&mesh);
```

In summary, we can condense the creation and addition of the cube mesh into three concise lines
```
ColorRGB color = { 0.0f, 1.0f, 0.0f };
Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
renderer.addMeshToRenderQueue(&mesh);
```

### Defining custom Mesh

It's similar to the first example, but it allows you to define your own positions, such as for a triangle
```
std::vector<Vertex> vertices = {
    //     COORDINATES                   /        COLORS                    /   NORMALS                 
    { glm::vec3(-0.5f, 0.0f,  0.5f),   glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(-0.5f, 0.0f, -0.5f),   glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(0.5f, 0.0f, -0.5f),    glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(0.5f, 0.0f,  0.5f),    glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(0.0f, 0.8f,  0.0f),    glm::vec3(0.92f, 0.86f, 0.76f),    glm::vec3(0.0f, 0.0f, 1.0f) } 
};
```

```
std::vector<GLuint> indices = {
    0, 1, 2,  // Base triangle 1
    2, 3, 0,  // Base triangle 2
    0, 4, 1,  // Side triangle 1
    1, 4, 2,  // Side triangle 2
    2, 4, 3,  // Side triangle 3
    3, 4, 0   // Side triangle 4
};
```

The rest of the code remains unchanged
```
ColorRGB color = { 1.0f, 1.0f, 0.0f };
Mesh mesh(vertices, indices, color, std::nullopt);
renderer.addMeshToRenderQueue(&mesh);
```

The entire code
```
std::vector<Vertex> vertices = {
    //     COORDINATES                   /        COLORS                    /   NORMALS                 
    { glm::vec3(-0.5f, 0.0f,  0.5f),   glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(-0.5f, 0.0f, -0.5f),   glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(0.5f, 0.0f, -0.5f),    glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(0.5f, 0.0f,  0.5f),    glm::vec3(0.83f, 0.70f, 0.44f),    glm::vec3(0.0f, 0.0f, 1.0f) },
    { glm::vec3(0.0f, 0.8f,  0.0f),    glm::vec3(0.92f, 0.86f, 0.76f),    glm::vec3(0.0f, 0.0f, 1.0f) } 
};

std::vector<GLuint> indices = {
    0, 1, 2,  // Base triangle 1
    2, 3, 0,  // Base triangle 2
    0, 4, 1,  // Side triangle 1
    1, 4, 2,  // Side triangle 2
    2, 4, 3,  // Side triangle 3
    3, 4, 0   // Side triangle 4
};

ColorRGB color = { 1.0f, 1.0f, 0.0f };
Mesh mesh(vertices, indices, color, std::nullopt);
renderer.addMeshToRenderQueue(&mesh);
```

# Instance Rendering
Instance rendering improves performance by reducing the number of draw calls needed for rendering multiple instances of the same object, allowing the GPU to process them more efficiently. This technique optimizes memory usage and simplifies scene management while maintaining the flexibility to customize individual instances

To start, we define a cube mesh similarly to the previous example using `Mesh`. Next, we create an instance of this mesh using `InstancedObject(Mesh* mesh)` which allows for optimized rendering of multiple copies (instances) of the same mesh

Here’s the code for defining and queuing a simple cube instance
```
ColorRGB color = { 0.0f, 0.3f, 1.0f };
Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
InstancedObject object(&mesh);
renderer.addMeshToRenderQueue(&mesh);
```

Next, we assign unique positions to each instance. We can use the `Random` class to generate these positions with the `randomPosition()` method, which provides random `glm::vec3` coordinates for positioning. This approach is useful for placing instances in varied locations within a defined volume
```
Random random(glm::vec2 volume);
```
```
Random rnd(glm::vec2(-5.0f, 5.0f));
for (int i = 0; i < 10; i++) {
    object.addInstancePosition(rnd.randomPosition());
}
```
**Note:** The number of added positions determines the count of instances to render

To make all instances share the same color, we can set them to be monochromatic (single-color). By enabling the `isMonochromatic` property and adding a color to the instanced object, we ensure each instance displays the specified color. Finally, we complete the instance setup with `setupInstances()`. This step finalizes the instancing configuration, ensuring all instances are ready for rendering with the assigned properties
```
object.isMonochromatic = true;
object.addInstanceColor(color);
object.setupInstances();
```

Here's the entire code
```
ColorRGB color = { 0.0f, 0.3f, 1.0f };
Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
InstancedObject object(&mesh);
renderer.addMeshToRenderQueue(&mesh);

Random rnd(glm::vec2(-5.0f, 5.0f));
for (int i = 0; i < 10; i++) {
    object.addInstancePosition(rnd.randomPosition());
}

object.isMonochromatic = true;
object.addInstanceColor(color);
object.setupInstances();
renderer.addInstancedObjectToRenderQueue(&object);
```