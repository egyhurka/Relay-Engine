# Loading
We love the challenge of rendering large numbers of meshes, but managing so many can be a performance hurdle. To tackle this, we load them in manageable chunks, speeding up the initialization process and optimizing memory usage. By dividing the loading into chunks, each 'batch' is processed individually, ensuring smoother rendering and reducing the load on the system

You could then follow up with an example of the code you’re using to load the instances in batches, showing the benefits of `Loader::simple()` and `Loader::batch()`

The `Loader::simple()` just to measure the load time it took. Here's the code with each instance random color, don't need explanation

```
Loader::simple(unsigned int count, bool stopwatch, std::function<void()> function);
```
```
ColorRGB color = { 0.0f, 0.3f, 1.0f };
Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
InstancedObject object(&mesh);
renderer.addMeshToRenderQueue(&mesh);

Random rnd(glm::vec2(-5.0f, 5.0f));
Loader::simple(10, true, [&]() {
    object.addInstancePosition(rnd.randomPosition());
    ColorRGB color = { rnd.randomPosition().x, rnd.randomPosition().y, rnd.randomPosition().z };
    object.addInstanceColor(color);
});

object.setupInstances();
renderer.addInstancedObjectToRenderQueue(&object);
```
**Note:** delete `isMonochromatic`

To handle advanced loading, we use the `Loader::batch` function. This method is ideal for large-scale instance creation, allowing us to load massive numbers of objects in smaller, optimized chunks.

Here's an example
```
unsigned int totalCubes = 100'000;
Loader::batch(totalCubes, Loader::batchSizeCalculator(totalCubes), true, [&](int i) {
    object.addInstancePosition(rnd.randomPosition());
    ColorRGB color = { rnd.randomPosition().x, rnd.randomPosition().y, rnd.randomPosition().z };
    object.addInstanceColor(color);
});
```

```
ColorRGB color = { 0.0f, 0.3f, 1.0f };
Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
InstancedObject object(&mesh);
renderer.addMeshToRenderQueue(&mesh);

Random rnd(glm::vec2(-100.0f, 100.0f));
unsigned int totalCubes = 100'000;
Loader::batch(totalCubes, Loader::batchSizeCalculator(totalCubes), true, [&](int i) {
    object.addInstancePosition(rnd.randomPosition());
    ColorRGB color = { rnd.randomPosition().x, rnd.randomPosition().y, rnd.randomPosition().z };
    object.addInstanceColor(color);
});

object.setupInstances();
renderer.addInstancedObjectToRenderQueue(&object);
```